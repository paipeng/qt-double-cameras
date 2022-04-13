QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += multimedia multimediawidgets
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    camera.cpp \
    main.cpp \
    camera_window.cpp

HEADERS += \
    camera-interface.h \
    camera.h \
    camera_window.h \
    zxing/BarcodeFormat.h \
    zxing/BitHacks.h \
    zxing/ByteArray.h \
    zxing/DecodeHints.h \
    zxing/DecodeStatus.h \
    zxing/Flags.h \
    zxing/GTIN.h \
    zxing/ImageView.h \
    zxing/Point.h \
    zxing/Quadrilateral.h \
    zxing/ReadBarcode.h \
    zxing/Result.h \
    zxing/StructuredAppend.h \
    zxing/TextUtfEncoding.h \
    zxing/ZXContainerAlgorithms.h

FORMS += \
    camera_window.ui

TRANSLATIONS += \
    qt-double-cameras_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qt-double-cameras.qrc

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/libs/x64/release/ -lZXing
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/libs/x64/debug/ -lZXing
else:unix: LIBS += -L$$PWD/libs/x64/ -lZXing

INCLUDEPATH += $$PWD/libs/x64
DEPENDPATH += $$PWD/libs/x64
