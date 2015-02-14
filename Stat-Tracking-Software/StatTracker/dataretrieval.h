#ifndef DATARETRIEVAL_H
#define DATARETRIEVAL_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include "feardatanode.h"
#include "feartype.h"

// Number of bytes in a single packet of data
const short SERIAL_NUM_BYTES = 5;

// The byte that starts off a packet
const quint8 PACKET_HEADER = 0xAA;

// The order of the data
const FearType DATA_ORDER[] = { TYPE_JUMP, TYPE_HEART, TYPE_SWEAT, TYPE_FEAR };

class DataRetrieval : public QObject
{
    Q_OBJECT
public:
    // Constructor
    explicit DataRetrieval(QObject *parent = 0);

    // Is a serial connection currently opened
    bool isOpened() const;

    // Destructor
    ~DataRetrieval();

signals:
    // Emitted whenever a full packet of data has been received
    void newDataRetrieved(FearDataNode data);

public slots:
    // Open up a port for reading
    void OpenSerialPort(QString port);

    // Close a serial port connection
    void CloseSerialPort();

private slots:
    // Called when new data is available on the serial port
    void ReadData();

    // Called whenever there's an error on the serial port
    void HandleError(QSerialPort::SerialPortError error);

private:
    QSerialPort * m_serial; // The serial port
    FearDataNode m_buffer;  // A buffer for data that isn't completely received
    int m_numCurBytes;      // How many bytes have been received since the last packet
};

#endif // DATARETRIEVAL_H
