#include <QDateTime>
#include <QVariant>

#include <feardatanode.h>

/**
 * @brief Default parameter
 *
 * @param parent The parent QObject of this object
 */
FearDataNode::FearDataNode()
    : m_timeFromStart(QDateTime::currentMSecsSinceEpoch()), m_accelLevel(0), m_sweat(0),
      m_heartRate(0), m_fearLevel(0)
{ }

/**
 * @brief A constructor that assigns every member variable
 *
 * @param starttime The time in milliseconds when the data storage began
 * @param jump      Whether there was a jump scare or not
 * @param sweat     The victim's sweat level
 * @param heartrate The victim's heartrate
 * @param fearlevel The victim's overall fear level
 * @param parent    The parent QObject of this object
 */
FearDataNode::FearDataNode(qint64 starttime, quint8 accel,
                           quint8 sweat, quint8 heartrate, quint8 fearlevel)
    : m_timeFromStart(QDateTime::currentMSecsSinceEpoch() - starttime), m_accelLevel(accel),
      m_sweat(sweat), m_heartRate(heartrate), m_fearLevel(fearlevel)
{ }

/**
 * @brief Copy constructor
 *
 * @param copy The other data node to copy
 */
FearDataNode::FearDataNode(const FearDataNode &copy)
    : m_timeFromStart(QDateTime::currentMSecsSinceEpoch()), m_accelLevel(0), m_sweat(0),
      m_heartRate(0), m_fearLevel(0)
{
    *this = copy;
}

/**
 * @brief Assignment operator overload
 *
 * @param rhs The right hand side of the assignment
 *
 * @return A pointer to the current data node
 */
FearDataNode *FearDataNode::operator=(const FearDataNode &rhs)
{
    if(this != &rhs)
    {
        m_timeFromStart = rhs.m_timeFromStart;
        m_accelLevel = rhs.m_accelLevel;
        m_sweat = rhs.m_sweat;
        m_heartRate = rhs.m_heartRate;
        m_fearLevel = rhs.m_fearLevel;
    }

    return this;
}

/**
 * @brief Returns a piece of data based off of its type
 *
 * @param type  Which piece of data to return
 *
 * @return Returns a piece of data based off of its type
 */
quint8 FearDataNode::GetData(FearType type) const
{
    quint8 data;

    switch(type)
    {
        case TYPE_HEART: data = m_heartRate; break;
        case TYPE_JUMP: data = m_accelLevel; break;
        case TYPE_SWEAT: data = m_sweat; break;
        case TYPE_FEAR: data = m_fearLevel; break;
        default: data = 0; break;
    }

    return data;
}

/**
 * @brief Setsa piece of data based off of its type
 *
 * @param type  Which piece of data to set
 * @param data  The data to set
 */
void FearDataNode::SetData(FearType type, quint8 data)
{
    switch(type)
    {
        case TYPE_HEART: m_heartRate = data; break;
        case TYPE_JUMP: m_accelLevel = data; break;
        case TYPE_SWEAT: m_sweat = data; break;
        case TYPE_FEAR: m_fearLevel = data; break;
        default: break;
    }
}

/**
 * Getters
 */
quint64 FearDataNode::GetTime() const
{ return m_timeFromStart; }

quint8 FearDataNode::GetAccelLevel() const
{ return m_accelLevel; }

quint8 FearDataNode::GetSweat() const
{ return m_sweat; }

quint8 FearDataNode::GetHeartRate() const
{ return m_heartRate; }

quint8 FearDataNode::GetFearLevel() const
{ return m_fearLevel; }

/**
 * Setters
 */
void FearDataNode::SetTimeFromStart(qint64 starttime)
{ m_timeFromStart = QDateTime::currentMSecsSinceEpoch() - starttime; }

void FearDataNode::SetAccelLevel(quint8 accel)
{ m_accelLevel = accel; }

void FearDataNode::SetSweat(quint8 sweat)
{ m_sweat = sweat; }

void FearDataNode::SetHeartRate(quint8 rate)
{ m_heartRate = rate; }

void FearDataNode::SetFearLevel(quint8 fear)
{ m_fearLevel = fear; }

/**
 * @brief Destructor
 */
FearDataNode::~FearDataNode()
{ }

