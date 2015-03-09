#include "feardata.h"
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <QDateTime>

/**
 * @brief Default Constructor
 *
 * @param parent The parent QObject of this object
 */
FearData::FearData(QObject *parent) : QObject(parent), m_starttime(QDateTime::currentMSecsSinceEpoch())
{
//    m_timer = new QTimer(this);
//    connect(m_timer, SIGNAL(timeout()), this, SLOT(addGarbage()));
//    m_timer->start(100);
}

/**
 * @brief Adds a node to the data store
 *
 * @param data  A pointer to a dynamically allocated
 *              FearDataNode to add to storage
 */
void FearData::AddData(FearDataNode data)
{
    data.SetTimeFromStart(m_starttime);
    m_data.append(data);
    emit newDataStored(this);
}

/**
 * @brief Add random data to the data storage module. Used for test purposes.
 */
void FearData::addGarbage()
{
    m_data.append(FearDataNode(m_starttime, rand() % 100, rand() % 100, rand() % 60 + 60, rand() % 100));
    emit newDataStored(this);
}

/**
 * @brief Returns the item at the specified index
 *
 * @param index The index of the data to return
 *
 * @return A pointer to the data specified at the index,
 *         or nullptr if an invalid index
 */
FearDataNode FearData::getDataNode(int index) const
{
    return m_data.at(index);
}

/**
 * @brief Gets the last num_data_nodes number of data nodes and returns it
 * @param type  Which piece of data to return
 * @param num_data_nodes    The number of data nodes to return
 * @return  Returns the latest data nodes
 */
QList<FearDataNode> FearData::getLatestData(int num_data_nodes) const
{
    int total_num_nodes = m_data.count();   // Total number of nodes currently stored

    // Make sure we have a correct number of data nodes
    if(num_data_nodes > total_num_nodes)
        num_data_nodes = total_num_nodes;

    return m_data.mid(total_num_nodes - num_data_nodes);
}

/**
 * @brief Returns every data node between the start and end times
 *
 * @param start Get every node after this time
 * @param end   Get every node before this time
 *
 * @return A list of nodes between the start and end times
 */
QList<FearDataNode> FearData::getData(quint64 start, quint64 end) const
{
    QList<FearDataNode> data;

    for(int i = 0; i < m_data.count(); ++i)
    {
        if(m_data[i].GetTime() >= start && m_data[i].GetTime() <= end)
            data << m_data[i];
    }

    return data;
}

/**
 * @brief Get the node nearest to the time given
 *
 * @param time The time at which to find the nearest node
 *
 * @return The data node closest temporally to the time given
 */
FearDataNode FearData::getNearestNode(quint64 time) const
{
    int index = 0;
    bool found = false;

    // Bound check the time
    if(time <= m_data.front().GetTime())
        index = 0;
    else if (time >= m_data.back().GetTime())
        index = m_data.count() - 1;
    else
    {
        for(int i = 0; i < m_data.count() - 1 && !found; ++i)
        {
            // If the time is between this node and the next
            if(time >= m_data[i].GetTime() && time <= m_data[i + 1].GetTime())
            {
                quint64 nearFirst = time - m_data[i].GetTime();
                quint64 nearSecond = m_data[i + 1].GetTime() - time;

                // determine which node is closer to the given time
                if(nearFirst <= nearSecond)
                    index = i;
                else
                    index = i + 1;

                found = true;
            }
        }
    }

    return m_data[index];
}

/**
 * @brief Returns a count of the current number of nodes being stored
 *
 * @return The number of nodes currently being stored
 */
int FearData::countDataNodes() const
{
    return m_data.count();
}

/**
 * @brief Destructor
 */
FearData::~FearData()
{ }

