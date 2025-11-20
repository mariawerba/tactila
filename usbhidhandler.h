#ifndef USBHIDHANDLER_H
#define USBHIDHANDLER_H

#include <string>
#include <thread>
#include <atomic>
#include <functional>

class USBHIDHandler {
public:
  explicit USBHIDHandler();
  ~USBHIDHandler();

  enum class USBHIDHandlerState { STATE_FAIL, STATE_DISCONNECT, STATE_CONNECTED };

  // start/stop the internal thread
  void start();
  void terminate();

  // configure dial positions on the device
  bool setDialPositions(unsigned mux_setting, unsigned dial_nr, char mode, unsigned nr_positions, float zero_offset, float mag_pressed_threshold);

  // serial as UTF-8 string
  const std::string &getSerial() const { return serial_; }

  // callbacks to notify the application
  std::function<void(USBHIDHandlerState)> onStateChanged;
  // dial_nr, value (raw), nr_positions, button_pressed, moved_pos, moved_neg
  std::function<void(unsigned, unsigned, unsigned, bool, bool, bool)> onDialChanged;

private:
  void run();
  bool openDevice();

  std::atomic<bool> run_;
  std::thread worker_;
  void *h_;
  std::string serial_;
  bool boardNo_;
};

#endif // USBHIDHANDLER_H
