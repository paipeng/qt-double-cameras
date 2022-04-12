#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>
#include "camera.h"

QT_BEGIN_NAMESPACE
namespace Ui { class CameraWindow; }
QT_END_NAMESPACE

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();

private slots:
    void initCameras();
    void startCamera1();
    void startCamera2();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::CameraWindow *ui;
    Camera camera1;
    Camera camera2;
};
#endif // CAMERAWINDOW_H
