#include "graph.h"
#include "ui_graph.h"
#include <QPainter>
#include <cstring>

Graph::Graph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Graph),
    cur_item(0)
{
    QPointF dummy(0.0, 255.0);
    for(int i = 0; i < MAX_ITEMS; ++i)
        dataList[i] = dummy;

    ui->setupUi(this);
}

void Graph::AddData(QByteArray & data)
{
    for(int i = 0; i < data.size(); ++i)
    {
        dataList[cur_item] = QPointF(cur_item, static_cast<unsigned char>(data.at(i)));
        if(++cur_item == MAX_ITEMS)
            cur_item = 0;
    }
}

void Graph::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setWindow(0, 0, MAX_ITEMS, 256);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawPolyline(dataList, MAX_ITEMS);

    update();
}

Graph::~Graph()
{
    delete ui;
}
