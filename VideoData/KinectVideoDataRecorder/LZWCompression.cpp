// LZWCompression.cpp: implementation of the CLZWCompression class.
//
//////////////////////////////////////////////////////////////////////

/*
	Created by: Luria Israel

  This project implements the use of a dynamic LZW compression.
  This code is free for use, and can be inserted into any MFC project.
*/

#include "stdafx.h"
#include "LZWCompression.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLZWCompression::CLZWCompression()
{
	Init();
	p_Log = NULL;

	//	The Maximum code for a bit
	m_MaxCode[0]		= 0;
	m_MaxCode[1]		= 0x1;
	m_MaxCode[2]		= 0x3;
	m_MaxCode[3]		= 0x7;
	m_MaxCode[4]		= 0xF;
	m_MaxCode[5]		= 0x1F;
	m_MaxCode[6]		= 0x3F;
	m_MaxCode[7]		= 0x7F;
	m_MaxCode[8]		= 0xFF;
	m_MaxCode[9]		= 0x1FF;
	m_MaxCode[10]		= 0x3FF;
	m_MaxCode[11]		= 0x7FF;
	m_MaxCode[12]		= 0xFFF;
	m_MaxCode[13]		= 0x1FFF;
	m_MaxCode[14]		= 0x3FFF;
	m_MaxCode[15]		= 0x7FFF;
	m_MaxCode[16]		= 0xFFFF;
	m_MaxCode[17]		= 0x1FFF;
	m_MaxCode[18]		= 0x3FFFF;
	m_MaxCode[19]		= 0x7FFFF;
	m_MaxCode[20]		= 0xFFFFF;
	m_MaxCode[21]		= 0x1FFFFF;
	m_MaxCode[22]		= 0x3FFFFF;
	m_MaxCode[23]		= 0x7FFFFF;
	m_MaxCode[24]		= 0xFFFFFF;
	m_MaxCode[25]		= 0x1FFFFFF;
	m_MaxCode[26]		= 0x3FFFFFF;
	m_MaxCode[27]		= 0x7FFFFFF;
	m_MaxCode[28]		= 0xFFFFFFF;
	m_MaxCode[29]		= 0x1FFFFFFF;
	m_MaxCode[30]		= 0x3FFFFFFF;
	m_MaxCode[31]		= 0x7FFFFFFF;

}

void CLZWCompression::Init()
{
	m_dictionary = NULL;
	m_SavedData = 0;
	m_TotalBits = 0;
	m_MaxBits = 9;
}

CLZWCompression::~CLZWCompression()
{
	ClearDictionary();
}

//	This function was added to send log information to the view
void CLZWCompression::Log(CString data)
{
	//	Put something inside the log if exist
	if (p_Log != NULL)
		p_Log->Add(data);
}

//	Create a new dictionary
void CLZWCompression::CreateDictionary()
{
	Log("Creating dictionary!");
	m_dictionary = new CDictionary;
}

//	Remove the existing dictionary
void CLZWCompression::ClearDictionary()
{
	if (m_dictionary != NULL)
	{
		Log("Clear dictionary!");

		delete[] m_dictionary;
		m_dictionary = NULL;
	}
}

BOOL CLZWCompression::Compress(CFile &source, CFile &destination)
{
	long prefix = 0;
	long result = 0;
	BYTE readByte = 0;
	unsigned long filetotal = 0;
	CString logString;
	DWORD resAdd = 256;

	//	Initialize the neccessry data
	Init();

	//	Get the total file size
	filetotal = source.GetLength();

	//	Create the dictionary (if not created already)
	if (m_dictionary == NULL)
	{
		CreateDictionary();
	}

	//	Read the first byte from the file
	source.Read(&prefix, 1);

	//	Go over the rest of the file and read it
	while (source.GetPosition() < filetotal)
	{
		//	Read the second byte
		source.Read(&readByte, 1);

		//	Check if the prefix and readByte combination exist in the dictionary
		result = m_dictionary->GetEntry(prefix, readByte);

		//	If not exist
		if (result == -1)
		{
			//	Add the new combination
			resAdd = m_dictionary->AddEntry(prefix, readByte);
			//	Calculate the new bit size needed to encode the file
			CalculateBitSize(resAdd);

			//	To show a log in the view
			//logString.Format("Adding combination of %d and %d to dictionary to entry %d.",
			//	prefix, readByte, resAdd);
			//Log(logString);

			//	Send the prefix for compression in to the destination file
			CompressData(destination, prefix);

			//	Set the prefix as the readByte
			prefix = readByte;

			//	Initiate the result
			result = -1;
		}
		else
		{
			//	Set the prefix as the result
			prefix = result;
			readByte = 0;
		}
	}

	//	Compress the remaining information in the refix into the destination file
	CompressData(destination, prefix);
	//	Close the destination file
	CloseCompressedFile(destination);

	//	Remove the existing dictionary
	ClearDictionary();
	return TRUE;
}

BOOL CLZWCompression::Compress(byte* source, byte* destination,  long sourceSize,  long* destinationSize)
{
	//????????????????????????????????????? destination size????????????????????????????????????????????????????????????
	long prefix = 0;
	long result = 0;
	BYTE readByte = 0;
	unsigned long filetotal = 0;
	CString logString;
	DWORD resAdd = 256;
	long index = 0, destinationIndex = 0; //equvalent to file pointer for source and destination
	//	Initialize the neccessry data
	Init();

	//	Get the total file size
	filetotal = sourceSize;

	//	Create the dictionary (if not created already)
	if (m_dictionary == NULL)
	{
		CreateDictionary();
	}

	//	Read the first byte from the file
	//source.Read(&prefix, 1);
	prefix = source[index];
	index++;
	//	Go over the rest of the file and read it
	while (index < filetotal)
	{
		//	Read the second byte
		//source.Read(&readByte, 1);
		readByte = source[index];
		index++;

		//	Check if the prefix and readByte combination exist in the dictionary
		result = m_dictionary->GetEntry(prefix, readByte);

		//	If not exist
		if (result == -1)
		{
			//	Add the new combination
			resAdd = m_dictionary->AddEntry(prefix, readByte);
			//	Calculate the new bit size needed to encode the file
			CalculateBitSize(resAdd);

			//	To show a log in the view
			//logString.Format("Adding combination of %d and %d to dictionary to entry %d.",
			//	prefix, readByte, resAdd);
			//Log(logString);

			//	Send the prefix for compression in to the destination file
			CompressData(destination, prefix, &destinationIndex);

			//	Set the prefix as the readByte
			prefix = readByte;

			//	Initiate the result
			result = -1;
		}
		else
		{
			//	Set the prefix as the result
			prefix = result;
			readByte = 0;
		}

		
	}

	//	Compress the remaining information in the refix into the destination file
	CompressData(destination, prefix, &destinationIndex);
	//	Close the destination file
	CloseCompressedFile(destination, &destinationIndex);

	//	Remove the existing dictionary
	ClearDictionary();
	*destinationSize = destinationIndex;
	return TRUE;
}

void CLZWCompression::CompressData(byte* dest, long toSave, long* destIndex)
{
	DWORD writeData = 0;

	//	Move the data you want to write few bits to the left
	//	and combine it with the already existing data in the buffer
	m_SavedData |= (DWORD) toSave << (32 - m_MaxBits - m_TotalBits);

	//	Add the new added number of bits to the total bits counter
	m_TotalBits += m_MaxBits;

	//	Check if it's possible to enter the data to the file
	//	(over and equal a byte of data)
	while (m_TotalBits >= 8)
	{
		//	Get the byte we want to write
		writeData = m_SavedData;
		writeData >>= 24;
		//dest.Write(&writeData, 1);
		dest[*destIndex] = (byte)writeData;
		(*destIndex)++;

		//	remove the byte from the buffer
		m_SavedData <<= 8;
		//	Remove the byte from the counter
		m_TotalBits -= 8;
	}
}

void CLZWCompression::CompressData(CFile &dest, long toSave)
{
	DWORD writeData = 0;

	//	Move the data you want to write few bits to the left
	//	and combine it with the already existing data in the buffer
	m_SavedData |= (DWORD) toSave << (32 - m_MaxBits - m_TotalBits);

	//	Add the new added number of bits to the total bits counter
	m_TotalBits += m_MaxBits;

	//	Check if it's possible to enter the data to the file
	//	(over and equal a byte of data)
	while (m_TotalBits >= 8)
	{
		//	Get the byte we want to write
		writeData = m_SavedData;
		writeData >>= 24;
		dest.Write(&writeData, 1);

		//	remove the byte from the buffer
		m_SavedData <<= 8;
		//	Remove the byte from the counter
		m_TotalBits -= 8;
	}
}

BOOL CLZWCompression::Decompress(CFile &source, CFile &destination)
{
	DWORD prefix = 0, data = 0;
	CString logString;
	CByteArray decodeString;
	BYTE writeData = 0, character = 0;
	int counter = 0;

	Init();

	//	Create the dicionary (if not already created)
	if (m_dictionary == NULL)
	{
		CreateDictionary();
	}

	//	Get the first prefix information
	prefix = DecompressData(source);
	//	Save the prefix as the last used character (since we're writing it in the
	//	destination file)
	character = (BYTE)prefix;
	//	Write the prefix in the destination file (the first byte inside
	//	a LZW copressed file is always the first byte of the original file)
	destination.Write(&prefix, 1);

	//	While the recieve data is not the maximum bit data possible
	while ((data = DecompressData(source)) != m_MaxCode[m_MaxBits])
	{
		//	Check if the code exist in the dictionary
		//	if not
		if (!m_dictionary->IsCodeExist(data))
		{
			//	Get the last used character into the decod buffer
			decodeString.Add((BYTE)character);
			//	Decode the existing prefix into a known string of data
			m_dictionary->GetBytesFromCode(&decodeString, prefix);
		}
		else
		{
			//	Decode the data into the decode buffer
			m_dictionary->GetBytesFromCode(&decodeString, data);
			//	Get the last letter inside the data, as the last used letter
			character = decodeString.GetAt(decodeString.GetSize() - 1);
		}

		//	Go over the decode buffer, from the end to the start,
		//	and write the information into the destination file
		counter = decodeString.GetSize();
		while (counter > 0)
		{
			writeData = (BYTE)decodeString.GetAt(--counter);
			destination.Write(&writeData, 1);

			//	To show a log in the view

			//	This commented addition was added as suggested by WREY from www.codeproject.com
			//logString.Format("Adding character code %d with know visualisation of: %s"
			//	, writeData, convertASCIIToText(writeData));
//			logString.Format("Adding byte %d to file.", writeData);
			Log(logString);
		}

		//	Clear the decode buffer
		decodeString.RemoveAll();

		//	Add the new combination into the dictionary
		m_dictionary->AddEntry(prefix, (BYTE)character);
		//	Calculate the new buffer size to read now
		CalculateBitSize(m_dictionary->GetMaxCode()+1);

		//	Set the new prefix to use
		prefix = data;
	}
	return TRUE;
}

BOOL CLZWCompression::Decompress(byte* source, byte* destination,  long sourceSize,  long * destinationSize)
{
	DWORD prefix = 0, data = 0;
	CString logString;
	CByteArray decodeString;
	BYTE writeData = 0, character = 0;
	int counter = 0;
	long sourceIndex = 0, destinationIndex = 0;

	Init();

	//	Create the dicionary (if not already created)
	if (m_dictionary == NULL)
	{
		CreateDictionary();
	}

	//	Get the first prefix information
	prefix = DecompressData(source,&sourceIndex,sourceSize);
	//	Save the prefix as the last used character (since we're writing it in the
	//	destination file)
	character = (BYTE)prefix;
	//	Write the prefix in the destination file (the first byte inside
	//	a LZW copressed file is always the first byte of the original file)
	//destination.Write(&prefix, 1);
	destination[destinationIndex] = character;
	destinationIndex++;

	//	While the recieve data is not the maximum bit data possible
	while ((data = DecompressData(source, &sourceIndex, sourceSize)) != m_MaxCode[m_MaxBits])
	{
		//	Check if the code exist in the dictionary
		//	if not
		if (!m_dictionary->IsCodeExist(data))
		{
			//	Get the last used character into the decod buffer
			decodeString.Add((BYTE)character);
			//	Decode the existing prefix into a known string of data
			m_dictionary->GetBytesFromCode(&decodeString, prefix);
		}
		else
		{
			//	Decode the data into the decode buffer
			m_dictionary->GetBytesFromCode(&decodeString, data);
			//	Get the last letter inside the data, as the last used letter
			character = decodeString.GetAt(decodeString.GetSize() - 1);
		}

		//	Go over the decode buffer, from the end to the start,
		//	and write the information into the destination file
		counter = decodeString.GetSize();
		while (counter > 0)
		{
			writeData = (BYTE)decodeString.GetAt(--counter);
			//destination.Write(&writeData, 1);
			destination[destinationIndex] = writeData;
			destinationIndex++;

			//	To show a log in the view

			//	This commented addition was added as suggested by WREY from www.codeproject.com
			//logString.Format("Adding character code %d with know visualisation of: %s"
			//	, writeData, convertASCIIToText(writeData));
//			logString.Format("Adding byte %d to file.", writeData);
			//Log(logString);
		}

		//	Clear the decode buffer
		decodeString.RemoveAll();

		//	Add the new combination into the dictionary
		m_dictionary->AddEntry(prefix, (BYTE)character);
		//	Calculate the new buffer size to read now
		CalculateBitSize(m_dictionary->GetMaxCode()+1);

		//	Set the new prefix to use
		prefix = data;
	}

	*destinationSize = destinationIndex;
	return TRUE;
}

DWORD CLZWCompression::DecompressData(byte* source, long* sourceIndex, long sourceLength)
{
	DWORD returnValue;
	BYTE readByte = 0;

	//	If the source file still contains information
	if (*sourceIndex < sourceLength)
	{
		//	check if the number of bits in the read buffer is >= 24
		while (m_TotalBits <= 24)
		{
			//	Read one byte
			readByte = source[*sourceIndex];
			(*sourceIndex)++;

			//	Add the byte to the read buffer
			m_SavedData |= (DWORD) readByte << (24 - m_TotalBits);
			//	Add byte to the bit counter
			m_TotalBits += 8;
		}
	}
	else
	{
		//	If there is no more data, and there are no more bits to read
		//	while the file is over, then return the maximum bit number
		//	to end the decompression process
		if (m_SavedData == 0 && m_TotalBits == 0)
			return m_MaxCode[m_MaxBits];
	}

	//	calculate the return information
	returnValue = m_SavedData >> (32 - m_MaxBits);
	//	Remove the returned information from the buffer
	m_SavedData <<= m_MaxBits;
	//	Remove the return information bit size from the bit counter
	m_TotalBits -= m_MaxBits;

	//	Return the data
	return returnValue;
}

DWORD CLZWCompression::DecompressData(CFile &source)
{
	DWORD returnValue;
	BYTE readByte = 0;

	//	If the source file still contains information
	if (source.GetPosition() < source.GetLength())
	{
		//	check if the number of bits in the read buffer is >= 24
		while (m_TotalBits <= 24)
		{
			//	Read one byte
			source.Read(&readByte, 1);

			//	Add the byte to the read buffer
			m_SavedData |= (DWORD) readByte << (24 - m_TotalBits);
			//	Add byte to the bit counter
			m_TotalBits += 8;
		}
	}
	else
	{
		//	If there is no more data, and there are no more bits to read
		//	while the file is over, then return the maximum bit number
		//	to end the decompression process
		if (m_SavedData == 0 && m_TotalBits == 0)
			return m_MaxCode[m_MaxBits];
	}

	//	calculate the return information
	returnValue = m_SavedData >> (32 - m_MaxBits);
	//	Remove the returned information from the buffer
	m_SavedData <<= m_MaxBits;
	//	Remove the return information bit size from the bit counter
	m_TotalBits -= m_MaxBits;

	//	Return the data
	return returnValue;
}

void CLZWCompression::CloseCompressedFile(byte *source, long* destIndex)
{
	//	Insert to the file the maximum number of bit (for signaling the end of the
	//	compression\decompression)
	CompressData(source, m_MaxCode[m_MaxBits],destIndex);
	//	Flash the rest of the file with 0
	CompressData(source, 0, destIndex);
}

void CLZWCompression::CloseCompressedFile(CFile &source)
{
	//	Insert to the file the maximum number of bit (for signaling the end of the
	//	compression\decompression)
	CompressData(source, m_MaxCode[m_MaxBits]);
	//	Flash the rest of the file with 0
	CompressData(source, 0);
}

void CLZWCompression::CalculateBitSize(DWORD value)
{
	//	Check the value of the parameter against the Maximum number possible
	//	and then returns the counter

	//	This can also be acheived by right shifting the value until we get 0
	//	and counting the number of times we doing it.

	BYTE counter;

	for (counter = 0; counter < 32; counter++)
	{
		if (value <= m_MaxCode[counter])
			break;
	}
	m_MaxBits = counter;

	//	Since the minimal number of bits we are using is 9 (256 is the begining of the dictionary), 
	//	then the minimal number of bits is check to return a 9 in case a lower value will be
	//	reached in the application
	if (m_MaxBits < 9)
		m_MaxBits = 9;
}

//	Added for using the log from the application
BOOL CLZWCompression::CompressWithLog(CFile &source, CFile &destination, CStringArray *pLog)
{
	p_Log = pLog;
	return Compress(source, destination);
}

BOOL CLZWCompression::DecompressWithLog(CFile &source, CFile &destination, CStringArray *pLog)
{
	p_Log = pLog;
	return Decompress(source, destination);
}

CString CLZWCompression::convertASCIIToText(BYTE ascii)
{
	//	Those are the values I know of.
	//	If you know others then just add then to this function.
	CString rValue;

	switch (ascii)
	{
	case 8:		//	Backspace
		rValue = "Backspace";
		break;
	case 9:		//	TAB
		rValue = "TAB";
		break;
	case 10:	//	Line Feed
		rValue = "Line Feed";
		break;
	case 12:	//	Form Feed
		rValue = "Form Feed";
		break;
	case 13:	//	Enter
		rValue = "Enter";
		break;
	case 32:	//	Space
		rValue = "Space";
		break;
	case 127:	//	Delete
		rValue = "Delete";
		break;
	default:
		rValue = "There is no visual character associated with this code";
		break;
	}

	//if ((ascii >= 33) && (ascii <= 126))
	//	rValue.Format("%c", ascii);

	return rValue;
}
