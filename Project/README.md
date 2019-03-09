# ProjectCplusplusII

This repository is destined to the final Project of the C++ II subject, UNIBE- Biomedical Engineering. 
My project aims to detect the eyes' position ,and then, by using those positions, to idetify where the user is looking at.   
Part of the project was based on the Producer Consumer Exercise of the C++ II course, which can be found in:

    https://gitlab.ti.bfh.ch/BMECPPII_2018/designpattern


## Requirements

In order to have a compilable project, Qtcreator and openCV must be installed. That can be done by following the tutorials:

Windowns user (tested!):

    https://wiki.qt.io/How_to_setup_Qt_and_openCV_on_Windows 
    
Linux user (not tested!):  

    http://xrong.org/misc/install-qt-opencv-ubuntu/ 
    
Once you have opencv integrated in your qtcretor, please check if you fulfill the following requirements:

1. Have at least one camera installed in your computer. Your built-in WebCam is enough.
2. Certify to have enough illumination, during utilisation of the application. The application will offer better results if there is a focus light in the face's region

## Actual state of the project

By now, the application is able to detect eyes' positions, either by a Webcam or USB Camera. With those positions, the center of the left eye and the center of the right eye are extracted.
In order to analyse the position of the eyes, a reference value need to be known. Because of that, a calibration must be done in the calibration widget.
The choice of which camera the user will use is done in the Eye detection widget. 
In the widget Action the position of eyes are compared with the calibration points , and then the direction of head is computed by the EyeAnalyser object.
The Eye detection widget detected the camera avaible and display on the Combox. The camera are detected in runnig time.
For reason of robusticity, the user can remove the usb camear any time and the application will update,  without crashing.


## Issues 

1. Opencv function cvtColor crashes the program when running in a thread, Gui main thread is the only execption. So far, it seems to be caused due to the fact that cvtColor is a openCv multhread function !??  Solution: Implemenation of such funtions by hand.
2. Eye and eye's center detection depends on ilumination, and are not 100% accurary. Is a filter need to enhance results?? Which one??.  Solution : A median filter is applied in a deque of 100 elements
3. When looking down, center of the eye is nearly similar with the reference,difference is not distinguible. How could I differenciate them ? Solution: the median filter help to avoid such mistake.
4. Iris detection is very poor in resoluion and not stable at all. Even after several attempts with different methods, I was not able to used the pupil detection to detected where the user is looking at. Solution: Detection of the eyes and compute distance based on actul position and calibration, without iris detection.
5. Due to problem when using opencv in a own thread, such classes as Eye Analyse and Eye Detection are running in the GUI thread, which reduce application efficiency.

The problem 1 was detected when such a function was used in the VCamera class , .cpp file, function readImage.


## Future developpement 

1. The main future developpement could be the detection of the iris , which would require better camera, even IR camera or a placement closer to the eye.
2. EyeAnalyser could run in an own thread.$
3. Solve problem with cv funtions that crashes when running in an own thread. 
