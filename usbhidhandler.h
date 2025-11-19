#ifndef USBHIDHANDLER_H
#define USBHIDHANDLER_H

#include <qobject.h>
#include <qrunnable.h>

class USBHIDHandler : public QObject, public QRunnable {
  Q_OBJECT

public:
  explicit USBHIDHandler(QObject *parent = nullptr, bool boardNo = false);

  enum class USBHIDHandlerState {
    STATE_FAIL,
    STATE_DISCONNECT,
    STATE_CONNECTED
  };
  Q_ENUM(USBHIDHandlerState);

  const QString &getSerial() { return serial_; }

public slots:
  void terminate();
  bool setDialPositions(unsigned mux_setting, unsigned dial_nr, char mode, unsigned nr_positions, float zero_offset, float mag_pressed_threshold);


private:
  bool run_;
  void *h_;
  void run();
  QString serial_;

signals:
  void stateChanged(USBHIDHandler::USBHIDHandlerState);
  void dialChanged(unsigned dial_nr, float value, unsigned nr_positions,
                   bool button_pressed, bool moved_pos, bool moved_neg);
};

#endif // USBHIDHANDLER_H
