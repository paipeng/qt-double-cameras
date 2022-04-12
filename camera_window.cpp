#include "camera_window.h"
#include "ui_camera_window.h"

CameraWindow::CameraWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
    ui->camera2ComboBox->setCurrentIndex(1);
    initCameras();
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::initCameras() {
    qDebug() << "initCameras";
    const QList<QCameraInfo> availableCameras = Camera::getAvailableCamersInfos();

    ui->camera1ComboBox->addItem(availableCameras.at(0).description(), 0);
    ui->camera2ComboBox->addItem(availableCameras.at(1).description(), 1);

    //camera1.init(ui->camera1Viewfinder);
    //camera2.init(ui->camera2Viewfinder);

    //camera1.setCamera(getSelectedCameraInfo(0));
    //camera2.setCamera(getSelectedCameraInfo(0));

}

const QCameraInfo CameraWindow::getSelectedCameraInfo(int source) {
    qDebug() << "getSelectedCameraInfo: " << source;
    const QList<QCameraInfo> availableCameras = Camera::getAvailableCamersInfos();

    QComboBox* comboBox = NULL;
    if (source == 0) {
        comboBox = ui->camera1ComboBox;
    } else {
        comboBox = ui->camera2ComboBox;
    }

    int index = 0;
    for (const QCameraInfo &cameraInfo : availableCameras) {
        if (index== comboBox->currentIndex()) {
            qDebug() << "selected camera found: " << cameraInfo.description();
            return cameraInfo;
        }
        index++;
    }
    QCameraInfo defaultCameraInfo;
    return defaultCameraInfo;
}

void CameraWindow::startCamera1() {
    qDebug() << "startCamera1";
    camera1.startCamera();
}

void CameraWindow::startCamera2() {
    qDebug() << "startCamera2";
    camera2.startCamera();

}

void CameraWindow::camera1Changed(int index) {
    qDebug() << "camera1Changed: " << index;
    camera1.setCamera(getSelectedCameraInfo(0), ui->camera1Viewfinder);
}

void CameraWindow::camera2Changed(int index) {
    qDebug() << "camera2Changed: " << index;
    camera2.setCamera(getSelectedCameraInfo(1), ui->camera2Viewfinder);
}

void CameraWindow::keyPressEvent(QKeyEvent *event) {

}

void CameraWindow::keyReleaseEvent(QKeyEvent *event) {

}

void CameraWindow::closeEvent(QCloseEvent *event) {
    qDebug("closeEvent");
    event->accept();
}
