// Plain C++ replacement for the previous QObject-based HallDial
#ifndef HALLDIAL_H
#define HALLDIAL_H

#include <functional>

class HallDial {
public:
    HallDial();

    int position() const { return m_position; }
    int positionCount() const { return m_position_count; }
    int identity() const { return m_id; }
    void setDialIdentity(const int identity) { m_id = identity; }
    bool pressed() const { return m_pressed; }

    // Called by the HID handler when a report for a dial arrives
    void dialChanged(unsigned dial_nr, unsigned value, unsigned nr_positions, bool button_pressed);

    // Callbacks for consumers. Set these to receive events.
    std::function<void(int)> onPositionChanged;
    std::function<void(int)> onPositionIncremented;
    std::function<void(int)> onPositionDecremented;
    std::function<void(bool)> onButtonChanged;
    std::function<void()> onButtonPressed;
    std::function<void()> onButtonReleased;

private:
    int m_position;
    int m_position_count;
    int m_id;
    bool m_pressed;
};

#endif // HALLDIAL_H
