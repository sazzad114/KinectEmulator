#pragma once
#include<vector>
#include<WinDef.h>

using namespace std;

class iNuiImageBuffer
{
public:
	int     m_Width;
    int     m_Height;
    int     m_BytesPerPixel;
	vector<BYTE> m_Buffer;

	iNuiImageBuffer()
	{
	}
};