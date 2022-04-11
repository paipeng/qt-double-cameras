#ifndef CAMERAWINDOW_H
#define CAMERAWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CameraWindow; }
QT_END_NAMESPACE

class CameraWindow : public QMainWindow
{
    Q_OBJECT

public:
    CameraWindow(QWidget *parent = nullptr);
    ~CameraWindow();

private:
    Ui::CameraWindow *ui;
};
#endif // CAMERAWINDOW_H
