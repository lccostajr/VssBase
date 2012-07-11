// VssDecoder.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VssDecoder.h"

#include <string>
#include <iostream>

using namespace std;

void getArguments(int argc, char* argv[], string *Path, string *VssPath, string *SSDIR, string *SSUSER, string *SSPWD);
void printArguments();

int _tmain(int argc, char* argv[])
{
	string Path, VssPath, SSDIR, SSUSER, SSPWD;

	getArguments(argc, argv, &Path, &VssPath, &SSDIR, &SSUSER, &SSPWD);

	VssDecoder *myVssDecoder = new VssDecoder();
	myVssDecoder->open(Path + "vssver2.scc");
	myVssDecoder->decode();
	myVssDecoder->createGetScript(Path + "VssBase.bat", VssPath, SSDIR, SSUSER, SSPWD);
	myVssDecoder->close();

	return 0;
};

void getArguments(int argc, char* argv[], string *Path, string *VssPath, string *SSDIR, string *SSUSER, string *SSPWD)
{
	bool bPath    = false;
	bool bVssPath = false;
	bool bSSDIR	  = false;
	bool bSSUSER  = false;
	bool bSSPWD	  = false;
	
	for ( int i = 1; i < argc; i++ )
	{
		//cout << argv[i] << endl;
		if ( _stricmp(argv[i],"-Path") == 0 )
		{
			Path->clear();
			Path->append(argv[++i]);
			bPath = true;
		}
		else if ( _stricmp(argv[i],"-VssPath") == 0 )
		{
			VssPath->clear();
			VssPath->append(argv[++i]);
			bVssPath = true;
		}
		else if ( _stricmp(argv[i],"-SSDIR") == 0 )
		{
			SSDIR->clear();
			SSDIR->append(argv[++i]);
			bSSDIR = true;
		}
		else if ( _stricmp(argv[i],"-SSUSER") == 0 )
		{
			SSUSER->clear();
			SSUSER->append(argv[++i]);
			bSSUSER = true;
		}
		else if ( _stricmp(argv[i],"-SSPWD") == 0 )
		{
			SSPWD->clear();
			SSPWD->append(argv[++i]);
			bSSPWD = true;
		}
		else if ( _stricmp(argv[i],"-help") == 0 )
		{
			printArguments();
			exit(1);
		}
		else
		{
			cout << "ERROR: Invalid usage" << endl;
			cout << "Try VssBase.exe -help for help" << endl;
			exit(1);
		}

	}

	if ( !bPath || !bVssPath || !bSSDIR || !bSSUSER || !bSSPWD )
	{
		cout << "ERROR: missing arguments" << endl;
		cout << "Try VssBase.exe -help for help" << endl;
		exit(1);
	}

	return;
};

void printArguments()
{
	cout
		<< "VssBase: creates a batch file to get files from Visual Source Safe" << endl
		<< "         accordingly to file vssver2.scc of working directory." << endl
		<< endl
		<< "Usage:" << endl
		<< endl
		<< "  VssBase.exe [-Path <Path> -VssPath <VssPath> -SSDIR <SSDIR> -SSUSER <SSUSER> -SSPWD <SSPWD> | -help ]" << endl
		<< endl
		<< "     -Path    <Path>    set source directory to <Path>" << endl
		<< "     -VssPath <VssPath> set Visual Source Safe program directory to <VssPath>" << endl
		<< "     -SSDIR   <SSDIR>   set repository directory to <SSDIR>" << endl
		<< "     -SSUSER  <SSUSER>  set user to <SSUSER>" << endl
		<< "     -SSPWD   <SSPWD>   set user password to <SSPWD>" << endl
		;

	return;
}