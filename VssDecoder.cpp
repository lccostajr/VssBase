
#include "VssDecoder.h"

VssDecoder::VssDecoder()
{
	decoded = false;

	return;
}

VssDecoder::~VssDecoder()
{
	close();

	return;
}

void VssDecoder::close()
{
	if ( vssFile.is_open() )
	{
		vssFile.close();
	}
}

void VssDecoder::open(string FileName)
{
	vssFile.open(FileName, ios::in | ios::binary );
	
	return;
}

void VssDecoder::decode()
{
	if ( decoded ) return;

	// --- Read file header ---
	vssFile.seekg(0,ios::beg);
	vssFile.read((char *) &fileHeader, sizeof(fileHeader));

	// --- Read file entries ---
	for ( unsigned i = 0; i < fileHeader.dwFileEntries; i++ )
	{
		FileEntry *fileEntry = (FileEntry *) malloc(sizeof(FileEntry));
		vssFile.read((char *) fileEntry, sizeof(FileEntry));
		fileEntries.push_back(fileEntry);
	}

	// --- Buffer size ---
	ifstream::pos_type initNames = vssFile.tellg();
	vssFile.seekg(0,ios::end);
	ifstream::pos_type endNames = vssFile.tellg();
	vssFile.seekg(initNames,ios::beg);
	int buffSize = (int) endNames - (int) initNames;

	char *buff = (char *) malloc(buffSize);
	vssFile.read(buff,buffSize);

	char *buffPtr = buff;

	// --- Project name ---
	project.append(buffPtr);
	buffPtr += strlen(buffPtr) + 1;

	// --- Read file names ---
	for ( unsigned i = 0; i < fileHeader.dwFileEntries; i++ )
	{
		fileNames.push_back(new string(buffPtr));
		buffPtr += strlen(buffPtr) + 1;
	}

	free(buff);

	decoded = true;

	return;
}

void VssDecoder::createGetScript(string VssBaseBat, string VssPath, string SSDIR, string SSUSER, string SSPWD)
{
	if ( !decoded ) return;

	ofstream scriptFile;
	scriptFile.open(VssBaseBat);

	scriptFile << "@ECHO OFF" << endl;
	scriptFile << endl;
	scriptFile << "SET PATH=\"" << VssPath << "\";%PATH%" << endl;
	scriptFile << "SET SSDIR=" << SSDIR << endl;
	scriptFile << "SET SSUSER=" << SSUSER << endl;
	scriptFile << "SET SSPWD=" << SSPWD << endl;
	scriptFile << endl;
	scriptFile << "mkdir VssBase" << endl;
	scriptFile << "cd    VssBase" << endl;
	scriptFile << endl;

	for ( unsigned i = 0; i < fileNames.size(); i++ )
	{
		scriptFile << "ss Get " << project << "/" << *(fileNames[i]) << " -V" << fileEntries[i]->dwFileVersion << endl;
	}

	scriptFile << endl;
	scriptFile << "pause" << endl;
	
	scriptFile.close();

	return;
}