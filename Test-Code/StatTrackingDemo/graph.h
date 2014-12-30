#ifndef GRAPH_H
#define GRAPH_H

#include <QWidget>
#include <vector>

#define MAX_ITEMS 500

namespace Ui {
class Graph;
}

class Graph : public QWidget
{
    Q_OBJECT

public:
    explicit Graph(QWidget *parent = 0);
    ~Graph();

public slots:
    void AddData(QByteArray & data);

private:
    Ui::Graph *ui;
    QPointF dataList[MAX_ITEMS];
    int cur_item;
    void paintEvent(QPaintEvent *);
};

#endif // GRAPH_H
