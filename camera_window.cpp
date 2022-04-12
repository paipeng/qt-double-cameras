#include "camera_window.h"
#include "ui_camera_window.h"

CameraWindow::CameraWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow)
{
    ui->setupUi(this);
    initCameras();
}

CameraWindow::~CameraWindow()
{
    delete ui;
}

void CameraWindow::initCameras() {
    const QList<QCameraInfo> availableCameras = Camera::getAvailableCamersInfos();

    int index = 0;
    for (const QCameraInfo &cameraInfo : availableCameras) {
        ui->camera1ComboBox->addItem(cameraInfo.description(), index);
        ui->camera2ComboBox->addItem(cameraInfo.description(), index);

        index ++;
    }

    camera1.init(ui->camera1Viewfinder);
    camera2.init(ui->camera2Viewfinder);
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
}

void CameraWindow::startCamera1() {
    qDebug() << "startCamera1";
    camera1.setCamera(getSelectedCameraInfo(0));
    camera1.startCamera();
}

void CameraWindow::startCamera2() {
    qDebug() << "startCamera2";
    camera2.setCamera(getSelectedCameraInfo(1));
    camera2.startCamera();

}

void CameraWindow::keyPressEvent(QKeyEvent *event) {

}

void CameraWindow::keyReleaseEvent(QKeyEvent *event) {

}

void CameraWindow::closeEvent(QCloseEvent *event) {
    qDebug("closeEvent");
    event->accept();
}
