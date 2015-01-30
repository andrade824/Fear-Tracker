#include <QDateTime>
#include <QVariant>

#include <feardatanode.h>

/**
 * @brief Default parameter
 *
 * @param parent The parent QObject of this object
 */
FearDataNode::FearDataNode(QObject * parent)
    : QObject(parent), m_timeFromStart(QDateTime::currentMSecsSinceEpoch()), m_jumpScare(false), m_sweat(0),
      m_heartRate(50), m_fearLevel(0)
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
FearDataNode::FearDataNode(qint64 starttime, bool jump,
                           unsigned short sweat, unsigned short heartrate,
                           unsigned short fearlevel, QObject * parent)
    : QObject(parent), m_timeFromStart(QDateTime::currentMSecsSinceEpoch() - starttime), m_jumpScare(jump),
      m_sweat(sweat), m_heartRate(heartrate), m_fearLevel(fearlevel)
{ }

/**
 * @brief Returns a piece of data based off of its type
 *
 * @param type  Which piece of data to return
 *
 * @return Returns a piece of data based off of its type
 */
QVariant FearDataNode::GetData(int type)
{
    QVariant data;

    switch(type)
    {
        case TYPE_HEART: data.setValue(m_heartRate); break;
        case TYPE_JUMP: data.setValue(m_jumpScare); break;
        case TYPE_SWEAT: data.setValue(m_sweat); break;
        case TYPE_FEAR: data.setValue(m_fearLevel); break;
        default: data.setValue(0); break;
    }

    return data;
}

/**
 * Getters
 */
qint64 FearDataNode::GetTimeFromStart() const
{ return m_timeFromStart; }

bool FearDataNode::GetJumpScare() const
{ return m_jumpScare; }

unsigned short FearDataNode::GetSweat() const
{ return m_sweat; }

unsigned short FearDataNode::GetHeartRate() const
{ return m_heartRate; }

unsigned short FearDataNode::GetFearLevel() const
{ return m_fearLevel; }

/**
 * Setters
 */
void FearDataNode::SetTimeFromStart(qint64 starttime)
{ m_timeFromStart = QDateTime::currentMSecsSinceEpoch() - starttime; }

void FearDataNode::SetJumpScare(bool jump)
{ m_jumpScare = jump; }

void FearDataNode::SetSweat(unsigned short sweat)
{ m_sweat = sweat; }

void FearDataNode::SetHeartRate(unsigned short rate)
{ m_heartRate = rate; }

void FearDataNode::SetFearLevel(unsigned short fear)
{ m_fearLevel = fear; }

/**
 * @brief Destructor
 */
FearDataNode::~FearDataNode()
{ }

