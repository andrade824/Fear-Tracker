#ifndef FEARDATA_H
#define FEARDATA_H

#include <QObject>
#include <QVariant>

#include "feardatanode.h"

class FearData : public QObject
{
    Q_OBJECT

public:
    // Default Constructor
    explicit FearData(QObject *parent = 0);

    // Returns the item at the specified index
    Q_INVOKABLE FearDataNode * getDataNode(int index) const;

    // Returns the item at the specified index
    Q_INVOKABLE QVariantList getLatestData(int type, int num_data_nodes) const;

    // Returns the number of nodes currently being stored
    Q_INVOKABLE int countDataNode() const;

    // Adds a node to the data store
    void AddData(FearDataNode * data);

    Q_INVOKABLE void addGarbage();

    // Destructor
    ~FearData();

signals:

public slots:

private:
    QList<FearDataNode *> m_data;   // A list of all data nodes
    qint64 m_starttime;
};

#endif // FEARDATA_H
