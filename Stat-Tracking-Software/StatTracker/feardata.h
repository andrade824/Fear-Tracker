#ifndef FEARDATA_H
#define FEARDATA_H

#include <QObject>
#include <QVariant>
#include <QTimer>

#include "feardatanode.h"

class FearData : public QObject
{
    Q_OBJECT

public:
    // Default Constructor
    explicit FearData(QObject *parent = 0);

    // Returns the item at the specified index
    FearDataNode getDataNode(int index) const;

    // Returns a list with the latest nodes
    QList<FearDataNode> getLatestData(int num_data_nodes) const;

    // Return a list of all the nodes between the two times
    QList<FearDataNode> getData(quint64 start, quint64 end) const;

    // Returns the number of nodes currently being stored
    int countDataNodes() const;

    // Destructor
    ~FearData();

signals:
    // This signal is emitted every time new data is stored
    void newDataStored(FearData *);

public slots:
    // Adds random garbage data for testing purposes
    void addGarbage();

    // Adds a node to the data store
    void AddData(FearDataNode data);

private:
    QList<FearDataNode> m_data; // A list of all data nodes
    qint64 m_starttime;         // When data started recording
    QTimer * m_timer;           // A timer used to add garbage data
};

#endif // FEARDATA_H
