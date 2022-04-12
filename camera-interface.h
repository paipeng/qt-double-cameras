#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H


#include <QPixmap>

class CameraInterface {
public:
    virtual ~CameraInterface() {}
    virtual void cameraState(int cameraId, int state) = 0;
    virtual void processCapturedImage(int cameraId, const QImage& img) = 0;
};

#endif // CAMERAINTERFACE_H
