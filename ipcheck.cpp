#include "ipcheck.h"
#include <QNetworkInterface>
ipCheck::ipCheck(QObject *parent) : QObject(parent)
{
    addressIP = "0";
    ipAddress();
}

QString ipCheck::ipAddress()
{
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
        {
            addressIP = address.toString();
            //qDebug() << address.toString();
            return address.toString();
        }
    }
    return "0";
}
