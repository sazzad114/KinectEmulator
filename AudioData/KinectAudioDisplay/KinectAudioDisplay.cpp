// KinectAudioReader.cpp : main project file.


#include <Windows.h>
#include "stdafx.h"

#include "AudioData.h"
#include "AudioPlayer.h"

#using <System.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::IO;
using namespace System::Data;
using namespace System::Threading;
using namespace System::Collections::Generic;
using namespace AxWMPLib;
using namespace System::Windows::Forms;

//using namespace System::Media;


void synchAudiodata(List<AudioData^>^ ad);
List<AudioData^>^ readAudioData();


int main(array<System::String ^> ^args)
{
	//AxWMPLib::AxWindowsMediaPlayer^ mediaPlayer = gcnew AxWindowsMediaPlayer();	
	//KinectAudioReader::AudioPlayer^ ap = gcnew KinectAudioReader::AudioPlayer();
	
	//ap->mediaPlayer->URL = "out.wav";
	//Application::Run(ap);
	//Application::Run(gcnew AudioPlayer());
	List<AudioData^>^ ad = readAudioData();
	synchAudiodata(ad);
	//System::Windows::Forms^ form1 = gcnew System::Windows::Forms();
    return 0;
}

List<AudioData^>^ readAudioData()
{
	FileStream^ fs = gcnew FileStream("Data.dat", FileMode::Open);
	StreamReader^ sr = gcnew StreamReader(fs);

	String^ str;

	List<AudioData^>^ ad = gcnew List<AudioData^>();

	while((str=sr->ReadLine()) != nullptr)
	{
		String^ delim = " ";
		array<Char>^ delmiter = delim->ToCharArray();
		array<String^>^ arr = str->Split(delmiter);
		double ba=Convert::ToDouble(arr[0]);
		double ca = Convert::ToDouble(arr[1]);
		_int64 ts = Convert::ToInt64(arr[2]);			
		double sa = Convert::ToDouble(arr[3]);
		AudioData^ auu = gcnew AudioData(sa, ca, ba, -ts);
		ad->Add(auu);
	}
	return ad;
}

void synchAudiodata(List<AudioData^>^ ad)
{
	//while(this->mediaPlayer->Ctlcontrols->currentPosition < this->mediaPlayer->Ctlcontrols->currentItem->duration)
	//if(mediaPlayer->playState == WMPLib::WMPPlayState::wmppsPlaying
	//while(true)
			
	
	Console::WriteLine("Begin");
	//Console::WriteLine(Beam Angle = " + ad[i]->beamAngle)
	Thread::Sleep(TimeSpan::FromTicks(ad[0]->ticks));
	
	for(int i=0; i < ad->Count - 1; i++)
	{
		//TimeSpan^ diff = gcnew TimeSpan(100);
		/*DateTime curr = this->startAudio.AddTicks(this->ad[i]->ticks);

		DateTime back = DateTime::Now.AddMilliseconds(1);
		DateTime forwd = DateTime::Now.AddMilliseconds(1);*/

		//this->beamBox->Text = Convert::ToString(DateTime::curr, back));
		//this->confidenceBox->Text = Convert::ToString(DateTime::Subtract(curr, forwd));
		//if((DateTime::Compare(curr, back)>=0) && (DateTime::Compare(curr, forwd)<=0))
		//if(true)
				
		//this->beamBox->Text = Convert::ToString(this->ad[i]->beamAngle);
		//this->confidenceBox->Text =  Convert::ToString(this->ad[i]->confidenceSource);
		//this->sourceBox->Text = Convert::ToString(this->ad[i]->sourceAngle);
		//this->beamBox->Update();
		//this->confidenceBox->Update();
		//this->sourceBox->Update();
		Console::WriteLine("Beam Angle = " + ad[i]->beamAngle + " Source Angle = " + ad[i]->sourceAngle + " Confidence = " + ad[i]->confidenceSource);		

		Thread::Sleep(TimeSpan::FromTicks(ad[i+1]->ticks));
	}
	Thread::Sleep(TimeSpan::FromTicks(ad[ad->Count-1]->ticks));
	Console::WriteLine("Beam Angle = " + ad[ad->Count-1]->beamAngle);
			
				
			
}