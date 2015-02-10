#ifndef TRIGRAPH_H
#define TRIGRAPH_H

#include <QWidget>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QResizeEvent>
#include "graphitem.h"
#include "feardata.h"
#include "trigraphoverlay.h"

class TriGraph : public QWidget
{
    Q_OBJECT

public:
    // Constructor
    explicit TriGraph(QWidget * parent = 0, int yLabelPadding = 30);

    // Pass the resize event down the chain of graphics views
    virtual void resizeEvent(QResizeEvent *event);

    // Destructor
    ~TriGraph();

signals:

public slots:
    // Add new data to the
    void displayLatestData(FearData * data_store);

private:
    QGraphicsScene * m_scene;

    // Graphics views
    QGraphicsView * m_heartGraph;
    QGraphicsView * m_sweatGraph;
    QGraphicsView * m_jumpGraph;

    // Graphic items
    GraphItem * m_heartItem;
    GraphItem * m_sweatItem;
    GraphItem * m_jumpItem;

    // The overlay that draws the labels
    TriGraphOverlay * m_overlay;

    // Layouts for the graphs
    QHBoxLayout * m_mainLayout;
    QVBoxLayout * m_graphLayout;

    // A cache of the data being displayed
    QList<FearDataNode> m_data;
};

#endif // TRIGRAPH_H
