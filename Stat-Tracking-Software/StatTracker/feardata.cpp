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
{ }

/**
 * @brief Adds a node to the data store
 *
 * @param data  A pointer to a dynamically allocated
 *              FearDataNode to add to storage
 */
void FearData::AddData(FearDataNode * data)
{
    m_data.append(data);
}

void FearData::addGarbage()
{
    m_data.append(new FearDataNode(m_starttime, rand() % 2, rand() % 100, rand() % 60 + 60, rand() % 100));
}

/**
 * @brief Returns the item at the specified index
 *
 * @param index The index of the data to return
 *
 * @return A pointer to the data specified at the index,
 *         or nullptr if an invalid index
 */
FearDataNode * FearData::getDataNode(int index) const
{
    FearDataNode * data = 0;

    if(index > 0 || index < m_data.count())
        data = m_data.at(index);

    return data;
}

/**
 * @brief Gets the last num_data_nodes number of data nodes and returns it
 * @param type  Which piece of data to return
 * @param num_data_nodes    The number of data nodes to return
 * @return  Returns the latest data nodes
 */
QVariantList FearData::getLatestData(int type, int num_data_nodes) const
{
    QVariantList data;

    int total_num_nodes = m_data.count();   // Total number of nodes currently stored

    // Make sure we have a correct number of data nodes
    if(num_data_nodes > total_num_nodes)
        num_data_nodes = total_num_nodes;

    // Grab the wanted data
    for(int i = total_num_nodes - num_data_nodes; i < total_num_nodes; ++i)
        data << m_data[i]->GetTimeFromStart() << m_data[i]->GetData(type);

    return data;
}

/**
 * @brief Returns a count of the current number of nodes being stored
 *
 * @return The number of nodes currently being stored
 */
int FearData::countDataNode() const
{
    return m_data.count();
}

/**
 * @brief Destructor
 */
FearData::~FearData()
{ }

