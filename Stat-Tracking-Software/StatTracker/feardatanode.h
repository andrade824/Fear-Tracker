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
    explicit FearDataNode(qint64 starttime, quint8 accel,
                          quint8 sweat, quint8 heartrate, quint8 fearlevel);

    // Copy constructor
    FearDataNode(const FearDataNode & copy);

    // Assignment Op overload
    FearDataNode * operator=(const FearDataNode & rhs);

    // Getters
    quint8 GetData(FearType type) const;
    quint64 GetTime() const;
    quint8 GetAccelLevel() const;
    quint8 GetSweat() const;
    quint8 GetHeartRate() const;
    quint8 GetFearLevel() const;

    // Setters
    void SetData(FearType type, quint8 data);
    void SetTimeFromStart(qint64 starttime);
    void SetAccelLevel(quint8 accel);
    void SetSweat(quint8 sweat);
    void SetHeartRate(quint8 rate);
    void SetFearLevel(quint8 fear);

    // Destructor
    ~FearDataNode();

signals:

public slots:

private:
    quint64 m_timeFromStart; // Time in seconds from the start of grabbing data
    quint8 m_accelLevel;       // Whether there was a jump scare or not
    quint8 m_sweat;         // The victim's sweat level
    quint8 m_heartRate;     // The victim's heartrate
    quint8 m_fearLevel;     // The victim's overall fear level
};

#endif // FEARDATANODE_H
