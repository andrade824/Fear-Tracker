#ifndef TRIGRAPH_H
#define TRIGRAPH_H

#include <QWidget>
#include <QPaintEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGraphicsView>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include "graphitem.h"
#include "feardata.h"
#include "trigraphoverlay.h"

class TriGraph : public QWidget
{
    Q_OBJECT

public:
    // The mode with which the graphs are operating in
    enum GraphingMode { MODE_REALTIME, MODE_ANAYLZE };

    // Constructor
    explicit TriGraph(QWidget * parent = 0, int yLabelPadding = 30,
                      GraphingMode mode = MODE_REALTIME);

    // Pass the resize event down the chain of graphics views
    virtual void resizeEvent(QResizeEvent *event);

    // Track when the mouse is hovered over the graph
    virtual void mouseMoveEvent(QMouseEvent * event);

    // Mouse has left the graphs
    virtual void leaveEvent(QEvent * event);

    // Set what mode the graphs are in
    void setMode(GraphingMode mode);

    // Set what data storage the graphs are using
    void setDataStore(FearData * data_store);

    // Set the number of nodes to display in real time mode
    void setNumRealTimeNodes(int num_nodes);

    // Destructor
    virtual ~TriGraph();
private:
    // Displays the currently cached data
    void displayData();

signals:
    // Output a signal when a node is being hovered on
    void dataHovered(FearDataNode data);

    // No nodes are being hovered over
    void noHovering();

public slots:
    // Add latest data to the graphs
    void getRealtimeData();

    // Add data for analyzing to the graphs
    void getAnalyzeData(quint64 beginTime, quint64 endTime);

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

    // The data storage module to get data from
    FearData * m_dataStore;

    // A cache of the data being displayed
    QList<FearDataNode> m_data;

    // What mode the graphs are in
    GraphingMode m_mode;

    // The last node that was hovered over
    quint64 m_lastNodeHovered;

    // The number of nodes to display in real time mode
    int m_numRealTimeNodes;
};

#endif // TRIGRAPH_H
