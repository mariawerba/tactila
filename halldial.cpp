
#include "halldial.h"
#include <iostream>

HallDial::HallDial()
{
    m_id = 0;
    m_position = 0;
    m_position_count = -1;
    m_pressed = false;
}

void HallDial::dialChanged(unsigned dial_nr, unsigned new_value, unsigned nr_positions, bool button_pressed)
{
    int new_position = 0;
    if (static_cast<int>(dial_nr) == m_id) {

        if (nr_positions != 0) {
            if (nr_positions != static_cast<unsigned>(m_position_count)) {
                m_position_count = nr_positions;
                // no explicit callback for position count; consumers can inspect positionCount()
            }
            new_position = static_cast<int>(new_value);
        }

        // Calculates the distances between points in a circular list
        if (new_position > m_position) {
            int positive_size = new_position - m_position;
            int negative_size = m_position + (nr_positions - new_position);

            if (positive_size < negative_size) {
                if (onPositionIncremented) onPositionIncremented(positive_size);
            } else if (positive_size > negative_size) {
                if (onPositionDecremented) onPositionDecremented(negative_size);
            }
        } else if (new_position < m_position) {
            int positive_size = new_position + (nr_positions - m_position);
            int negative_size = m_position - new_position;

            if (positive_size < negative_size) {
                if (onPositionIncremented) onPositionIncremented(positive_size);
            } else if (positive_size > negative_size) {
                if (onPositionDecremented) onPositionDecremented(negative_size);
            }
        }

        if (m_position != new_position) {
            m_position = new_position;
            if (onPositionChanged) onPositionChanged(m_position);
        }

        // Check button state change
        if (m_pressed != button_pressed) {
            if (button_pressed) {
                if (onButtonPressed) onButtonPressed();
            } else {
                if (onButtonReleased) onButtonReleased();
            }
            m_pressed = button_pressed;
            if (onButtonChanged) onButtonChanged(m_pressed);
        }
    }
}


