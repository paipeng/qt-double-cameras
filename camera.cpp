#include "camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

int Camera::init(QCameraViewfinder *surface) {
#if 0
    qDebug() << "init: " << cameraName;
    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();
    QCameraInfo defaultCameraInfo;
    for (const QCameraInfo &cameraInfo : availableCameras) {
        //QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
        //videoDeviceAction->setCheckable(true);
        //videoDeviceAction->setData(QVariant::fromValue(cameraInfo));

        if (cameraInfo.description() == cameraName) {
            qDebug() << cameraName << " found!";
            defaultCameraInfo = cameraInfo;
        }
        //if (cameraInfo == QCameraInfo::defaultCamera())
            //videoDeviceAction->setChecked(true);
        //ui->menuDevices->addAction(videoDeviceAction);
    }

    if (defaultCameraInfo.isNull()) {
        defaultCameraInfo = QCameraInfo::defaultCamera();
        qDebug("set to use default camera: %s", (const char*)(defaultCameraInfo.description().data_ptr()) );
    }
#endif
    this->surface = surface;

    //setCamera(defaultCameraInfo);
}

void Camera::setCamera(const QCameraInfo &cameraInfo) {
    qDebug() << "setCamera: " << cameraInfo.description();
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &Camera::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &Camera::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &Camera::updateRecorderState);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &Camera::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &Camera::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

    m_camera->setViewfinder(surface);

    updateCameraState(m_camera->state());
    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &Camera::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &Camera::processCapturedImage);
    //connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &Camera::imageSaved);
    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
            this, &Camera::displayCaptureError);

    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
            this, &Camera::updateLockStatus);

    //ui->captureWidget->setTabEnabled(0, true);
    //ui->captureWidget->setTabEnabled(1, true);

    updateCaptureMode();
}

const QList<QCameraInfo> Camera::getAvailableCamersInfos() {
    return QCameraInfo::availableCameras();
}



void Camera::takeImage() {

}

void Camera::startCamera() {
    qDebug("startCamera: %d", m_isCameraStart);
    if (m_isCameraStart) {
        qDebug() << "stop";
        m_camera->stop();

        displayCapturedImage();
    } else {
        qDebug() << "start";
        m_camera->start();

        displayViewfinder();
    }
    m_isCameraStart = !m_isCameraStart;
    qDebug("startCamera end: %d", m_isCameraStart);
}

void Camera::stopCamera() {
    qDebug() << "stopCamera camera state: " << m_camera->status();
    m_camera->stop();
}

void Camera::updateCaptureMode() {
    //int tabIndex = ui->captureWidget->currentIndex();
    //QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;

    if (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage))
        m_camera->setCaptureMode(QCamera::CaptureStillImage);
}

void Camera::updateCameraState(QCamera::State state) {
    switch (state) {
    case QCamera::ActiveState:

        break;
    case QCamera::UnloadedState:
    case QCamera::LoadedState:
        break;

    }
}

void Camera::updateRecorderState(QMediaRecorder::State state) {

}

void Camera::setExposureCompensation(int index) {
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void Camera::displayRecorderError() {
    //QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void Camera::displayCameraError() {
    //QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void Camera::updateCameraDevice(QAction *action) {
    //setCamera(qvariant_cast<QCameraInfo>(action->data()));
}

void Camera::displayViewfinder() {
}

void Camera::displayCapturedImage() {
}

void Camera::readyForCapture(bool ready) {
    qDebug("readyForCapture: %d", ready);
    if (ready) {
        m_isCapturingImage = true;
        m_imageCapture->capture();
    } else {
        m_isCapturingImage = false;
    }
}

void Camera::imageSaved(int id, const QString &fileName) {
    Q_UNUSED(id);
    qDebug("imageSaved: %s", (const char*)(fileName.data()));
    m_isCapturingImage = false;
}


void Camera::processCapturedImage(int requestId, const QImage& img) {
    Q_UNUSED(requestId);
    qDebug("processCapturedImage imageFormat: %d", img.format());
}


void Camera::updateLockStatus(QCamera::LockStatus status, QCamera::LockChangeReason reason) {
    QColor indicationColor = Qt::black;

    switch (status) {
    case QCamera::Searching:
        indicationColor = Qt::yellow;
        //ui->statusbar->showMessage(tr("Focusing..."));
        break;
    case QCamera::Locked:
        indicationColor = Qt::darkGreen;
        //ui->statusbar->showMessage(tr("Focused"), 2000);
        break;
    case QCamera::Unlocked:
        indicationColor = reason == QCamera::LockFailed ? Qt::red : Qt::black;
        //if (reason == QCamera::LockFailed)
        //    ui->statusbar->showMessage(tr("Focus Failed"), 2000);
        break;
    }
}


void Camera::updateRecordTime() {
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
    //ui->statusbar->showMessage(str);
}


void Camera::displayCaptureError(int id, const QCameraImageCapture::Error error, const QString &errorString) {
    Q_UNUSED(id);
    Q_UNUSED(error);
    //QMessageBox::warning(this, tr("Image Capture Error"), errorString);
    //m_isCapturingImage = false;
}
