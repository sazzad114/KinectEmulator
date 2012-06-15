#include<iostream>
#include<fstream>
#include<string>

using namespace std;

class FileReader
{

public:

	fstream fp;

	FileReader(string filename)
	{

		fp = fstream(filename.c_str(), ios::in | ios::binary);

	}

	void CloseFile()
	{
		fp.close();
	}

};