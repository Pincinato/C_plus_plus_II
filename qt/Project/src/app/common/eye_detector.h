#ifndef EYE_DETECTOR_H
#define EYE_DETECTOR_H

#include "icamera.h"
#include "camera.h"
#include "ieye_detector.h"

class Eye_detector : public Icamera
{
public:
    Eye_detector(Ieye_detector *Owner);
    ~Eye_detector() override;
    void setData(Mat &frame) override;
    void setStatus(string cameraStatus) override;
    void start();
    void stop();

private:
    string face_cascade_name = "haarcascade_frontalface_alt.xml";
    string eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    unique_ptr<Camera> m_camera;
    string m_cameraStatus;
    unique_ptr<Ieye_detector> m_Owner;

};

#endif // EYE_DETECTOR_H
