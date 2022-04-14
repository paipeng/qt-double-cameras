#include "cpcameraviewfinder.h"

CPCameraViewfinder::CPCameraViewfinder(QWidget *parent) : QCameraViewfinder(parent)
{

}

void CPCameraViewfinder::paintEvent(QPaintEvent* event) {
    // Default rendered -> call base class
    QCameraViewfinder::paintEvent(event);
    // draw some text
    QPainter painter(this);
    painter.setPen(QPen(Qt::green, 4));

    //QBrush brush(Qt::green, Qt::SolidPattern);
    //painter.setBrush(brush);
    painter.drawText(100,100,"text");
    QRect rect( 10, 10, 200, 200);
    painter.drawRect(rect);
};
