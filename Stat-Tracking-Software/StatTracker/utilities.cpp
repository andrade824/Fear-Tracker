#include <QString>

namespace Utilities
{
    /**
     * @brief Converts the milliseconds from when data capture began
     *        to a string representation in the following format:
     *              hours:minutes:seconds
     *
     * @param milli Number of milliseconds from when data capture began
     *
     * @return String representation
     */
    QString milliToTime(qint64 milli)
    {
        int time = 0;
        QString time_text;

        // Hours
        time = (milli / 1000 / 60 / 60) % 24;
        time_text = ((time < 10) ? "0" : "") + QString::number(time);

        // Minutes
        time = (milli / 1000 / 60) % 60;
        time_text += ((time < 10) ? ":0" : ":") + QString::number(time);

        // Seconds
        time = (milli / 1000) % 60;
        time_text += ((time < 10) ? ":0" : ":") + QString::number(time);

        // Milliseconds
        time = milli % 1000;
        time_text += ((time < 100) ? ((time < 10) ? ":00" : ":0") : ":") + QString::number(time);

        return time_text;
    }
}
