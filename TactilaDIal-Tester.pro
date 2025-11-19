QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        halldial.cpp \
        hid.c \
        ipcheck.cpp \
        main.cpp \
        usbhidhandler.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
INSTALLS += target
target.files = Demo
target.path = /home/densitron/Desktop

LIBS += \
    -ludev

HEADERS += \
    halldial.h \
    hid_structs.h \
    hidapi.h \
    ipcheck.h \
    usbhidhandler.h
