#ifndef FEARDATANODE_H
#define FEARDATANODE_H

#include <QObject>
#include "feartype.h"

class FearDataNode
{
public:
    // Default Constructor
    explicit FearDataNode();

    // Constructor that defines every value
    explicit FearDataNode(qint64 starttime, bool jump,
                          unsigned short sweat, unsigned short heartrate,
                          unsigned short fearlevel);

    // Getters
    unsigned short GetData(FearType type) const;
    qint64 GetTimeFromStart() const;
    bool GetJumpScare() const;
    unsigned short GetSweat() const;
    unsigned short GetHeartRate() const;
    unsigned short GetFearLevel() const;

    // Setters
    void SetTimeFromStart(qint64 starttime);
    void SetJumpScare(bool jump);
    void SetSweat(unsigned short sweat);
    void SetHeartRate(unsigned short rate);
    void SetFearLevel(unsigned short fear);

    // Destructor
    ~FearDataNode();

signals:

public slots:

private:
    qint64 m_timeFromStart;   // Time in seconds from the start of grabbing data
    bool m_jumpScare;               // Whether there was a jump scare or not
    unsigned short m_sweat;         // The victim's sweat level
    unsigned short m_heartRate;     // The victim's heartrate
    unsigned short m_fearLevel;     // The victim's overall fear level
};

#endif // FEARDATANODE_H
