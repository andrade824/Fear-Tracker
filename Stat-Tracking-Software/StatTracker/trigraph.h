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
    // The mode with which the graphs are operating in
    enum GraphingMode { MODE_REALTIME, MODE_ANAYLZE };

    // Constructor
    explicit TriGraph(QWidget * parent = 0, int yLabelPadding = 30,
                      GraphingMode mode = MODE_ANAYLZE);

    // Pass the resize event down the chain of graphics views
    virtual void resizeEvent(QResizeEvent *event);

    // Set what mode the graphs are in
    void setMode(GraphingMode mode);

    // Set what data storage the graphs are using
    void setDataStore(FearData * data_store);

    // Destructor
    ~TriGraph();
private:
    // Displays the currently cached data
    void displayData();

signals:

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
};

#endif // TRIGRAPH_H
