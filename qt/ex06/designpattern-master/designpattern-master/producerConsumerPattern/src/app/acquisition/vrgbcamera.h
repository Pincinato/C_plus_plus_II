#ifndef VRGBCAMERA_H
#define VRGBCAMERA_H

#include <thread>
#include "dataBuffer.h"
#include "basecamera.h"

// Forward declarations
class ICamera;
class DataBufferPool;

class VrgbCamera final: public BaseCamera
{
public:
    VrgbCamera(ICamera* control, std::shared_ptr<DataBufferPool> dataPool);
    ~VrgbCamera()override;

    void startPlayData() override;
    void stop() override;
    bool isPlaying() override;
    void setPlayRate(int playRate) override;

private:
    void run() ;
    bool readImage(DataBufferPtr data);
    std::string m_tag;
    std::thread m_acquireThread;
    bool m_play;
    int m_playRate;
    size_t offset;
};

#endif // VRGBCAMERA_H
