#include "trigraph.h"
#include <QSpacerItem>
#include <QGraphicsView>
#include "feardata.h"

/**
 * @brief Default constructor
 *
 * @param parent The widget that owns this one
 */
TriGraph::TriGraph(QWidget * parent, int yLabelPadding, GraphingMode mode)
    : QWidget(parent), m_mode(mode)
{
    // Set up the scene
    m_heartItem = new GraphItem(TYPE_HEART, Qt::red);
    m_sweatItem = new GraphItem(TYPE_SWEAT, Qt::blue);
    m_jumpItem = new GraphItem(TYPE_FEAR, Qt::green);

    m_scene = new QGraphicsScene(this);
    m_scene->addItem(m_heartItem);
    m_scene->addItem(m_sweatItem);
    m_scene->addItem(m_jumpItem);

    // Initialize the layouts
    m_mainLayout = new QHBoxLayout;
    m_graphLayout = new QVBoxLayout;

    m_mainLayout->addSpacing(yLabelPadding);
    m_mainLayout->addLayout(m_graphLayout);
    m_mainLayout->setMargin(0);
    m_mainLayout->setSpacing(0);

    // Initialize the graphs
    m_heartGraph = new QGraphicsView(m_scene, this);
    m_sweatGraph = new QGraphicsView(m_scene, this);
    m_jumpGraph = new QGraphicsView(m_scene, this);
    m_heartGraph->setFrameShape(QFrame::StyledPanel);
    m_sweatGraph->setFrameShape(QFrame::StyledPanel);
    m_jumpGraph->setFrameShape(QFrame::StyledPanel);

    // Fill up the layouts
    m_graphLayout->addWidget(m_heartGraph);
    m_graphLayout->addWidget(m_sweatGraph);
    m_graphLayout->addWidget(m_jumpGraph);
    m_graphLayout->setSpacing(0);
    m_graphLayout->setMargin(0);

    this->setLayout(m_mainLayout);

    // Set graphics view properties
    m_heartGraph->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_heartGraph->setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
    m_sweatGraph->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_sweatGraph->setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
    m_jumpGraph->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    m_jumpGraph->setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);

    // Make sure scrollbars don't appear
    m_heartGraph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_sweatGraph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_jumpGraph->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    // Set up the overlay
    m_overlay = new TriGraphOverlay(yLabelPadding, 100, m_heartGraph, m_sweatGraph, m_jumpGraph, m_heartItem, m_sweatItem, m_jumpItem, this);
}

/**
 * @brief Make sure every graphics view resizes when the window resizes
 */
void TriGraph::resizeEvent(QResizeEvent * event)
{
    m_heartGraph->fitInView(m_heartItem);
    m_sweatGraph->fitInView(m_sweatItem);
    m_jumpGraph->fitInView(m_jumpItem);
    m_overlay->resize(event->size());
    event->accept();
}

/**
 * @brief Set the mode of the graphs
 *
 * @param mode The mode to switch to
 */
void TriGraph::setMode(TriGraph::GraphingMode mode)
{
    m_mode = mode;
}

/**
 * @brief Sets the data storage used by the graphs
 * @param data_store The storage to use
 */
void TriGraph::setDataStore(FearData * data_store)
{
    m_dataStore = data_store;
}

/**
 * @brief Updates each of the graphs with the new data
 *
 * @param data_store The data store to grab the latest data from
 */
void TriGraph::getRealtimeData()
{
    if(m_mode == MODE_REALTIME)
    {
        m_data = m_dataStore->getLatestData(150);
        displayData();
    }
}

/**
 * @brief Get data between two points in time and display it
 *
 * @param beginTime The start time to get data
 * @param endTime   The end time to get data
 */
void TriGraph::getAnalyzeData(quint64 beginTime, quint64 endTime)
{
    if(m_mode == MODE_ANAYLZE)
    {
        m_data = m_dataStore->getData(beginTime, endTime);
        displayData();
    }
}

/**
 * @brief Update the graphs with the currently cached data
 */
void TriGraph::displayData()
{
    m_heartItem->setData(&m_data);
    m_sweatItem->setData(&m_data);
    m_jumpItem->setData(&m_data);

    // Make sure each graph is vertically apart from each other (no overlapping)
    m_heartItem->setPos(0, 0);
    m_sweatItem->setPos(0, 1000);
    m_jumpItem->setPos(0, 2000);

    m_scene->setSceneRect(0, 0, m_heartItem->getMaxX() - m_heartItem->getMinX(), 2500);
    m_heartGraph->fitInView(m_heartItem);
    m_sweatGraph->fitInView(m_sweatItem);
    m_jumpGraph->fitInView(m_jumpItem);
    m_overlay->update();
}

/**
 * @brief Destructor
 */
TriGraph::~TriGraph()
{
    // Destructors are deceptively simple in Qt
}
