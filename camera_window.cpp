#include "camera_window.h"
#include "ui_camera_window.h"

CameraWindow::CameraWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::initCameras() {
    camera1.init("", ui->camera1Viewfinder);
    camera2.init("", ui->camera2Viewfinder);
}


void CameraWindow::startCamera1() {
    camera1.startCamera();
}

void CameraWindow::startCamera2() {
    camera2.startCamera();

}

void CameraWindow::keyPressEvent(QKeyEvent *event) {

}

void CameraWindow::keyReleaseEvent(QKeyEvent *event) {

}

void CameraWindow::closeEvent(QCloseEvent *event) {

}
