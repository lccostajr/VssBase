
#ifndef VSSDECODER_H
#define VSSDECODER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <vector>

using namespace std;

typedef unsigned long DWORD;
typedef char BYTE;

struct FileHeader
{
	DWORD       dwSignature;         /* 0x00011234 */
	BYTE        arrDatabaseGuid[16]; /* a GUID identifying the VSS database associated with the vssver2.scc file */
	DWORD       dwChecksum;          /* a checksum of the vssver2.scc file */
	DWORD       dwProjectID;         /* the number identifying the project from VSS database accociated with the vssver2.scc files */
	DWORD       dwFileEntries;       /* the number of file entries stored in the vssver2.scc file and following this structure */
};

struct FileEntry
{
	DWORD       dwFileID;            /* the number identifying the file in the VSS database that is tracked by this vssver.scc file */
	DWORD       dwFileChecksum;      /* the file's checksum */
	DWORD       dwFileTimestamp;     /* a file timestamp */
	DWORD       dwFileVersion;       /* the version of the file from the VSS database that you have locally */
};

class VssDecoder
{
public:
	VssDecoder();
	~VssDecoder();

	void open(string FileName);
	void close();
	void decode();
	void createGetScript(string VssBaseBat, string VssPath, string SSDIR, string SSUSER, string SSPWD);

private:
	FileHeader fileHeader;
	string project;
	vector<string *> fileNames;
	vector<FileEntry *> fileEntries;

	ifstream vssFile;
	bool decoded;

};

#endif /* VSSDECODER_H */