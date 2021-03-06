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


#if 0
IplImage* QImage2IplImage(const QImage *qimg) {
    IplImage *imgHeader = cvCreateImageHeader( cvSize(qimg->width(), qimg->height()), IPL_DEPTH_8U, 3);
    imgHeader->imageData = (char*) qimg->bits();

    uchar* newdata = (uchar*) malloc(sizeof(uchar) * qimg->width() * qimg->height() * 3);
    //memcpy(newdata, qimg->bits(), sizeof(uchar) * qimg->width() * qimg->height() * 3);
    for (int i = 0; i < qimg->height(); i++) {
        for (int j = 0; j < qimg->width(); j++) {
            QRgb rgb = qimg->pixel(j, i);
            newdata[i*qimg->width()*3 + j*3 + 2] = (rgb >> 16) & 0xFF;
            newdata[i*qimg->width()*3 + j*3 + 1] = (rgb >> 8) & 0xFF;
            newdata[i*qimg->width()*3 + j*3 + 0] = (rgb >> 0) & 0xFF;
        }
    }

    imgHeader->imageData = (char*) newdata;
    //cvClo
    return imgHeader;
}


IplImage* QImage2IplImage2(QImage *qimg) {
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
    , ui(new Ui::CameraWindow), camera1(0, this), camera2(1, this), camera1AutoCapture(true), camera2AutoCapture(true)
{
    ui->setupUi(this);
    ui->camera2ComboBox->setCurrentIndex(1);
    initCameras();
    ui->statusbar->showMessage(tr("app_info"));


    QObject::connect(&arcFaceEngine, &ArcFaceEngine::updateFaceDecodeResult, this, &CameraWindow::updateFaceDecodeResult);
    arcFaceEngine.start();
    arcFaceEngine.setPriority(QThread::LowestPriority);

}

CameraWindow::~CameraWindow() {
    free(registeredFaceFeature.feature);
    arcFaceEngine.UnInitEngine();
    //delete arcFaceEngine;
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

    //arcFaceEngine = new ArcFaceEngine();

    MRESULT faceRes = arcFaceEngine.ActiveSDK((char*)(appId.toStdString().c_str()), (char*)(sdkKey.toStdString().c_str()), NULL);
    qDebug() << "ActiveSDK: " << faceRes;


    //????????????????????????
    ASF_ActiveFileInfo activeFileInfo = { 0 };
    arcFaceEngine.GetActiveFileInfo(activeFileInfo);

    if (faceRes == MOK)
    {
        faceRes = arcFaceEngine.InitEngine(ASF_DETECT_MODE_IMAGE);//Image
        qDebug() << "IMAGE????????????????????????: " << faceRes;

        //faceRes = arcFaceEngine->InitEngine(ASF_DETECT_MODE_VIDEO);//Video
        //qDebug() << "VIDEO????????????????????????: " << faceRes;

    }

    arcFaceEngine.SetLivenessThreshold(0.8, 0.0);

    //load QImage
    QImage registeredFaceImage;
    registeredFaceImage.load("C:/Users/paipeng/Pictures/paipeng2.jpeg");
    qDebug() << "image: " << registeredFaceImage.width() << "-" << registeredFaceImage.height() << "-" << registeredFaceImage.bitPlaneCount() << " " << registeredFaceImage.byteCount();

    arcFaceEngine.registerFace(registeredFaceImage);
#if 0

    // convert to opencv image IplImage
    IplImage *originImage = QImage2IplImage(&registeredFaceImage);

    qDebug() << "IplImage: " << originImage->width << "-" << originImage->height << "-" << originImage->nChannels;
    cvSaveImage("foo.jpeg", originImage);
    //FD
    ASF_SingleFaceInfo faceInfo = { 0 };
    MRESULT detectRes = arcFaceEngine.PreDetectFace(originImage, faceInfo, true);
    qDebug() << "PreDetectFace: " << detectRes;
    if (MOK == detectRes)
    {
        qDebug() << "PreDetectFace OK";

        //age gender
        ASF_MultiFaceInfo multiFaceInfo = { 0 };
        multiFaceInfo.faceOrient = (MInt32*)malloc(sizeof(MInt32));
        multiFaceInfo.faceRect = (MRECT*)malloc(sizeof(MRECT));

        multiFaceInfo.faceNum = 1;
        multiFaceInfo.faceOrient[0] = faceInfo.faceOrient;
        multiFaceInfo.faceRect[0] = faceInfo.faceRect;

        ASF_AgeInfo ageInfo = { 0 };
        ASF_GenderInfo genderInfo = { 0 };
        ASF_Face3DAngle angleInfo = { 0 };
        ASF_LivenessInfo liveNessInfo = { 0 };

        //age ???gender ???3d angle ??????
        detectRes = arcFaceEngine.FaceASFProcess(multiFaceInfo, originImage, ageInfo, genderInfo, angleInfo, liveNessInfo);

        if (MOK == detectRes)
        {
            QString showStr = QString("??????:%1,??????:%2,??????:%3").arg(
                        QString::number(ageInfo.ageArray[0]), QString::number(genderInfo.genderArray[0]),
                    QString::number(liveNessInfo.isLive[0]));
 //                   (genderInfo.genderArray[0] == 0 ? "???" : "???"),
  //                  (liveNessInfo.isLive[0] == 1 ? "???" : "???"));
            qDebug() << "age/gender: " << showStr;
        }

        //FR used for face compare 1032 bytes

        registeredFaceFeature = { 0 };
        registeredFaceFeature.featureSize = FACE_FEATURE_SIZE;
        registeredFaceFeature.feature = (MByte *)malloc(registeredFaceFeature.featureSize * sizeof(MByte));
        detectRes = arcFaceEngine.PreExtractFeature(originImage, registeredFaceFeature, faceInfo);

        if (MOK == detectRes) {
            qDebug() << "PreExtractFeature OK " << registeredFaceFeature.featureSize;

        }
        //free(registeredFaceFeature.feature);
    }

    cvReleaseImage(&originImage);
#endif
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
        qrcodeDecode(cameraId, img);
    } else {
        //faceProcess(cameraId, img);
        arcFaceEngine.setImage(img);
    }
}

void CameraWindow::faceProcess(int cameraId, const QImage& image) {
    qDebug() << "faceProcess: " << cameraId;
#if 0
    IplImage *originImage = QImage2IplImage(&image);

    //FD
    ASF_SingleFaceInfo faceInfo = { 0 };
    MRESULT detectRes = arcFaceEngine.PreDetectFace(originImage, faceInfo, true);
    qDebug() << "PreDetectFace: " << detectRes;
    if (MOK == detectRes)
    {
        qDebug() << "PreDetectFace OK";

        //age gender
        ASF_MultiFaceInfo multiFaceInfo = { 0 };
        multiFaceInfo.faceOrient = (MInt32*)malloc(sizeof(MInt32));
        multiFaceInfo.faceRect = (MRECT*)malloc(sizeof(MRECT));

        multiFaceInfo.faceNum = 1;
        multiFaceInfo.faceOrient[0] = faceInfo.faceOrient;
        multiFaceInfo.faceRect[0] = faceInfo.faceRect;

        ASF_AgeInfo ageInfo = { 0 };
        ASF_GenderInfo genderInfo = { 0 };
        ASF_Face3DAngle angleInfo = { 0 };
        ASF_LivenessInfo liveNessInfo = { 0 };

        //age ???gender ???3d angle ??????
        detectRes = arcFaceEngine.FaceASFProcess(multiFaceInfo, originImage, ageInfo, genderInfo, angleInfo, liveNessInfo);

        if (MOK == detectRes)
        {
            QString showStr = QString("??????:%1,??????:%2,??????:%3").arg(
                        QString::number(ageInfo.ageArray[0]), QString::number(genderInfo.genderArray[0]),
                    QString::number(liveNessInfo.isLive[0]));
 //                   (genderInfo.genderArray[0] == 0 ? "???" : "???"),
  //                  (liveNessInfo.isLive[0] == 1 ? "???" : "???"));
            qDebug() << "age/gender: " << showStr;
        }

        //FR used for face compare 1032 bytes
        ASF_FaceFeature faceFeature;

        faceFeature = { 0 };
        faceFeature.featureSize = FACE_FEATURE_SIZE;
        faceFeature.feature = (MByte *)malloc(faceFeature.featureSize * sizeof(MByte));
        detectRes = arcFaceEngine.PreExtractFeature(originImage, faceFeature, faceInfo);

        if (MOK == detectRes) {
            qDebug() << "PreExtractFeature OK " << faceFeature.featureSize;
        }

        MFloat confidenceLevel = 0;
        // ??????????????????????????????????????????????????????0.82 ??????????????????????????????0.80
        MRESULT pairRes = arcFaceEngine.FacePairMatching(confidenceLevel, faceFeature, registeredFaceFeature);
        if (MOK == pairRes) {
            qDebug() << "FacePairMatching: " << confidenceLevel;
        }
        free(faceFeature.feature);
    }

    cvReleaseImage(&originImage);
#endif
}

void CameraWindow::updateFaceDecodeResult(int decodeState, float score) {
    Q_UNUSED(decodeState);
    Q_UNUSED(score);
    qDebug() << "updateFaceDecodeResult: " << decodeState << " score: " << score;
    if (decodeState == 0) {
    FaceData faceData;
    memcpy(&faceData, &(arcFaceEngine.faceData), sizeof(FaceData));
#if 1
    QString showStr = QString("??????:%1,??????:%2,??????:%3, score: %4").arg(
                QString::number(faceData.ageInfo.ageArray[0]), QString::number(faceData.genderInfo.genderArray[0]),
            QString::number(faceData.liveNessInfo.isLive[0]), QString::number(score));
    ui->camera2Label->setText(showStr);
#endif
    } else {
        ui->camera2Label->setText(QString("not found -> error"));
    }
    camera2.takeImage();
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
