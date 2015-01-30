#ifndef FEARDATANODE_H
#define FEARDATANODE_H

#include <QObject>

class FearDataNode : public QObject
{
    Q_OBJECT

    // Properties exposed to QML (they're all read-only properties)
    Q_PROPERTY(qint64 timeFromStart READ GetTimeFromStart)
    Q_PROPERTY(bool jumpScare READ GetJumpScare)
    Q_PROPERTY(unsigned short sweat READ GetSweat)
    Q_PROPERTY(unsigned short heartRate READ GetHeartRate)
    Q_PROPERTY(unsigned short fearLevel READ GetFearLevel)
    Q_ENUMS(DataType)

public:
    enum DataType {
        TYPE_HEART,
        TYPE_JUMP,
        TYPE_SWEAT,
        TYPE_FEAR
    };

public:
    // Default Constructor
    explicit FearDataNode(QObject * parent = 0);

    // Constructor that defines every value
    explicit FearDataNode(qint64 starttime, bool jump,
                          unsigned short sweat, unsigned short heartrate,
                          unsigned short fearlevel, QObject * parent = 0);

    // Getters
    QVariant GetData(int type);
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
