#ifndef IPCHECK_H
#define IPCHECK_H

#include <QObject>

class ipCheck : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY addressChanged)

public:
    explicit ipCheck(QObject *parent = nullptr);
    QString ipAddress();

signals:
    void addressChanged();
private:
    QString addressIP;
    int tryCounter;

public slots:

};

#endif // IPCHECK_H
