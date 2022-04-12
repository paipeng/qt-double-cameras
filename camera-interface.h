#ifndef CAMERAINTERFACE_H
#define CAMERAINTERFACE_H



class CameraInterface {
public:
    virtual ~CameraInterface() {}
    virtual void cameraState(int cameraId, int state) = 0;
};

#endif // CAMERAINTERFACE_H
