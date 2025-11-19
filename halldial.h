#ifndef HALLDIAL_H
#define HALLDIAL_H
#include <QObject>
#include <qdebug.h>

class HallDial : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int identity READ identity WRITE setDialIdentity NOTIFY idChanged FINAL)
    Q_PROPERTY(int positionCount READ positionCount NOTIFY positionCountChanged FINAL)
    Q_PROPERTY(int position READ position NOTIFY positionChanged FINAL)
    Q_PROPERTY(int incrementCount NOTIFY positionIncremented FINAL)
    Q_PROPERTY(int decrementCount NOTIFY positionDecremented FINAL)
    Q_PROPERTY(bool pressed NOTIFY buttonPressed NOTIFY buttonReleased NOTIFY buttonChanged FINAL)


public:
    explicit HallDial(QObject *parent = nullptr);
    int position() const {return m_position;}
    int positionCount() const {return m_position_count;}
    int identity() const {return m_id;}
    void setDialIdentity(const int identity);
    bool pressed() const {return m_pressed;}

signals:
    void positionChanged(int position);
    void positionIncremented(int incrementCount);
    void positionDecremented(int decrementCount);
    void buttonChanged(bool buttonPosition);
    void buttonPressed();
    void buttonReleased();
    void idChanged(int id);
    bool calibrateDialPosition(unsigned dial_nr, unsigned nr_positions, float zero_offset);
    void positionCountChanged(int count);

public slots:
    void dialChanged(unsigned dial_nr, unsigned value, unsigned nr_positions,bool button_pressed);
private:
    int m_position;
    int m_position_count;
    int m_id;
    bool m_pressed;

};

#endif // HALLDIAL_H
