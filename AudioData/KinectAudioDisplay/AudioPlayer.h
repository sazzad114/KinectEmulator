#pragma once



using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// Summary for AudioPlayer
/// </summary>
public ref class AudioPlayer : public System::Windows::Forms::Form
{
public:
	AudioPlayer(void)
	{
		InitializeComponent();
		//
		//TODO: Add the constructor code here
		//
	}

protected:
	/// <summary>
	/// Clean up any resources being used.
	/// </summary>
	~AudioPlayer()
	{
		if (components)
		{
			delete components;
		}
	}

protected: 

protected: 

private:
	/// <summary>
	/// Required designer variable.
	/// </summary>
	System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Required method for Designer support - do not modify
	/// the contents of this method with the code editor.
	/// </summary>
	void InitializeComponent(void)
	{
		this->SuspendLayout();
		// 
		// AudioPlayer
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(284, 262);
		this->Name = L"AudioPlayer";
		this->Text = L"AudioPlayer";
		this->Load += gcnew System::EventHandler(this, &AudioPlayer::AudioPlayer_Load);
		this->ResumeLayout(false);

	}
#pragma endregion
private: System::Void AudioPlayer_Load(System::Object^  sender, System::EventArgs^  e) 
			{
				//this->mediaPlayer->URL = "out.wav";

			}
};

