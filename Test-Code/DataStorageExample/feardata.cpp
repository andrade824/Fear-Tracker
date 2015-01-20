#include "feardata.h"

/**
 * @brief Default Constructor
 *
 * @param parent The parent QObject of this object
 */
FearData::FearData(QObject *parent) : QObject(parent)
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

/**
 * @brief Returns the item at the specified index
 *
 * @param index The index of the data to return
 *
 * @return A pointer to the data specified at the index,
 *         or nullptr if an invalid index
 */
FearDataNode * FearData::atDataNode(int index) const
{
    FearDataNode * data = 0;

    if(index > 0 || index < m_data.count())
        data = m_data.at(index);

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

