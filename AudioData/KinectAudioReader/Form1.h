#pragma once

#include "AudioData.h"
//#include "AudioSynch.h"

#include <iostream>
using namespace std;

#using <System.Drawing.dll>
#using <System.dll>
#using <System.Windows.Forms.dll>
namespace KincetAudioReader {

	using namespace System;
	using namespace System::IO;
	using namespace System::ComponentModel;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Threading;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;
	using namespace System::Media;
	using namespace System::Runtime::InteropServices;
	using namespace System::Diagnostics;
	/// <summary>
	/// Summary for Form1
	/// </summary>

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:	
		//const int ATTACH_PARENT_PROCESS = -1;
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			

		}

		void synchAudiodata()
		{
			//while(this->mediaPlayer->Ctlcontrols->currentPosition < this->mediaPlayer->Ctlcontrols->currentItem->duration)
			//if(mediaPlayer->playState == WMPLib::WMPPlayState::wmppsPlaying
			//while(true)
			
			//Monitor::Enter(this);
			cout<<"Begin"<<endl;
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
				Console::WriteLine("Beam Angle = " + ad[i]->beamAngle);		

				Thread::Sleep(TimeSpan::FromTicks(ad[i+1]->ticks));
			}
			Thread::Sleep(TimeSpan::FromTicks(ad[ad->Count-1]->ticks));
			Console::WriteLine("Beam Angle = " + ad[ad->Count-1]->beamAngle);
				
			
			

}
		void readAudioData()
		{
			FileStream^ fs = gcnew FileStream("Data.dat", FileMode::Open);
			StreamReader^ sr = gcnew StreamReader(fs);

			String^ str;

			this->ad = gcnew List<AudioData^>();

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

		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		List<AudioData^>^ ad;
		DateTime startAudio;
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^  souceLabel;
	private: System::Windows::Forms::Label^  sourceLabel;
	private: System::Windows::Forms::Label^  beamLabel;
	private: System::Windows::Forms::Label^  confidenceLabel;
	private: System::Windows::Forms::TextBox^  beamBox;
	private: System::Windows::Forms::TextBox^  confidenceBox;
	private: System::Windows::Forms::TextBox^  sourceBox;
	private: AxWMPLib::AxWindowsMediaPlayer^  mediaPlayer;
	
			 

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->souceLabel = (gcnew System::Windows::Forms::Label());
			this->mediaPlayer = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->sourceLabel = (gcnew System::Windows::Forms::Label());
			this->beamLabel = (gcnew System::Windows::Forms::Label());
			this->confidenceLabel = (gcnew System::Windows::Forms::Label());
			this->beamBox = (gcnew System::Windows::Forms::TextBox());
			this->confidenceBox = (gcnew System::Windows::Forms::TextBox());
			this->sourceBox = (gcnew System::Windows::Forms::TextBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mediaPlayer))->BeginInit();
			this->SuspendLayout();
			// 
			// souceLabel
			// 
			this->souceLabel->AutoSize = true;
			this->souceLabel->Location = System::Drawing::Point(263, 28);
			this->souceLabel->Name = L"souceLabel";
			this->souceLabel->Size = System::Drawing::Size(0, 13);
			this->souceLabel->TabIndex = 0;
			// 
			// mediaPlayer
			// 
			this->mediaPlayer->Enabled = true;
			this->mediaPlayer->Location = System::Drawing::Point(24, 58);
			this->mediaPlayer->Name = L"mediaPlayer";
			this->mediaPlayer->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^  >(resources->GetObject(L"mediaPlayer.OcxState")));
			this->mediaPlayer->Size = System::Drawing::Size(222, 45);
			this->mediaPlayer->TabIndex = 1;
			// 
			// sourceLabel
			// 
			this->sourceLabel->AutoSize = true;
			this->sourceLabel->Location = System::Drawing::Point(21, 198);
			this->sourceLabel->Name = L"sourceLabel";
			this->sourceLabel->Size = System::Drawing::Size(71, 13);
			this->sourceLabel->TabIndex = 2;
			this->sourceLabel->Text = L"Source Angle";
			// 
			// beamLabel
			// 
			this->beamLabel->AutoSize = true;
			this->beamLabel->Location = System::Drawing::Point(21, 134);
			this->beamLabel->Name = L"beamLabel";
			this->beamLabel->Size = System::Drawing::Size(64, 13);
			this->beamLabel->TabIndex = 3;
			this->beamLabel->Text = L"Beam Angle";
			// 
			// confidenceLabel
			// 
			this->confidenceLabel->AutoSize = true;
			this->confidenceLabel->Location = System::Drawing::Point(21, 163);
			this->confidenceLabel->Name = L"confidenceLabel";
			this->confidenceLabel->Size = System::Drawing::Size(90, 13);
			this->confidenceLabel->TabIndex = 4;
			this->confidenceLabel->Text = L"Confidence Label";
			// 
			// beamBox
			// 
			this->beamBox->Location = System::Drawing::Point(117, 134);
			this->beamBox->Name = L"beamBox";
			this->beamBox->ReadOnly = true;
			this->beamBox->Size = System::Drawing::Size(129, 20);
			this->beamBox->TabIndex = 5;
			// 
			// confidenceBox
			// 
			this->confidenceBox->Location = System::Drawing::Point(117, 163);
			this->confidenceBox->Name = L"confidenceBox";
			this->confidenceBox->ReadOnly = true;
			this->confidenceBox->Size = System::Drawing::Size(129, 20);
			this->confidenceBox->TabIndex = 6;
			// 
			// sourceBox
			// 
			this->sourceBox->Location = System::Drawing::Point(117, 198);
			this->sourceBox->Name = L"sourceBox";
			this->sourceBox->ReadOnly = true;
			this->sourceBox->Size = System::Drawing::Size(129, 20);
			this->sourceBox->TabIndex = 7;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(407, 262);
			this->Controls->Add(this->sourceBox);
			this->Controls->Add(this->confidenceBox);
			this->Controls->Add(this->beamBox);
			this->Controls->Add(this->confidenceLabel);
			this->Controls->Add(this->beamLabel);
			this->Controls->Add(this->sourceLabel);
			this->Controls->Add(this->mediaPlayer);
			this->Controls->Add(this->souceLabel);
			this->Name = L"Form1";
			this->Text = L"KincetAudioReader";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->mediaPlayer))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
			 {
				//this->readAudioData();
				this->startAudio = DateTime::Now;
				//Thread^ t1 = gcnew Thread(gcnew ThreadStart(this, &Form1::synchAudiodata)); 
				//t1->Start();
				
				mediaPlayer->URL = "out.wav";
				Process::Start("KinectAudioDisplay.exe");
				//this->synchAudiodata();
				//mediaPlayer->Ctlcontrols->pause();
				//double length = mediaPlayer->Ctlcontrols->currentItem->duration;
				//mediaPlayer->Ctlcontrols->play();
				//this->synchAudiodata();
				cout<<"Hellooooo"<<endl;
			 }
	};

}

