#include "camera_window.h"
#include "ui_camera_window.h"

#include "ReadBarcode.h"
#include "TextUtfEncoding.h"
#include "GTIN.h"



#include "opencv/cv.h"
#include "opencv/highgui.h"


#define FACE_FEATURE_SIZE 1032

using namespace ZXing;
using namespace TextUtfEncoding;


#if 1
IplImage* QImage2IplImage(QImage *qimg) {
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg->width(), qimg->height()), IPL_DEPTH_8U, 4);
    imgHeader->imageData = (char*) qimg->bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg->byteCount());
    memcpy(newdata, qimg->bits(), qimg->byteCount());
    imgHeader->imageData = (char*) newdata;
    //cvClo
    return imgHeader;
}

QImage*  IplImage2QImage(IplImage *iplImg) {
    int h = iplImg->height;
    int w = iplImg->width;
    int channels = iplImg->nChannels;
    QImage *qimg = new QImage(w, h, QImage::Format_ARGB32);
    char *data = iplImg->imageData;

    for (int y = 0; y < h; y++, data += iplImg->widthStep) {
        for (int x = 0; x < w; x++) {
            char r, g, b, a = 0;
            if (channels == 1) {
                r = data[x * channels];
                g = data[x * channels];
                b = data[x * channels];
            } else if (channels == 3 || channels == 4) {
                r = data[x * channels + 2];
                g = data[x * channels + 1];
                b = data[x * channels];
            }

            if (channels == 4) {
                a = data[x * channels + 3];
                qimg->setPixel(x, y, qRgba(r, g, b, a));
            } else {
                qimg->setPixel(x, y, qRgb(r, g, b));
            }
        }
    }
    return qimg;
}
#endif


CameraWindow::CameraWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CameraWindow), camera1(0, this), camera2(1, this)
{
    ui->setupUi(this);
    ui->camera2ComboBox->setCurrentIndex(1);
    initCameras();
    ui->statusbar->showMessage(tr("app_info"));
}

CameraWindow::~CameraWindow()
{
    arcFaceEngine->UnInitEngine();
    delete arcFaceEngine;
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

    DecodeHints hints;
    hints.setEanAddOnSymbol(EanAddOnSymbol::Read);


    QImage image;
    image.load("C:/Users/paipeng/Downloads/qrcode.jpg");
    qDebug() << "image: " << image.width() << "-" << image.height();

    ImageView imageView{image.bits(), image.width(), image.height(), ImageFormat::RGBX};
    auto results = ReadBarcodes(imageView, hints);

    // if we did not find anything, insert a dummy to produce some output for each file
    if (results.empty())
        results.emplace_back(DecodeStatus::NotFound);

    for (auto&& result : results) {

        qDebug() << "RESULT: " << result.text();

    }


    qDebug() << "App path : " << qApp->applicationDirPath();
    QSettings settings(QString("C:/Users/paipeng/Documents/qt-double-cameras/setting.ini"), QSettings::IniFormat);
    QString appId = settings.value("x64_free/APPID", "default value if unset").toString(); // settings.value() returns QVariant
    qDebug() << "setting: " << appId;

    QString sdkKey = settings.value("x64_free/SDKKEY", "default value if unset").toString(); // settings.value() returns QVariant
    qDebug() << "setting: " << sdkKey;

    arcFaceEngine = new ArcFaceEngine();

    MRESULT faceRes = arcFaceEngine->ActiveSDK((char*)(appId.toStdString().c_str()), (char*)(sdkKey.toStdString().c_str()), NULL);
    qDebug() << "ActiveSDK: " << faceRes;


    //获取激活文件信息
    ASF_ActiveFileInfo activeFileInfo = { 0 };
    arcFaceEngine->GetActiveFileInfo(activeFileInfo);

    if (faceRes == MOK)
    {
        faceRes = arcFaceEngine->InitEngine(ASF_DETECT_MODE_IMAGE);//Image
        qDebug() << "IMAGE模式下初始化结果: " << faceRes;

        faceRes = arcFaceEngine->InitEngine(ASF_DETECT_MODE_VIDEO);//Video
        qDebug() << "VIDEO模式下初始化结果: " << faceRes;

    }

    //load QImage
    //QImage image;
    image.load("C:/Users/paipeng/Pictures/paipeng2.jpeg");
    qDebug() << "image: " << image.width() << "-" << image.height();

    // convert to opencv image IplImage
    IplImage *originImage = QImage2IplImage(&image);

    qDebug() << "IplImage: " << originImage->width << "-" << originImage->height;

    //FD
    ASF_SingleFaceInfo faceInfo = { 0 };
    MRESULT detectRes = arcFaceEngine->PreDetectFace(originImage, faceInfo, true);
    if (MOK == detectRes)
    {
        qDebug() << "PreDetectFace OK";
        //cvReleaseImage(&originImage);

        //FR
        ASF_FaceFeature faceFeature = { 0 };
        faceFeature.featureSize = FACE_FEATURE_SIZE;
        faceFeature.feature = (MByte *)malloc(faceFeature.featureSize * sizeof(MByte));
        detectRes = arcFaceEngine->PreExtractFeature(originImage, faceFeature, faceInfo);

        if (MOK == detectRes)
        {
            qDebug() << "PreExtractFeature OK " << faceFeature.featureSize;
        }
            free(faceFeature.feature);
//

    }

    cvReleaseImage(&originImage);


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
        } else {
            ui->camera2StartButton->setText(tr("start"));
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
    qDebug() << "processCapturedImage: " << cameraId << " img: " << img.width() << "-" << img.height();

    qrcodeDecode(cameraId, img);
}

void CameraWindow::qrcodeDecode(int cameraId, const QImage& image) {
    DecodeHints hints;
    hints.setEanAddOnSymbol(EanAddOnSymbol::Read);

    ImageView imageView{image.bits(), image.width(), image.height(), ImageFormat::RGBX};
    auto results = ReadBarcodes(imageView, hints);

    // if we did not find anything, insert a dummy to produce some output for each file
    if (results.empty())
        results.emplace_back(DecodeStatus::NotFound);

    for (auto&& result : results) {

        qDebug() << "RESULT: " << result.text();
        QString text = QString::fromWCharArray(result.text().c_str());
        if (cameraId == 0) {
            ui->camera1Label->setText(text);
        } else {
            ui->camera2Label->setText(text);
        }
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
