#include <QPainter>
#include <QPen>
#include <QFont>
#include "trigraphoverlay.h"
#include "graphitem.h"
#include "utilities.h"

/**
 * @brief Constructor that defines every value
 * @param xoffset How far from the left side of the trigraph to start drawing the graphs
 * @param xPixelPerUnit How many pixels each x-label should be separated by
 * @param heartGraph The QGraphicsView representing the heartrate graph
 * @param sweatGraph The QGraphicsView representing the sweat graph
 * @param jumpGraph The QGraphicsView representing the jump graph
 * @param heartItem The GraphItem representing the heartrate graph
 * @param sweatItem The GraphItem representing the sweat graph
 * @param jumpItem The GraphItem representing the jump graph
 * @param parent The parent widget
 */
TriGraphOverlay::TriGraphOverlay(int xoffset, int xPixelPerUnit, QGraphicsView * heartGraph, QGraphicsView * sweatGraph,
                                 QGraphicsView * jumpGraph, GraphItem * heartItem, GraphItem * sweatItem, GraphItem * jumpItem, QWidget * parent)
    : QWidget(parent), m_xoffset(xoffset), m_xPixelsPerLabel(xPixelPerUnit), m_heartGraph(heartGraph), m_sweatGraph(sweatGraph), m_jumpGraph(jumpGraph),
      m_heartItem(heartItem), m_sweatItem(sweatItem), m_jumpItem(jumpItem)
{
    setPalette(Qt::transparent);
    setAttribute(Qt::WA_TransparentForMouseEvents);
}

/**
 * @brief Draw the labels and lines for every graph
 */
void TriGraphOverlay::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::gray));

    QFont font;
    font.setFamily("sans-serif");
    font.setPointSize(8);
    painter.setFont(font);

    int thirdHeight = height() / 3;

    // Draw X-axis lines and labels
    for(int i = m_xPixelsPerLabel; i + m_xoffset < width(); i += m_xPixelsPerLabel)
    {
        QString timeText = Utilities::milliToTime(m_heartGraph->mapToScene(i, 0).x() + m_heartItem->getMinX());
        painter.drawLine(i + m_xoffset, 0, i + m_xoffset, height());
        painter.drawText(i + m_xoffset + 3, thirdHeight - 5, timeText);
        painter.drawText(i + m_xoffset + 3, thirdHeight + thirdHeight - 5, timeText);
        painter.drawText(i + m_xoffset + 3, thirdHeight + thirdHeight + thirdHeight - 5, timeText);
    }

    // Draw the Y labels for each graph
    drawYLabels(&painter, m_heartItem, thirdHeight);
    drawYLabels(&painter, m_sweatItem, thirdHeight * 2);
    drawYLabels(&painter, m_jumpItem, thirdHeight * 3);

    // Draw hover marker
    if(m_hoverMarkerEnabled)
    {
        QPen hoverpen(QColor("orange"));
        hoverpen.setWidth(3);
        painter.setPen(hoverpen);
        painter.drawLine(m_hoverMarkerPos + m_xoffset + 1, 0, m_hoverMarkerPos + m_xoffset + 1, height());
    }
}

/**
 * @brief Draws the y labels for a single GraphItem
 *
 * @param painter The painter object to draw the labels with
 * @param graph The graph to draw labels on top of
 * @param yoffset The yoffset from the top within the trigraph the passed in graph is
 */
void TriGraphOverlay::drawYLabels(QPainter * painter, GraphItem * graph, int yoffset)
{
    int thirdHeight = height() / 3;
    int range = graph->getMaxY() - graph->getMinY();
    int numLabels = 0;
    int unitsPerLabel = 0;
    float pixelPerLabel = 0.0f;

    // Determine number of labels
    if(range >= 10 && range <= 20)
        numLabels = 5;
    else if (range < 10)
        numLabels = range;
    else
        numLabels = 10;

    if(numLabels > 1)
    {
        // Determine how many units each label represents
        unitsPerLabel = range / (numLabels - 1);

        // Determine how many pixels inbetween each label
        pixelPerLabel = thirdHeight / static_cast<float>(numLabels);

        // Draw Heartrate graph Y labels
        for(float i = pixelPerLabel, num = 1; num < numLabels; i += pixelPerLabel, num++)
        {
            painter->drawLine(m_xoffset - 5, yoffset - i, m_xoffset + 5, yoffset - i);
            painter->drawText(m_xoffset - 25, yoffset - i + 5, QString::number(unitsPerLabel * num + graph->getMinY()));
        }
    }
}

/**
 * @brief Display the hover marker over the provided data node
 * @param node The node to hover over
 */
void TriGraphOverlay::displayHoverMarker(FearDataNode node)
{
    m_hoverMarkerEnabled = true;
    m_hoverMarkerPos = m_heartGraph->mapFromScene(node.GetTime() - m_heartItem->getMinX(), 0).x();
    update();
}

/**
 * @brief Disable the hover marker
 */
void TriGraphOverlay::disableHoverMarker()
{
    m_hoverMarkerEnabled = false;
    update();
}

/**
 * @brief Destructor
 */
TriGraphOverlay::~TriGraphOverlay()
{

}
