#include<iostream>
#include<fstream>
#include<string>
#include<MSR_NuiApi.h>
#include<WinNT.h>
#include "stdafx.h"
#include "SkeletalViewer.h"
#include "resource.h"
#include <mmsystem.h>


using namespace std;

class FileWriter
{

public:
	fstream fp;

	FileWriter(string filename)
	{
		fp = fstream(filename.c_str(), ios::out | ios::binary);
	}
	
	void WriteSkeletonData(NUI_SKELETON_FRAME  data)
	{		
		fp.write((char*)&data,sizeof(data));	
	}

	void CloseFile()
	{
		fp.close();
	}

};