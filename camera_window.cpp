#include "camera_window.h"
#include "ui_camera_window.h"


CameraWindow::CameraWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow), camera1(0, this), camera2(1, this), camera1AutoCapture(true), camera2AutoCapture(true)
{
    ui->setupUi(this);
    ui->camera2ComboBox->setCurrentIndex(1);
    initCameras();
    ui->statusbar->showMessage(tr("app_info"));


    QObject::connect(&arcFaceEngine, &ArcFaceEngine::updateFaceDecodeResult, this, &CameraWindow::updateFaceDecodeResult);
    arcFaceEngine.start();
    arcFaceEngine.setPriority(QThread::LowestPriority);


    QObject::connect(&barcodeDecoder, &BarcodeDecoder::updateBarcodeDecodeResult, this, &CameraWindow::updateBarcodeDecodeResult);
    barcodeDecoder.start();
    barcodeDecoder.setPriority(QThread::LowestPriority);
}

CameraWindow::~CameraWindow() {
    qDebug() << "~CameraWindow()";

    //arcFaceEngine.stop();
    arcFaceEngine.UnInitEngine();

    //barcodeDecoder.stop();
    delete ui;
}

void CameraWindow::initCameras() {
    qDebug() << "initCameras";
    const QList<QCameraInfo> availableCameras = Camera::getAvailableCamersInfos();

    int index = 0;
    for (const QCameraInfo &cameraInfo : availableCameras) {
        ui->camera1ComboBox->addItem(cameraInfo.description(), index);
        ui->camera2ComboBox->addItem(cameraInfo.description(), index);
        index ++;
    }

    //camera1.init(ui->camera1Viewfinder);
    //camera2.init(ui->camera2Viewfinder);

    //camera1.setCamera(getSelectedCameraInfo(0));
    //camera2.setCamera(getSelectedCameraInfo(0));



    QImage image;
    image.load("C:/Users/paipeng/Downloads/qrcode.jpg");
    qDebug() << "image: " << image.width() << "-" << image.height();


    qDebug() << "App path : " << qApp->applicationDirPath();
    QSettings settings(QString("C:/Users/paipeng/Documents/qt-double-cameras/setting.ini"), QSettings::IniFormat);
    QString appId = settings.value("x64_free/APPID", "default value if unset").toString(); // settings.value() returns QVariant
    qDebug() << "setting: " << appId;

    QString sdkKey = settings.value("x64_free/SDKKEY", "default value if unset").toString(); // settings.value() returns QVariant
    qDebug() << "setting: " << sdkKey;

    //arcFaceEngine = new ArcFaceEngine();

    MRESULT faceRes = arcFaceEngine.ActiveSDK((char*)(appId.toStdString().c_str()), (char*)(sdkKey.toStdString().c_str()), NULL);
    qDebug() << "ActiveSDK: " << faceRes;


    //获取激活文件信息
    ASF_ActiveFileInfo activeFileInfo = { 0 };
    arcFaceEngine.GetActiveFileInfo(activeFileInfo);

    if (faceRes == MOK) {
        faceRes = arcFaceEngine.InitEngine(ASF_DETECT_MODE_IMAGE);//Image
        qDebug() << "IMAGE模式下初始化结果: " << faceRes;

        //faceRes = arcFaceEngine->InitEngine(ASF_DETECT_MODE_VIDEO);//Video
        //qDebug() << "VIDEO模式下初始化结果: " << faceRes;
    }

    arcFaceEngine.SetLivenessThreshold(0.8f, 0.0f);

    //load QImage
    QImage registeredFaceImage;
    registeredFaceImage.load("C:/Users/paipeng/Pictures/paipeng2.jpeg");
    qDebug() << "image: " << registeredFaceImage.width() << "-" << registeredFaceImage.height() << "-" << registeredFaceImage.bitPlaneCount() << " " << registeredFaceImage.byteCount();

    arcFaceEngine.registerFace(registeredFaceImage);
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
    ui->camera2Label->setText(QString("Starting..."));
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
    barcodeDecoder.stop();
    arcFaceEngine.stop();
    event->accept();
}

void CameraWindow::cameraReadyForCapture(int cameraId, bool ready) {
    qDebug() << "cameraReadyForCapture: " << cameraId << " state: " << ready;

    if (ready) {
        if (cameraId == 0) {
            camera1.takeImage();
        } else {
            if (camera2AutoCapture) {
                camera2AutoCapture = false;
                camera2.takeImage();
            }
        }
    }
}

void CameraWindow::cameraState(int cameraId, int state) {
    qDebug() << "cameraState: " << cameraId << " state: " << state;
    if (state == 0) {
        if (cameraId == 0) {
            ui->camera1StartButton->setText(tr("start"));
        } else {
            ui->camera2StartButton->setText(tr("start"));
        }
        displayCapturedImage(cameraId);
    } else if (state == 1) {
        if (cameraId == 0) {
            ui->camera1StartButton->setText(tr("start"));
            camera1AutoCapture = true;
        } else {
            ui->camera2StartButton->setText(tr("start"));
            camera2AutoCapture = true;
        }
    } else if (state == 2) {
        if (cameraId == 0) {
            ui->camera1StartButton->setText(tr("stop"));
        } else {
            ui->camera2StartButton->setText(tr("stop"));
        }
        displayViewfinder(cameraId);
    }
}

void CameraWindow::processCapturedImage(int cameraId, const QImage& img) {
    //qDebug() << "processCapturedImage: " << cameraId << " img: " << img.width() << "-" << img.height();

    if (cameraId == 0) {
        barcodeDecoder.setImage(img);
    } else {
        arcFaceEngine.setImage(img);
    }
}

void CameraWindow::updateFaceDecodeResult(int decodeState, float score) {
    Q_UNUSED(decodeState);
    Q_UNUSED(score);
    qDebug() << "updateFaceDecodeResult: " << decodeState << " score: " << score;
    ui->camera2Viewfinder->updateData(decodeState, score, &(arcFaceEngine.faceData));
    if (decodeState == 0) {
        FaceData *faceData = ui->camera2Viewfinder->getFaceData();
#if 1
        QString showStr = QString("年龄:%1,性别:%2,活体:%3, score: %4").arg(
                    QString::number(faceData->ageInfo.ageArray[0]), QString::number(faceData->genderInfo.genderArray[0]),
                QString::number(faceData->liveNessInfo.isLive[0]), QString::number(score));
        ui->camera2Label->setText(showStr);
#endif
    } else {
        ui->camera2Label->setText(QString("not found -> error"));
    }

    camera2.takeImage();
}

void CameraWindow::updateBarcodeDecodeResult(int decodeState) {
    Q_UNUSED(decodeState);
    qDebug() << "updateBarcodeDecodeResult: " << decodeState;

    if (decodeState == 0) {
        for (auto&& result : barcodeDecoder.decodeResults) {
            qDebug() << "RESULT: " << result.text();
            QString text = QString::fromWCharArray(result.text().c_str());
            ui->camera1Label->setText(text);
        }
    } else {
        ui->camera1Label->setText(QString(""));
    }

}

void CameraWindow::displayViewfinder(int cameraId) {
    if (cameraId == 0) {
        ui->camera1StackedWidget->setCurrentIndex(0);
    } else {
        ui->camera2StackedWidget->setCurrentIndex(0);
    }
}

void CameraWindow::displayCapturedImage(int cameraId) {
    if (cameraId == 0) {
        ui->camera1StackedWidget->setCurrentIndex(1);
    } else {
        ui->camera2StackedWidget->setCurrentIndex(1);
    }
}
