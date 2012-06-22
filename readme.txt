;;;;;;;;;;;;;;;;;;;;;;;;
;;;;     readme     ;;;;
;;;;;;;;;;;;;;;;;;;;;;;;

Here you will have some projects showing how you can record data from kinect device. We also provide here some sample projects demostrating, how to use recorded data in other project and work without connecting the kinect device. In most cases, we reused the sample code "skeletalViewer" provided by microsoft. When you use the recorded data in your application, you should comment out the portion of initialization, shown in the sample projects(e.g. SampleVideoApplication's NuiImpl.cpp's Nui_init function).


;;;;;;;;;;;;;;;;;;;
;;;  VideoData  ;;;
;;;;;;;;;;;;;;;;;;;

VideoData folder contains two projects.
 	1.KinectVideoDataRecorder: this project records video data into a file named "video.dat" in the directory.
 	2.SampleVideoApplication: this project simply shows the video data recorded previously. Before running it, it is mandatory to put "video.dat" in 		directory(with the cpp's), which was recorded previously by "KinectVideoDataRecorder".


;;;;;;;;;;;;;;;;;;;;;;
;;;; SkeletonData ;;;;
;;;;;;;;;;;;;;;;;;;;;;

SkeletonData folder contains two projects.
 	1.KinectSkeletonDataRecorder: this project records skeleton data into a file named "skeleton.dat" in the directory.
 	
	2.SampleSkeletonApplication: this project simply shows the skeleton data recorded previously. Before running it, it is mandatory to put "skeleton.dat" in 	directory(with the cpp's), which was recorded previously by "KinectSkeletonDataRecorder".

	In all the sample applications, we produced psudo-events by invoking the event driven methods manually. But in actual cased those methods are invoked when an event 
	is generated(by either of the pull or push method).

;;;;;;;;;;;;;;;;;;
;;; AudiohData ;;;
;;;;;;;;;;;;;;;;;;

AudioData folder contains theree projects.
 	
	1.KinectAudioRecorder: This project records the audio data and store audio source, confidence level and beam angle.
 
	2.KinectAudioReader: This project display the audio data using KinectAudioRecorder. Build the project and get the KinectAudioDisplay.exe from 			KinectAudioDisplay described later.
 	
	3.KinectAudioDisplay: Sample application for showing the change of source and beam information with time using the previously stored data using KinectAudioRecorder. Build the project and move the .exe to the same directory as the KinectAudioReader and execute the KinectAudioDisplay.exe.













