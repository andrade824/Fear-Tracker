#ifndef FEARDATANODE_H
#define FEARDATANODE_H

#include <QObject>

class FearDataNode : public QObject
{
    Q_OBJECT

    // Properties exposed to QML (they're all read-only properties)
    Q_PROPERTY(unsigned int timeFromStart READ GetTimeFromStart)
    Q_PROPERTY(bool jumpScare READ GetJumpScare)
    Q_PROPERTY(unsigned short sweat READ GetSweat)
    Q_PROPERTY(unsigned short heartRate READ GetHeartRate)
    Q_PROPERTY(unsigned short fearLevel READ GetFearLevel)

public:
    // Default Constructor
    explicit FearDataNode(QObject * parent = 0);

    // Constructor that defines every value
    explicit FearDataNode(unsigned int time, bool jump,
                          unsigned short sweat, unsigned short heartrate,
                          unsigned short fearlevel, QObject * parent = 0);

    // Getters
    unsigned int GetTimeFromStart() const;
    bool GetJumpScare() const;
    unsigned short GetSweat() const;
    unsigned short GetHeartRate() const;
    unsigned short GetFearLevel() const;

    // Destructor
    ~FearDataNode();

signals:

public slots:

private:
    unsigned int m_timeFromStart;   // Time in seconds from the start of grabbing data
    bool m_jumpScare;               // Whether there was a jump scare or not
    unsigned short m_sweat;         // The victim's sweat level
    unsigned short m_heartRate;     // The victim's heartrate
    unsigned short m_fearLevel;     // The victim's overall fear level
};

#endif // FEARDATANODE_H
