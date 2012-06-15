#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace KincetAudioReader {

	/// <summary>
	/// Summary for AudioData
	/// </summary>
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


}
