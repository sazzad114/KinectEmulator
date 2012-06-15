#pragma once
#include<WinNT.h>
#include<WinDef.h>
#include<MSR_NuiImageCamera.h>
#include<NuiImageBuffer.h>
#include"iNuiImageBuffer.h"


using namespace std;

class iImageFrame
{

public:
  LARGE_INTEGER             liTimeStamp;
  DWORD                     dwFrameNumber;
  NUI_IMAGE_TYPE            eImageType;
  NUI_IMAGE_RESOLUTION      eResolution;
 // iNuiImageBuffer    pFrameTexture;
  DWORD                     dwFrameFlags_NotUsed;  
  NUI_IMAGE_VIEW_AREA       ViewArea_NotUsed;
    

  iImageFrame(){}
	iImageFrame(const NUI_IMAGE_FRAME * frame)
	{
		this->liTimeStamp = frame->liTimeStamp;
		this->dwFrameNumber = frame->dwFrameNumber;
		this->eImageType = frame->eImageType;
		this->eResolution = frame->eResolution;
		this->dwFrameFlags_NotUsed=frame->dwFrameFlags_NotUsed;
		this->ViewArea_NotUsed=frame->ViewArea_NotUsed;

	}
};

class videoFrame
{
public:
	iImageFrame frameData;
	BYTE* buffer;
	videoFrame(iImageFrame frame,BYTE* b)
	{
		this->frameData=frame;
		this->buffer=b;
	}
};