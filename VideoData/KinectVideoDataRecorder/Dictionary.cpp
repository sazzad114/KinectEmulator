// Dictionary.cpp: implementation of the CDictionary class.
//
//////////////////////////////////////////////////////////////////////

/*
	Created by: Luria Israel

  This project implements the use of a dynamic LZW compression.
  This code is free for use, and can be inserted into any MFC project.
*/
#include "stdafx.h"
#include "Dictionary.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDictionary::CDictionary()
{
}

CDictionary::~CDictionary()
{
	ClearDictionary();
}

void CDictionary::ClearDictionary()
{
	//	Go over every element in the dictionary and delete it
	dicElement *temp = NULL;

	while (GetSize() > 0)
	{
		temp = (dicElement*)GetAt(0);
		RemoveAt(0);
		delete[] temp;
	}
}

DWORD CDictionary::AddEntry(DWORD prefix, BYTE letter)
{
	//	Add a dictionary element.
	//	Since the dictionary should already have all the values
	//	between 0-255, we start it from 256.
	dicElement *temp = new dicElement;

	temp->m_Prefix = prefix;
	temp->m_Letter = letter;

	Add(temp);

	return GetSize() + 255;
}

long CDictionary::GetEntry(DWORD prefix, BYTE letter)
{
	//	Returns the code of an element from the dictionary
	//	by searching for the prefix and letter assosiated with
	//	that element code.
	
	//	Returns -1 if no entry was found
	int total = GetSize();
	dicElement *temp = NULL;
	int counter;
	for (counter = 0; counter < total; counter++)
	{
		temp = (dicElement*)GetAt(counter);

		if ((temp->m_Prefix == prefix) && 
			(temp->m_Letter == letter))
		{
			break;
		}
		temp = NULL;
	}

	if (temp != NULL)
		return counter + 256;
	else
		return -1;
}

BOOL CDictionary::IsCodeExist(DWORD code)
{
	//	Check if the code exist in the dictionary
	//	Returns TRUE if so, and FALSE if not.
	DWORD returnValue = 0;

	//	If the code is lower then 256, then the element is a normal
	//	ASCII character, and as such is considered to be in the
	//	dictionay.
	if (code < 256)
		return TRUE;

	returnValue = code - 256;
	if (returnValue < (unsigned)GetSize())
		return TRUE;
	else 
		return FALSE;
}

DWORD CDictionary::GetMaxCode()
{
	//	Return the highest code in the dictionary
	return GetSize() + 256;
}

void CDictionary::GetBytesFromCode(CByteArray *Buffer, DWORD code)
{
	//	Fill an array with bytes using the code for retrieving 
	//	those bytes from the dictionary elements

	//	Since we dont have 0-255 in the dictionary we have to make 
	//	sure, that if we get below 256 we stop (but still add that code)
	//	Every code higher then 255, will have a letter attached to it,
	//	which we use for getting the string back.
	dicElement *tmpEl = NULL;

	while (code > 255)
	{
		tmpEl = (dicElement*)GetAt(code - 256);
		Buffer->Add(tmpEl->m_Letter);
		code = tmpEl->m_Prefix;
	}
	Buffer->Add((BYTE)code);
}
