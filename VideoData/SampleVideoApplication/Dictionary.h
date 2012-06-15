// Dictionary.h: interface for the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DICTIONARY_H__736E8D7B_3FB4_4B85_9D5D_9A0315A1A84A__INCLUDED_)
#define AFX_DICTIONARY_H__736E8D7B_3FB4_4B85_9D5D_9A0315A1A84A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct dicElement
{
	DWORD	m_Prefix;		//	keep the prefix of the element
	BYTE	m_Letter;		//	keep the letter of the element

	dicElement()
	{
		m_Prefix = 0;
		m_Letter = 0;
	}
};

class CDictionary : public CPtrArray  
{
public:
	void GetBytesFromCode(CByteArray *Buffer, DWORD code);
	DWORD GetMaxCode();
	BOOL IsCodeExist(DWORD code);
	long GetEntry(DWORD prefix, BYTE letter);
	DWORD AddEntry(DWORD prefix, BYTE letter);
	void ClearDictionary();
	CDictionary();
	virtual ~CDictionary();

private:
};

#endif // !defined(AFX_DICTIONARY_H__736E8D7B_3FB4_4B85_9D5D_9A0315A1A84A__INCLUDED_)
