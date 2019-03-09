/****************************************************************************
** Copyright (c) 2018 University of Bern & Bern University of Applied Science
** Project: Eye tracking
** Done by: Pratick Arnold , Modified by : Thiago Pincinato
** Contact:  Thiago Henrique Pincianto ( thiago.pincinato@bfh.ch )
*****************************************************************************/

#ifndef CONTROL_H
#define CONTROL_H

#include <memory>
#include <iostream>
#include <string>
#include <QWidget>
#include "icamera.h"
#include <QTimer>
#include <deque>

using namespace cv;
using namespace std;

// Forward declarations
class VCamera;
class DataBufferPool;
class EyeAnalyser;
class EyeDetector;
class BaseCamera;
class BaseCameraFactory;
class IControl;

/*!
 * \brief The Control class     Class responsible to the core's logic of the program
 */
class Control :  public QWidget , ICamera
{

public:
    /*!
     * \brief Control           Constructor class, initialize variabels via initializer list
     *                          Clear vectors eyes and faces. It also calls init function
     * \param parent            Icontrol pointer
     */
    Control(IControl *parent);
    ~Control() override;

    /*!
     * \brief displayMsg        calls displayMsg of Icontrol Class, using input parameter
     *                          as parameter for the Icontrol displayMsg function.
     * \param tag               Name of the class/object
     * \param msg               Message to be displayed
     */
    void displayMsg(const string &tag, const string &msg) override;

    /*!
     * \brief setData           Update/transmits the DataBufferPrt to the Icontrol object
     * \param dataJunk          Pointer that contain the frame,Qimaga, gray frame
     */
    void setData(DataBufferPtr dataJunk) override;

    /*!
     * \brief init              Respoisble to init all unique pointer and clear deques
     */
    void init();

    /*!
     * \brief startPlaying      also calls init, and start camera object
     */
    void startPlaying();

    /*!
     * \brief stopPlaying       stop camera object
     */
    void stopPlaying();

    /*!
     * \brief isPlaying         return the actual state of the camera object.
     * \return                  true if camera is playing and false if not.
     */
    bool isPlaying() const;

    /*!
     * \brief startDetecting       enable abilitiy to detect and draw eyes of camera object
    */
    void startDetecting();

    /*!
     * \brief stopDetecting       disable abilitiy to detect and draw eyes of camera object
     */
    void stopDetecting();

    /*!
     * \brief isDetecting         return the actual state of the control object.
     * \return                  true if control is able to detect face and eyes
     *                          as well as draw them; false if not.
     */
    bool isDetecting() const;

    /*!
     * \brief setPlayRate       receive the play rate and transmits to the camera object
     * \param playRate          const int & that is used as parameter to camera play Rate function
     */
   void setPlayRate(const int &playRate);

    /*!
     * \brief getEyes           Localize the position of the eyes.
     * \param data              DataBufferPtr to the actual frame
     * \return                  true if the eyes position have been detected, false otherwise
     */
    bool getEyes(const DataBufferPtr &data);

    /*!
     * \brief setEyesInFrame    draws a circle around the eyes
     * \param data              DAtaBuffer in which a circle are drawn
     * \return                  true if the circles were drawn, false otherwise
     */
    bool setEyesInFrame(DataBufferPtr &data);

    /*!
     * \brief setFaceInFrame    draws a retangle that surround the face .
     * \param data              dataBuffer in which the retangle is drawn
     * \return                  true if the retangle was drawn, false otherwise
     */
    bool setFaceInFrame(DataBufferPtr &data);

    /*!
     * \brief setCamera         Set varible m_cameraOption
     * \param option
     */
    void setCamera(const string &option);

    /*!
     * \brief setEyesCenter     draws a point in the center of the each eye
     * \param data              dataBuffer in which the centers were drawn
     * \return                  true if the centers were drawn, flase otherwise
     */
    bool setEyesCenter(DataBufferPtr &data);

    /*!
     * \brief getDirection      gets the direction of the face
     * \param calibrationLeft   const Point of the left eye acquired during calibration
     * \param calibrationRight  const Point of the right eye acquired during calibration
     * \return                  short indicating the direction
     *                          1- center
     *                          2- right
     *                          3- up
     *                          4- left
     *                          5- down
     */
    short getDirection(const Point &calibrationLeft,const Point &calibrationRight);

    /*!
     * \brief clearVectors  clear vectors
     */
    void clearVectors();

    /*!
     * \brief setSensibility    set sensibility value
     * \param newValue          value to be attribuated to sensibility
     */
    void setSensibility(const int &newValue);




private:
    /*!
     * \brief m_widget          pointer to Icontrol
     */
    IControl* m_widget;

    /*!
     * \brief m_height          height of QImage
     */
    uint m_height;

    /*!
     * \brief m_widht           widht of QImage
     */
    uint m_widht;

    /*!
     * \brief cameraOption      string that contains the option of camera
     */
    string m_cameraOption;

    /*!
     * \brief m_player          unique pointer to BaseCamera
     */
    unique_ptr<BaseCamera> m_player;

    /*!
     * \brief camera_factory    unique pointer to BaseCameraFactory
     */
    unique_ptr<BaseCameraFactory> m_camera_factory;

    /*!
     * \brief m_tracking        unique pointer to EyeDetector
     */
    unique_ptr<EyeDetector> m_tracking;

    /*!
     * \brief m_detecting      bool to indicate states of detection ability
     */
    bool m_detecting;

    /*!
     * \brief m_dataPool        shared pointer carring frames
     */
    shared_ptr<DataBufferPool> m_dataPool;

    /*!
     * \brief m_ScanUpdateRateTimer unique pointer to Qtimer
     */
    unique_ptr<QTimer> m_ScanUpdateRateTimer;

    /*!
     * \brief m_analyser    pointer to EyeAnalyser
     */
    unique_ptr<EyeAnalyser> m_analyser;

    /*!
     * \brief m_eyes    vector that contains the last rect of the eyes
     */
    std::vector<Rect> m_eyes;

    /*!
     * \brief m_faces           vector of faces
     */
    vector<Rect> m_faces;

    /*!
     * \brief m_centerEyeLeft   point of center left eye
     */
    Point m_centerEyeLeft;

    /*!
     * \brief m_centerEyeRight  point of center right eye
     */
    Point m_centerEyeRight;

    /*!
     * \brief m_EyeRight        deque of right eye center points
     */
    deque<cv::Point > m_EyeRight;

    /*!
     * \brief m_EyeLeft         deque of left eye center points
     */
    deque<cv::Point > m_EyeLeft;
};
#endif // CONTROL_H
