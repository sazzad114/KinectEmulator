#include<iostream>
#include<fstream>
#include<string>
#include<MSR_NuiApi.h>
#include<WinNT.h>
#include"LZWCompression.h"
using namespace std;

class FileIO
{
	//string filename;
public:
	long packetSize;
	long packetCount;
	CLZWCompression compressor;
	long destinationSize;
	BYTE arr[1250000];
	fstream fp;
	//const NUI_IMAGE_FRAME * keyFrame
	FileIO(string filename)
	{
		packetSize = 0;
		packetCount = 0;
		destinationSize = 1250000;
		fp = fstream(filename.c_str(), ios::out | ios::binary);
		//fp.open("c:\\x.dat",ios::out | ios::binary);
		bool b = fp.is_open();
		//fp.close();
	}
	fstream& OpenFile(string filename)
	{
		fstream file(filename.c_str(),ios::app | ios::binary);
		return file;
	}
	
	void WriteData(string filename,void* data)
	{		
		fstream file(filename.c_str(),ios::app | ios::binary);
		file.write((char*)data,sizeof(iSkeletonData));	
		file.close();
	}
	void ReadData(fstream& file,void* frame)
	{	
		//NUI_SKELETON_FRAME frame;
		file.read((char*)frame,sizeof(iSkeletonData));
		//return (void*)(&frame);
	}
	void WriteVideoData(const NUI_IMAGE_FRAME * imageFrame, const NUI_IMAGE_FRAME * keyFrame, bool flag)
	{	
		packetCount++;
		iImageFrame frame(imageFrame); 		
		KINECT_LOCKED_RECT LockedRect;
		imageFrame->pFrameTexture->LockRect( 0, &LockedRect, NULL, 0 );
		
		if( LockedRect.Pitch != 0 )
		{
			BYTE * pBuffer = (BYTE*) LockedRect.pBits;			
			long size=imageFrame->pFrameTexture->BufferLen();

			if(!flag)
			{
				KINECT_LOCKED_RECT keyFrameLockedRect;
				keyFrame->pFrameTexture->LockRect( 0, &keyFrameLockedRect, NULL, 0 );
				BYTE * keyFramepBuffer = (BYTE*) keyFrameLockedRect.pBits;			
				if( keyFrameLockedRect.Pitch != 0 )
				{		
					for(int i = 0; i<size; i++)
						pBuffer[i] = pBuffer[i] - keyFramepBuffer[i];
					compressor.Compress(pBuffer,arr, size, &destinationSize);
					fp.write((char*)&destinationSize,sizeof(long));
					fp.write((char*)arr,destinationSize);
					fp.flush();
				}
			}
			else
			{
				fp.write((char*)&size,sizeof(long));	
				fp.write((char*)pBuffer,size);
				fp.flush();
			}
		}	
	}
	void ReadVideoData(string filename,void* data,int pos)
	{
		fstream file(filename.c_str(),ios::in | ios::binary);
	//	fstream f("size.dat",ios::in|ios::binary);
		file.seekp(1228800*pos);
		file.read((char*)data,1228800);
		file.close();
	}
	void CloseFile()
	{
		fp.close();
	}

};