//#include<Windows.h>
#include<MSR_NuiApi.h>
#include<time.h>
#pragma once

class iSkeletonData
{
	time_t time_to_wait;
	NUI_SKELETON_FRAME SkeletonFrame;

public:
	iSkeletonData(time_t t,NUI_SKELETON_FRAME data)
	{
		this->time_to_wait=t;
		this->SkeletonFrame=data;
	}
};