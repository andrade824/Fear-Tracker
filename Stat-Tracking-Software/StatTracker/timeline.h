#ifndef TIMELINE_H
#define TIMELINE_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QMouseEvent>
#include "graphitem.h"
#include "feardata.h"

// Minimum padding between the markers
const int MARKER_PADDING = 20;

// Width of the markers
const int MARKER_WIDTH = 3;

class Timeline : public QGraphicsView
{
    Q_OBJECT

public:
    // Default constructor
    Timeline(QWidget * parent = 0);

    // Resize the scene to fit the new size
    virtual void resizeEvent(QResizeEvent *event);

    // Draw the overlay
    virtual void paintEvent(QPaintEvent * event);

    // Overload the mouse events for moving markers
    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);

    // Set what data storage the graphs are using
    void setDataStore(FearData * data_store);

    // Destructor
    ~Timeline();
signals:
    void markersMoved(quint64 beginTime, quint64 endTime);

public slots:
    // Add new data to the graph
    void displayLatestData();

private:
    // Graphics scene to draw on and the graph to draw
    QGraphicsScene * m_scene;
    GraphItem * m_fearGraph;

    // Where the markers are located
    int m_leftMarkerPos;
    int m_rightMarkerPos;

    // Whether a marker is currently being moved
    bool m_leftMarkerMoving;
    bool m_rightMarkerMoving;

    // The data storage module to get data from
    FearData * m_dataStore;

    // A cache of the data being displayed
    QList<FearDataNode> m_data;
};

#endif // TIMELINE_H
