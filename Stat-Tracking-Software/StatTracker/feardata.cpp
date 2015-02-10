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
    m_timer = new QTimer(this);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(addGarbage()));
    m_timer->start(50);
}

/**
 * @brief Adds a node to the data store
 *
 * @param data  A pointer to a dynamically allocated
 *              FearDataNode to add to storage
 */
void FearData::AddData(const FearDataNode & data)
{
    m_data.append(data);
    emit newDataStored(this);
}

void FearData::addGarbage()
{
    m_data.append(FearDataNode(m_starttime, rand() % 100, rand() % 100, rand() % 60 + 60, rand() % 47));
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
QList<FearDataNode> FearData::getLatestData(int num_data_nodes)
{
    int total_num_nodes = m_data.count();   // Total number of nodes currently stored

    // Make sure we have a correct number of data nodes
    if(num_data_nodes > total_num_nodes)
        num_data_nodes = total_num_nodes;

    return m_data.mid(total_num_nodes - num_data_nodes);
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

