#ifndef GRAPHITEM_H
#define GRAPHITEM_H

#include <QObject>
#include <QGraphicsItem>
#include "feardatanode.h"
#include "feartype.h"

class GraphItem : public QGraphicsItem
{

public:
    // Default constructor
    GraphItem(int miny, int maxy, FearType type = TYPE_HEART, QColor color = Qt::red);

    // The coordinates of this item
    QRectF boundingRect() const;

    // Redraw the graph
    void paint(QPainter * painter, const QStyleOptionGraphicsItem *, QWidget *);

    // Set the data in the item for future painting
    void setData(QList<FearDataNode> * newData);

    // Return the minimum X
    int getMinX() const;

    // Return the maximum X
    int getMaxX() const;

    // Return the maximum Y for the current type of data
    int getMaxY() const;

    // Return the minimum Y for the current type of data
    int getMinY() const;

    ~GraphItem();

private:
    FearType m_type;
    int m_minX;
    int m_maxX;
    int m_minY;
    int m_maxY;
    QColor m_color;
    QList<FearDataNode> * m_data;
};

#endif // GRAPHITEM_H
