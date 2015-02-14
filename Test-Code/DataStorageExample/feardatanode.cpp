#include "feardatanode.h"

/**
 * @brief Default parameter
 *
 * @param parent The parent QObject of this object
 */
FearDataNode::FearDataNode(QObject * parent)
    : QObject(parent), m_timeFromStart(0), m_jumpScare(false), m_sweat(0),
      m_heartRate(50), m_fearLevel(0)
{ }

/**
 * @brief A constructor that assigns every member variable
 *
 * @param time      Time in seconds from the start of grabbing data
 * @param jump      Whether there was a jump scare or not
 * @param sweat     The victim's sweat level
 * @param heartrate The victim's heartrate
 * @param fearlevel The victim's overall fear level
 * @param parentThe parent QObject of this object
 */
FearDataNode::FearDataNode(unsigned int time, bool jump,
                           unsigned short sweat, unsigned short heartrate,
                           unsigned short fearlevel, QObject * parent)
    : QObject(parent), m_timeFromStart(time), m_jumpScare(jump), m_sweat(sweat),
      m_heartRate(heartrate), m_fearLevel(fearlevel)
{ }

/**
 * Getters
 */
unsigned int FearDataNode::GetTimeFromStart() const
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
 * @brief Destructor
 */
FearDataNode::~FearDataNode()
{ }

