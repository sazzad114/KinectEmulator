#include<iostream>
#include<fstream>
#include<string>
#include<MSR_NuiApi.h>
#include<WinNT.h>
#include "stdafx.h"
#include "SkeletalViewer.h"
#include "resource.h"
#include <mmsystem.h>
#include "LZWCompression.h"

using namespace std;

class FileWriter
{

public:
	long packetSize;
	long packetCount;
	CLZWCompression compressor;
	long destinationSize;
	BYTE arr[1250000];
	fstream fp;

	FileWriter(string filename)
	{
		packetSize = 0;
		packetCount = 0;
		destinationSize = 1250000;
		fp = fstream(filename.c_str(), ios::out | ios::binary);

	}
	
	void WriteVideoData(const NUI_IMAGE_FRAME * imageFrame, const NUI_IMAGE_FRAME * keyFrame, bool flag)
	{	
		packetCount++; 		
		KINECT_LOCKED_RECT LockedRect;
		imageFrame->pFrameTexture->LockRect( 0, &LockedRect, NULL, 0);
		
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

	void CloseFile()
	{
		fp.close();
	}

};