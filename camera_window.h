#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include "camera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CameraWindow; }
QT_END_NAMESPACE

class CameraWindow : public QMainWindow, CameraInterface
{
    Q_OBJECT

public:
    CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();

private slots:
    void initCameras();
    void startCamera1();
    void startCamera2();
    const QCameraInfo getSelectedCameraInfo(int source);
    void camera1Changed(int index);
    void camera2Changed(int index);


protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    void cameraState(int cameraId, int state) override;
    void processCapturedImage(int cameraId, const QImage& img) override;

private:
    void displayViewfinder(int cameraId);
    void displayCapturedImage(int cameraId);

private:
    Ui::CameraWindow *ui;
    Camera camera1;
    Camera camera2;
};
#endif // CAMERAWINDOW_H
