#include <QPainter>
#include "graphitem.h"
#include "feartype.h"

/**
 * @brief Constructor
 *
 * @param type The type of data this graph will display
 * @param color The color of the line in this graph
 */
GraphItem::GraphItem(FearType type, QColor color)
    : m_type(type), m_minX(0), m_maxX(0), m_minY(0), m_maxY(0), m_color(color), m_data(0)
{ }

/**
 * @brief Defines how large the graph item is in the scene
 *
 * @return Returns the bounding rectangle for this item
 */
QRectF GraphItem::boundingRect() const
{
    return QRectF(0, 0, m_maxX - m_minX, m_maxY - m_minY);
}

/**
 * @brief Actually draw the graph
 *
 * @param painter The painter object to draw lines with
 */
void GraphItem::paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setRenderHints(QPainter::Antialiasing);
    if(m_data != 0)
    {
        painter->setPen(QPen(m_color, 2));

        for(int i = 0; i < m_data->count() - 1; ++i)
        {
            painter->drawLine(m_data->at(i).GetTimeFromStart() - m_minX,
                              m_maxY - m_data->at(i).GetData(m_type),
                              m_data->at(i + 1).GetTimeFromStart() - m_minX,
                              m_maxY - m_data->at(i + 1).GetData(m_type));
        }
    }
}

/**
 * @brief Set the internal cache of data and update any needed state variables
 *
 * @param newData A list of the data that needs to be drawn
 */
void GraphItem::setData(QList<FearDataNode> * newData)
{
    m_data = newData;
    prepareGeometryChange();

    // Find minimum and maximum X coordinates
    m_minX = m_data->front().GetTimeFromStart();
    m_maxX = m_data->back().GetTimeFromStart();

    // Find minimum and maximum Y coordinates
    unsigned short data = 0;
    m_maxY = 0;
    m_minY = 9999;
    for(int i = 0; i < m_data->count(); ++i)
    {
        data = m_data->at(i).GetData(m_type);

        if(m_maxY < data)
            m_maxY = data;

        if(m_minY > data)
            m_minY = data;
    }
}

/**
 * Getters
 */
int GraphItem::getMinX() const
{ return m_minX; }

int GraphItem::getMaxX() const
{ return m_maxX; }

int GraphItem::getMaxY() const
{ return m_maxY; }

int GraphItem::getMinY() const
{ return m_minY; }

/**
 * @brief Destructors
 */
GraphItem::~GraphItem()
{ }
