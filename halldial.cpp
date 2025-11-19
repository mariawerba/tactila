#include "halldial.h"

HallDial::HallDial(QObject *parent)
  : QObject(parent)
{
    m_id =0;
    m_position=0;
    m_position_count=-1;    //Initiate with -1, if dial exist it will be overwritten.
    m_pressed=false;        //Initiate with false, button no pressed.
}

void HallDial::dialChanged(unsigned dial_nr, unsigned new_value, unsigned nr_positions, bool button_pressed){

    int new_position =0;
    if(static_cast<int>(dial_nr) == m_id)
    {

        if(nr_positions !=0) // Check if the dial exists
        {
            if(nr_positions != static_cast<unsigned>(m_position_count))
            {
                m_position_count = nr_positions;
                emit positionCountChanged(m_position_count);
            }
            new_position = new_value; // Convert from unsigned to Int
        }

        //Calculates the distances between points in a circular list
        if(new_position>m_position)
        {
            int positive_size = new_position-m_position; // Calculates the distance betweent two points in positive direction
            int negative_size = m_position+(nr_positions-new_position); //+1; // Calculates the distance between two points in negative direction

            //Emit the smaler distance as the more likely outcome
            if(positive_size<negative_size)
            {
                emit positionIncremented(positive_size);
            }
            else if(positive_size>negative_size)
            {
                emit positionDecremented(negative_size);
                qDebug() << negative_size;
            }
        }
        else if(new_position<m_position)
        {

            int positive_size = new_position + (nr_positions - m_position); //+1; Not needed // Calculates the distance between two points in positive direction
            int negative_size = m_position - new_position; // Calculates the distance betweent two points in negative direction

            //Emit the smaler distance as the more likely outcome
            if(positive_size<negative_size)
            {
                emit positionIncremented(positive_size); //Emit clockwise turn of positive_size
            }
            else if(positive_size>negative_size)
            {
                emit positionDecremented(negative_size); //Emit counter clockwise turn of negative_size

            }
        }

        if(m_position != new_position) //if the read position is different, emitt the change
        {
            m_position = new_position;
            emit positionChanged(m_position);
            //qDebug() << m_position;
        }

        //Check if the button position has changed
        if(m_pressed != button_pressed)
        {
            //Change to button_pressed implies a button was pressed
            if(button_pressed)
            {
                emit buttonPressed();
            }
            //Only other change is that the button was released
            else if (!button_pressed)
            {
                emit buttonReleased();
            }
            //After the change was handeled update the m_pressed value
            m_pressed = button_pressed;
            emit buttonChanged(m_pressed);
        }
    }
}

void HallDial::setDialIdentity(const int identity)
{
    m_id = identity;
}


