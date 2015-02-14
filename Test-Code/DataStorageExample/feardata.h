#ifndef FEARDATA_H
#define FEARDATA_H

#include <QObject>
#include <QQmlListProperty>

#include "feardatanode.h"

class FearData : public QObject
{
    Q_OBJECT

public:
    // Default Constructor
    explicit FearData(QObject *parent = 0);

    // Returns the item at the specified index
    Q_INVOKABLE FearDataNode * atDataNode(int index) const;

    // Returns the number of nodes currently being stored
    Q_INVOKABLE int countDataNode() const;

    // Adds a node to the data store
    void AddData(FearDataNode * data);

    // Destructor
    ~FearData();

signals:

public slots:

private:
    QList<FearDataNode *> m_data;   // A list of all data nodes
};

#endif // FEARDATA_H
