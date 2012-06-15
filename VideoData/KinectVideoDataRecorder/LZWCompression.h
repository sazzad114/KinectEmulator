// LZWCompression.h: interface for the CLZWCompression class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LZWCOMPRESSION_H__6C8D7CDC_4AF5_426D_A4AF_49682963D8C3__INCLUDED_)
#define AFX_LZWCOMPRESSION_H__6C8D7CDC_4AF5_426D_A4AF_49682963D8C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Dictionary.h"

class CLZWCompression  
{
public:
	//	These two functions were added to use the log file with the application
	BOOL DecompressWithLog(CFile &source, CFile &destination, CStringArray *pLog);
	BOOL CompressWithLog(CFile &source, CFile &destination, CStringArray *pLog = NULL);
	void Log(CString data);
private:
	CStringArray * p_Log;

public:
	void ClearDictionary();
	BOOL Decompress(CFile &source, CFile &destination);
	BOOL Decompress(byte* source, byte* destination,  long sourceSize,  long * destinationSize);
	BOOL Compress(byte* source, byte* destination,  long sourceSize,  long * destinationSize);
	BOOL Compress(CFile &source, CFile &destination);
	void CreateDictionary();
	CLZWCompression();
	virtual ~CLZWCompression();
private:
	CString convertASCIIToText(BYTE ascii);
	void Init();
	void CalculateBitSize(DWORD value);
	void CloseCompressedFile(CFile &source);
	void CloseCompressedFile(byte *source, long* destIndex);
	DWORD DecompressData(CFile &source);
	DWORD DecompressData(byte* source, long* sourceIndex, long sourceLength);	
	BYTE m_MaxBits;
	DWORD m_MaxCode[32];
	int m_TotalBits;
	void CompressData(CFile &dest, long toSave);
	void CompressData(byte* dest, long toSave, long* destIndex);
	DWORD m_SavedData;
	CDictionary *m_dictionary;
};

#endif // !defined(AFX_LZWCOMPRESSION_H__6C8D7CDC_4AF5_426D_A4AF_49682963D8C3__INCLUDED_)
