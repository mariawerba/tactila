#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCursor>
#include <ipcheck.h>

#include <QQmlContext>
#include <qthreadpool.h>
#include <cmath>

#include <qdebug.h>
#include <iostream>
#include "halldial.h"
#include "usbhidhandler.h"

#define MAX_DIALS 16

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    USBHIDHandler *hidHandler = new USBHIDHandler(NULL, false);
    USBHIDHandler *hidHandlert = new USBHIDHandler(NULL, true);
    HallDial dialZero;
    HallDial dialOne;
    HallDial dialTwo;
    HallDial dialThree;
    HallDial dialFour;
    HallDial dialFive;
    HallDial dialSix;
    HallDial dialSeven;
    HallDial dialEight;
    HallDial dialNine;
    HallDial dialTen;
    HallDial dialEleven;
    HallDial dialTwelve;
    HallDial dialThirteen;
    HallDial dialFourteen;
    HallDial dialFifteen;

    dialZero.setDialIdentity(0);
    dialOne.setDialIdentity(1);
    dialTwo.setDialIdentity(2);
    dialThree.setDialIdentity(3);
    dialFour.setDialIdentity(4);
    dialFive.setDialIdentity(5);
    dialSix.setDialIdentity(6);
    dialSeven.setDialIdentity(7);
    dialEight.setDialIdentity(0);
    dialNine.setDialIdentity(1);
    dialTen.setDialIdentity(2);
    dialEleven.setDialIdentity(3);
    dialTwelve.setDialIdentity(4);
    dialThirteen.setDialIdentity(5);
    dialFourteen.setDialIdentity(6);
    dialFifteen.setDialIdentity(7);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<ipCheck>("ipCheck", 1,0, "IpChecker" );     //Adds the interface to the IP check as a QML Type
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    //QGuiApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

//    const QString &serial = hidHandler->getSerial();
//    if (serial == "30315004003C004B") {
//        std::cout << "device SERIAL 430315004003C004B is 15.6" << std::endl;
//        hidHandler->setDialPositions(0, 0, 'n', 24, 128, 12941);
//        hidHandler->setDialPositions(1, 1, 'n', 24, 105, 12964);
//        hidHandler->setDialPositions(2, 2, 'n', 24, 160, 12929);
//        hidHandler->setDialPositions(3, 3, 'n', 24, 82, 12966);
//    }
//    else {
//        std::cout << "device SERIAL " << serial.toStdString() << " not known, all dials off!" << std::endl;
//        // all dials are off
//        for (int i=0; i<MAX_DIALS; i++) {
//            //hidHandler->setDialPositions(i, 1, 0);
//        }
//    }
    const QString &serial = hidHandler->getSerial();
    if (serial == "4730501500500035") {
        std::cout << "device SERIAL 4730501500500035 is 27 Vertical" << std::endl;
    hidHandler->setDialPositions(0, 0, 'n', 24, 118, 12941);
    hidHandler->setDialPositions(1, 1, 'n', 24, 21, 12941);
    hidHandler->setDialPositions(2, 2, 'n', 24, 66, 12941);
    hidHandler->setDialPositions(3, 3, 'n', 24, 3, 12941);
    hidHandler->setDialPositions(4, 4, 'n', 24, 96, 12941);
    hidHandler->setDialPositions(5, 5, 'n', 24, 53, 12941);
    hidHandler->setDialPositions(6, 6, 'n', 24, 168, 12941);
    hidHandler->setDialPositions(7, 7, 'n', 24, 137, 12941);
    hidHandler->setDialPositions(8, 8, 'n', 24, 45, 12941);
    hidHandler->setDialPositions(9, 9, 'n', 24, 57, 12941);
    hidHandler->setDialPositions(10, 10, 'n', 24, 44, 12941);
    hidHandler->setDialPositions(11, 11, 'n', 24, 10, 12941);
    hidHandler->setDialPositions(12, 12, 'n', 24, 54, 12941);
    hidHandler->setDialPositions(13, 13, 'n', 24, 10, 12941);
    hidHandler->setDialPositions(14, 14, 'n', 24, 128, 12941);
    hidHandler->setDialPositions(15, 15, 'n', 24, 144, 12941);
    }
    else if(serial == "303150040043004A") {
            std::cout << "device SERIAL 303150040043004A is 27 Horizontal" << std::endl;
            hidHandler->setDialPositions(0, 0, 'n', 24, 42, 12941);
            hidHandler->setDialPositions(1, 1, 'n', 24, 151, 12941);
            hidHandler->setDialPositions(2, 2, 'n', 24, 13, 12941);
            hidHandler->setDialPositions(3, 3, 'n', 24, 164, 12941);
            hidHandler->setDialPositions(4, 4, 'n', 24, 133, 12941);
            hidHandler->setDialPositions(5, 5, 'n', 24, 56, 12941);
            hidHandler->setDialPositions(6, 6, 'n', 24, 43, 12941);
            hidHandler->setDialPositions(7, 7, 'n', 24, 99, 12941);
            hidHandler->setDialPositions(8, 8, 'n', 24, 41, 12941);
            hidHandler->setDialPositions(9, 9, 'n', 24, 9, 12941);
            hidHandler->setDialPositions(10, 10, 'n', 24, 76, 12941);
            hidHandler->setDialPositions(11, 11, 'n', 24, 72, 12941);
            hidHandler->setDialPositions(12, 12, 'n', 1, 4095, 12941);
            hidHandler->setDialPositions(13, 13, 'n', 1, 4095, 12941);
            hidHandler->setDialPositions(14, 14, 'n', 24, 117, 12941);
            hidHandler->setDialPositions(15, 15, 'n', 1, 4095, 12941);
    }
    else if (serial == "30315004003C004B") {
        std::cout << "device SERIAL 430315004003C004B is 15.6" << std::endl;
    hidHandler->setDialPositions(0, 0, 'n', 24, 128, 12941);
    hidHandler->setDialPositions(1, 1, 'n', 24, 105, 12964);
    hidHandler->setDialPositions(2, 2, 'n', 24, 160, 12929);
    hidHandler->setDialPositions(3, 3, 'n', 24, 82, 12966);
    }
    else {
            std::cout << "device SERIAL " << serial.toStdString() << " not known, all dials off!" << std::endl;
            // all dials are off
            for (int i=0; i<MAX_DIALS; i++) {
                //hidHandler->setDialPositions(i, 1, 0);
            }
        }
    engine.rootContext()->setContextProperty("dialZero", &dialZero);
    engine.rootContext()->setContextProperty("dialOne", &dialOne);
    engine.rootContext()->setContextProperty("dialTwo", &dialTwo);
    engine.rootContext()->setContextProperty("dialThree", &dialThree);
    engine.rootContext()->setContextProperty("dialFour", &dialFour);
    engine.rootContext()->setContextProperty("dialFive", &dialFive);
    engine.rootContext()->setContextProperty("dialSix", &dialSix);
    engine.rootContext()->setContextProperty("dialSeven", &dialSeven);
    engine.rootContext()->setContextProperty("dialEight", &dialEight);
    engine.rootContext()->setContextProperty("dialNine", &dialNine);
    engine.rootContext()->setContextProperty("dialTen", &dialTen);
    engine.rootContext()->setContextProperty("dialEleven", &dialEleven);
    engine.rootContext()->setContextProperty("dialTwelve", &dialTwelve);
    engine.rootContext()->setContextProperty("dialThirteen", &dialThirteen);
    engine.rootContext()->setContextProperty("dialFourteen", &dialFourteen);
    engine.rootContext()->setContextProperty("dialFifteen", &dialFifteen);

    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialZero, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialOne, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialTwo, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialThree, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialFour, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialFive, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialSix, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandler, &USBHIDHandler::dialChanged, &dialSeven, &HallDial::dialChanged,Qt::DirectConnection);

    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialEight, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialNine, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialTen, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialEleven, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialTwelve, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialThirteen, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialFourteen, &HallDial::dialChanged,Qt::DirectConnection);
    QObject::connect(hidHandlert, &USBHIDHandler::dialChanged, &dialFifteen, &HallDial::dialChanged,Qt::DirectConnection);

    QObject::connect(&app, &QGuiApplication::aboutToQuit, hidHandler, &USBHIDHandler::terminate);
    QObject::connect(&app, &QGuiApplication::aboutToQuit, hidHandlert, &USBHIDHandler::terminate);

    QThreadPool::globalInstance()->setMaxThreadCount(3);
    QThreadPool::globalInstance()->start(hidHandlert);
    QThreadPool::globalInstance()->start(hidHandler);

    engine.load(url);

    return app.exec();
}
