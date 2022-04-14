#ifndef FACECAMERAVIEWFINDER_H
#define FACECAMERAVIEWFINDER_H

#include <QCameraViewfinder>
#include <QPainter>

class FaceCameraViewfinder : public QCameraViewfinder
{
    Q_OBJECT
public:
    FaceCameraViewfinder(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // FACECAMERAVIEWFINDER_H
