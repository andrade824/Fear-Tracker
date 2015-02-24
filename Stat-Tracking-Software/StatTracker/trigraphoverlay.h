#ifndef TRIGRAPHOVERLAY_H
#define TRIGRAPHOVERLAY_H

#include <QWidget>
#include <QPaintEvent>
#include <QGraphicsView>
#include "graphitem.h"

class TriGraphOverlay : public QWidget
{
    Q_OBJECT
public:
    // Constructor that defines every value
    explicit TriGraphOverlay(int xoffset, int xPixelPerUnit, QGraphicsView * heartGraph,
                             QGraphicsView * sweatGraph, QGraphicsView * jumpGraph, GraphItem * heartItem,
                             GraphItem * sweatItem, GraphItem * jumpItem, QWidget * parent = 0);
    // Destructor
    ~TriGraphOverlay();

protected:
    // Paint event that draws the labels
    void paintEvent(QPaintEvent *);

private:
    // Draws Y-labels for a graph
    void drawYLabels(QPainter * painter, GraphItem * graph, int yoffset);

private:
    int m_xoffset;  // How far from the left side of the trigraph to start drawing the graphs
    int m_xPixelsPerLabel;  // How many pixels each x-label should be separated by

    QGraphicsView * m_heartGraph;   // The QGraphicsView representing the heartrate graph
    QGraphicsView * m_sweatGraph;   // The QGraphicsView representing the sweat graph
    QGraphicsView * m_jumpGraph;    // The QGraphicsView representing the jump graph

    GraphItem * m_heartItem;    // The GraphItem representing the heartrate graph
    GraphItem * m_sweatItem;    // The GraphItem representing the sweat graph
    GraphItem * m_jumpItem;     // The GraphItem representing the jump graph
};

#endif // TRIGRAPHOVERLAY_H
