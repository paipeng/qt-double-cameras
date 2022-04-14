#include "facecameraviewfinder.h"

FaceCameraViewfinder::FaceCameraViewfinder(QWidget *parent) : QCameraViewfinder(parent)
{

}
void FaceCameraViewfinder::updateData(int decodeState, float score, FaceData *faceData) {
    this->decodeState = decodeState;
    this->score = score;
    memcpy(&(this->faceData), faceData, sizeof(FaceData));
    this->repaint();
}

FaceData* FaceCameraViewfinder::getFaceData() {
    return &(this->faceData);
}

void FaceCameraViewfinder::paintEvent(QPaintEvent* event) {
    qDebug() << "paintEvent";
    // Default rendered -> call base class
    QCameraViewfinder::paintEvent(event);
    // draw some text
    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 4));

    //QBrush brush(Qt::green, Qt::SolidPattern);
    //painter.setBrush(brush);
    painter.drawText(100,100,"text");
    if (decodeState == 0) {
        // rescale camera-preview-image coordination -> viewfinder cooridnation
        float scale = this->width()*1.0f/faceData.width;

        QRect rect(faceData.faceInfo.faceRect.left * scale,
                   faceData.faceInfo.faceRect.top * scale,
                   (faceData.faceInfo.faceRect.right - faceData.faceInfo.faceRect.left) * scale,
                   (faceData.faceInfo.faceRect.bottom - faceData.faceInfo.faceRect.top) * scale);


        painter.drawRect(rect);
    }
};
