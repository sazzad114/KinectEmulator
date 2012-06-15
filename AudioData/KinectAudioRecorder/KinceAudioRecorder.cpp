// KinceAudioRecorder.cpp : main project file.

#include "stdafx.h"

using namespace System;
using namespace System::IO;
using namespace System::Text;
using namespace System::Threading;
using namespace Microsoft::Research::Kinect::Audio;

struct WAVEFORMATEX
{
public: 
	unsigned short wFormatTag;
	unsigned short nChannels;
	unsigned int nSamplesPerSec;
	unsigned int nAvgBytesPerSec;
    unsigned short nBlockAlign;
    unsigned short wBitsPerSample;
    unsigned short cbSize;

	WAVEFORMATEX()
	{
		wFormatTag = 1,
		nChannels = 1,
		nSamplesPerSec = 16000,
		nAvgBytesPerSec = 32000,
		nBlockAlign = 2,
		wBitsPerSample = 16,
		cbSize = 0;

	}

};


[ Serializable ]
ref class AudioData
{
public:
	double sourceAngle;
	double beamAngle;
	double confidenceSource;
	_int64 ticks;

	AudioData(double sa, double cs, double ba, _int64 t)
	{
		this->beamAngle = ba;
		this->confidenceSource = cs;
		this->ticks = t;
		this->sourceAngle = sa;

	}
	String^ toString()
	{
		return this->beamAngle + " " + this->confidenceSource + " " + this->ticks + " " + this->sourceAngle;
	}

};

ref class AudioRecorderKinect
{
public:
	void writeString(MemoryStream^ stream, String^ s);
	void writeWaveHeader(Stream^ stream, int dataLength);
	void source_BeamChanged(System::Object^  sender, BeamChangedEventArgs^ e);
	void recordAudio();
	bool objectToFile(AudioData ^_Object, System::String ^_FileName);
protected:
private:
	double sourceAngle;
	double beamAngle;
	double confidenceSource;
	DateTime begin;
	String^ dataFile;
	FileStream^ fs;
	StreamWriter^ sw;

};

bool AudioRecorderKinect::objectToFile(AudioData ^_Object, System::String ^_FileName)
{
	try
	{	
		MemoryStream ^_MemoryStream = gcnew MemoryStream();
		System::Runtime::Serialization::Formatters::Binary::BinaryFormatter ^_BinaryFormatter = gcnew System::Runtime::Serialization::Formatters::Binary::BinaryFormatter();
		_BinaryFormatter->Serialize(_MemoryStream, _Object);
		array<System::Byte> ^_ByteArray = _MemoryStream->ToArray();
		System::IO::FileStream ^_FileStream = gcnew System::IO::FileStream(_FileName, System::IO::FileMode::Create, System::IO::FileAccess::Write);
	
		_FileStream->Write(_ByteArray, 0, _ByteArray->Length);
	    _FileStream->Close();
	    _MemoryStream->Close();
		delete _MemoryStream;
		_MemoryStream = nullptr;
		_ByteArray = nullptr;
		return true;
	}
	catch (Exception ^_Exception)
	{
		Console::WriteLine("\nError has occurred " + _Exception->Message);
		return false;

	}
	
	
}

void AudioRecorderKinect::writeString(MemoryStream^ stream, String^ s)
{
	Encoding^ ascii = Encoding::ASCII;
	array<Byte>^bytes = ascii->GetBytes(s);
	//Debug->Assert((bytes->Length==s->Length);
	stream->Write(bytes, 0, bytes->Length);

}

void AudioRecorderKinect::writeWaveHeader(Stream^ stream, int dataLength)
{

	MemoryStream^ memStream = gcnew MemoryStream(64);
	this->fs = gcnew FileStream("Data.dat", FileMode::Create);
	this->sw=gcnew StreamWriter(fs);
	int cbFormat = 18;
	WAVEFORMATEX format = WAVEFORMATEX();
		
	BinaryWriter^ bw = gcnew BinaryWriter(memStream);
	writeString(memStream, "RIFF");
	bw->Write(dataLength + cbFormat + 4);
	writeString(memStream, "WAVE");
	writeString(memStream, "fmt ");
	bw->Write(cbFormat);

	bw->Write(format.wFormatTag);
	bw->Write(format.nChannels);
	bw->Write(format.nSamplesPerSec);
	bw->Write(format.nAvgBytesPerSec);
	bw->Write(format.nBlockAlign);
	bw->Write(format.wBitsPerSample);
	bw->Write(format.cbSize);

	writeString(memStream, "data");
	bw->Write(dataLength);
	memStream->WriteTo(stream);
}

void AudioRecorderKinect::source_BeamChanged(System::Object^ sender, BeamChangedEventArgs^ e)
{
	this->beamAngle = e->Angle;
	TimeSpan ts = begin - DateTime::Now;
	this->begin = DateTime::Now;
	Console::WriteLine("\nBeam direction changed (radians): " + e->Angle);
	//AudioData^ ad = gcnew AudioData(this->sourceAngle, this->confidenceSource, this->beamAngle, ts);
	//this->objectToFile(ad, this->dataFile);
	AudioData^ au = gcnew AudioData(this->sourceAngle, this->confidenceSource, this->beamAngle, ts.Ticks);
	sw->WriteLine(au->toString());
}

void AudioRecorderKinect::recordAudio()
{
	this->dataFile = "Data.dat";
	String^ outputFileName = "out.wav";
	const int recordTime = 20;
	const int recordLength = recordTime * 2 * 16000;
	array<Byte>^ buffer = gcnew array<Byte>(4096);

	Thread::CurrentThread->Priority = ThreadPriority::Highest;

	KinectAudioSource^ source = gcnew KinectAudioSource();
	source->SystemMode = SystemMode::OptibeamArrayOnly;
	source->BeamChanged += gcnew System::EventHandler<BeamChangedEventArgs^>(this, &AudioRecorderKinect::source_BeamChanged);

	FileStream^ fileStream = gcnew FileStream(outputFileName, FileMode::Create);
	this->writeWaveHeader(fileStream, recordLength);

	Console::WriteLine("Recording for " + recordTime + "seconds");
	//double prevSAngle = 0.0;
	double currSAngle = 0.0;
	//prevSAngle = source->SoundSourcePosition;
	currSAngle = source->SoundSourcePosition;
	Stream^ audioStream  = source->Start();	
	int count, totalCount = 0;
	this->begin = DateTime::Now;
	while((count=audioStream->Read(buffer, 0, buffer->Length)) && (totalCount < recordLength))
	{
		fileStream->Write(buffer, 0, count);
		totalCount += count;
		//currSAngle = source->SoundSourcePosition;
		if(source->SoundSourcePositionConfidence)
		{
			double diff = currSAngle - source->SoundSourcePosition;
			if(diff)
			{
				this->confidenceSource = source->SoundSourcePositionConfidence;
				TimeSpan ts = this->begin - DateTime::Now;
				this->begin = DateTime::Now;
				this->sourceAngle = currSAngle = source->SoundSourcePosition;
				//this->objectToFile(gcnew AudioData(this->sourceAngle, this->confidenceSource, this->beamAngle, ts), this->dataFile);
				AudioData^ au = gcnew AudioData(this->sourceAngle, this->confidenceSource, this->beamAngle, ts.Ticks);
				sw->WriteLine(au->toString());
				Console::WriteLine("\nSource Angle " + currSAngle); 				
			}
		}
	}
	sw->Close();
	fs->Close();
	Console::WriteLine("Recording saved to" + outputFileName);

}


int main(array<System::String ^> ^args)
{
  AudioRecorderKinect^ ark = gcnew AudioRecorderKinect();
  ark->recordAudio();

}
