#include "timeline.h"
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <QFont>
#include <math.h>
#include "utilities.h"

/**
 * @brief Default constructor
 *
 * @param parent The parent to this widget
 */
Timeline::Timeline(QWidget * parent)
    : QGraphicsView(parent), m_markersEnabled(false), m_leftMarkerPos(0), m_rightMarkerPos(MARKER_PADDING),
      m_leftMarkerMoving(false), m_rightMarkerMoving(false)
{
    // Set up the scene
    m_fearGraph = new GraphItem(TYPE_FEAR, Qt::gray);

    m_scene = new QGraphicsScene(this);
    m_scene->addItem(m_fearGraph);

    // Set graphics view properties
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setOptimizationFlags(QGraphicsView::DontSavePainterState | QGraphicsView::DontAdjustForAntialiasing);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Produce mouse move events when mouse is hovering
    setMouseTracking(true);

    setScene(m_scene);
}

/**
 * @brief Resize the graph item to take up the new size
 *
 * @param event The resize event
 */
void Timeline::resizeEvent(QResizeEvent * event)
{
    fitInView(m_fearGraph);

    // Window is originally set to a size of (-1,-1)
    if(event->oldSize().width() == -1)
    {
        m_leftMarkerPos = 0;
        m_rightMarkerPos = event->size().width();
    }
    else
    {
        // Relocate the markers to fit the new size
        double scale = event->size().width() / static_cast<double>(event->oldSize().width());

        m_leftMarkerPos = round(scale * m_leftMarkerPos);
        m_rightMarkerPos = round(scale * m_rightMarkerPos);
    }
    event->accept();
}

/**
 * @brief Draw the markers and labels
 */
void Timeline::paintEvent(QPaintEvent * event)
{
    // Ensure the graphics scene gets drawn
    QGraphicsView::paintEvent(event);

    // Draw the overlay
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing);

    // Setup the pen for the lines
    QPen pen(QColor("orange"));
    pen.setWidth(MARKER_WIDTH);
    painter.setPen(pen);

    // Draw markers if enabled
    if(m_markersEnabled)
    {
        painter.drawLine(m_leftMarkerPos, 0, m_leftMarkerPos, height());
        painter.drawLine(m_rightMarkerPos, 0, m_rightMarkerPos, height());

        // Only display marker labels when markers are moving
        if(m_leftMarkerMoving || m_rightMarkerMoving)
        {
            // Setup the font for the labels
            QFont font;
            font.setFamily("sans-serif");
            font.setPointSize(8);
            painter.setFont(font);

            // The strings to display
            QString leftMarkerText = Utilities::milliToTime(mapToScene(m_leftMarkerPos,0).x());
            QString rightMarkerText = Utilities::milliToTime(mapToScene(m_rightMarkerPos,0).x());

            // Draw rectangles for labels
            pen.setWidth(2);
            painter.setPen(pen);
            painter.drawRect(m_leftMarkerPos, 0, 80, 20);
            painter.drawRect(m_rightMarkerPos, 0, 80, 20);

            // Draw labels
            pen.setColor(Qt::gray);
            painter.setPen(pen);
            painter.drawText(m_leftMarkerPos + 5, 15, leftMarkerText);
            painter.drawText(m_rightMarkerPos + 5, 15, rightMarkerText);
        }
    }
}

/**
 * @brief Detect if any markers were just selected
 */
void Timeline::mousePressEvent(QMouseEvent * event)
{
    if(m_markersEnabled)
    {
        // If they clicked near the left marker, change it's state
        if(event->x() < m_leftMarkerPos + MARKER_WIDTH && event->x() > m_leftMarkerPos - MARKER_WIDTH)
            m_leftMarkerMoving = true;
        // If they clicked near the right marker, change it's state
        else if(event->x() < m_rightMarkerPos + MARKER_WIDTH && event->x() > m_rightMarkerPos - MARKER_WIDTH)
            m_rightMarkerMoving = true;
    }

    event->accept();
}

/**
 * @brief Detect if any markers are being dragged
 */
void Timeline::mouseMoveEvent(QMouseEvent * event)
{
    if(m_markersEnabled)
    {
        // Update the cursor if mouse is over marker or marker is moving
        if(m_leftMarkerMoving || m_rightMarkerMoving)
            setCursor(Qt::SplitHCursor);
        else if((event->x() < m_leftMarkerPos + MARKER_WIDTH) && (event->x() > m_leftMarkerPos - MARKER_WIDTH))
            setCursor(Qt::SplitHCursor);
        else if((event->x() < m_rightMarkerPos + MARKER_WIDTH) && (event->x() > m_rightMarkerPos - MARKER_WIDTH))
            setCursor(Qt::SplitHCursor);
        else
            setCursor(Qt::ArrowCursor);

        // Update markers
        if(m_leftMarkerMoving && event->x() < (m_rightMarkerPos - MARKER_PADDING))
            m_leftMarkerPos = event->x();
        else if(m_rightMarkerMoving && event->x() > (m_leftMarkerPos + MARKER_PADDING))
            m_rightMarkerPos = event->x();
    }

    event->accept();
}

/**
 * @brief   Detect if any markers were released and emit a signal to the graphs with the
 *          new coordinates.
 */
void Timeline::mouseReleaseEvent(QMouseEvent * event)
{
    if(m_markersEnabled)
    {
        setCursor(Qt::ArrowCursor);

        // Send out a signal saying that the markers moved
        if(m_leftMarkerMoving || m_rightMarkerMoving)
        {
            if(mapToScene(m_leftMarkerPos, 0).x() < 0)
                m_leftMarkerPos = mapFromScene(0,0).x();

            if(m_rightMarkerPos < MARKER_PADDING)
                m_rightMarkerPos = m_leftMarkerPos + MARKER_PADDING;

            if(m_rightMarkerPos > width())
                m_rightMarkerPos = width() - MARKER_WIDTH;

            if(m_leftMarkerPos > width())
                m_leftMarkerPos = m_rightMarkerPos - MARKER_PADDING;

            emit markersMoved(mapToScene(m_leftMarkerPos, 0).x(), mapToScene(m_rightMarkerPos, 0).x());
        }

        // Markers aren't moving anymore
        m_leftMarkerMoving = false;
        m_rightMarkerMoving = false;
    }

    event->accept();
}

/**
 * @brief Sets the data storage used by the graphs
 * @param data_store The storage to use
 */
void Timeline::setDataStore(FearData * data_store)
{
    m_dataStore = data_store;
}

/**
 * @brief Enable the markers for analyzing mode
 *
 * @param enabled Whether to enable the markers or not
 */
void Timeline::enableMarkers(bool enabled)
{
    m_markersEnabled = enabled;
}

/**
 * @brief Display the newest data coming from the data store.
 *
 * @param data_store The data storage module to get the data from
 */
void Timeline::displayLatestData()
{
    m_data << m_dataStore->getLatestData(1);

    m_fearGraph->setData(&m_data);
    m_scene->setSceneRect(0, 0, m_fearGraph->getMaxX() - m_fearGraph->getMinX(), m_fearGraph->getMaxY());
    fitInView(m_fearGraph);
}

/**
 * @brief Destructor
 */
Timeline::~Timeline()
{

}
