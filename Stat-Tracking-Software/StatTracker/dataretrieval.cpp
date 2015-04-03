#include <QDebug>
#include <QMessageBox>
#include "dataretrieval.h"

/**
 * @brief Constructor
 * @param parent The parent widget
 */
DataRetrieval::DataRetrieval(QObject *parent)
    : QObject(parent), m_serial(new QSerialPort(this)), m_numCurBytes(0)
{
    // Connect up the serial port signals
    connect(m_serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
                   SLOT(HandleError(QSerialPort::SerialPortError)));

    connect(m_serial, SIGNAL(readyRead()), this, SLOT(ReadData()));
}

/**
 * @brief Is a serial connection currently opened
 *
 * @return Returns whether a serial connection is opened
 */
bool DataRetrieval::isOpened() const
{
    return m_serial->isOpen();
}

/**
 * @brief Open a serial port connection
 * @param port The name of the port to open
 */
void DataRetrieval::OpenSerialPort(QString port)
{
    m_serial->setPortName(port);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setStopBits(QSerialPort::OneStop);

    qDebug() << "Attempting to open serial port";
    if(m_serial->open(QIODevice::ReadWrite)) {
        qDebug() << "Connected to " << m_serial->portName() << "\n";
    } else {
        QMessageBox::critical(NULL, tr("Serial Port Connection Error"), tr("Can't connect to serial device :("));
    }
}

/**
 * @brief Closes the serial port if opened
 */
void DataRetrieval::CloseSerialPort()
{
    if(m_serial->isOpen())
        m_serial->close();
}

/**
 * @brief Reads data from the serial port and stores it
 */
void DataRetrieval::ReadData()
{
    QByteArray data = m_serial->readAll();
    int headerPos = -1;
    bool keepLooping = false;

    do
    {
        keepLooping = false;

        // Wait for packet header
        if(m_numCurBytes == 0)
        {
            headerPos = data.indexOf(PACKET_HEADER);

            // We found a header!
            if(headerPos != -1)
            {
                data = data.mid(headerPos + 1);
                m_numCurBytes++;
            }
        }

        // Start filling in data
        if (m_numCurBytes != 0)
        {
            int bytesAdded = 0;
            for(; bytesAdded < data.count() && m_numCurBytes < SERIAL_NUM_BYTES; ++bytesAdded, ++m_numCurBytes)
                m_buffer.SetData(DATA_ORDER[m_numCurBytes - 1], data[bytesAdded]);

            // If buffer is full and there's still data, keep looping
            if(m_numCurBytes == SERIAL_NUM_BYTES && bytesAdded < data.count())
                keepLooping = true;

            // Send out the data if we've filled up a buffer
            if(m_numCurBytes == SERIAL_NUM_BYTES && m_buffer.GetSweat() > 5)
            {
                emit newDataRetrieved(m_buffer);
                m_numCurBytes = 0;
            }

            if(m_numCurBytes == SERIAL_NUM_BYTES)
                m_numCurBytes = 0;
        }
    } while(keepLooping);
}

/**
 * @brief Called whenever there is an error on the serial port
 *
 * @param error The error that occurred
 */
void DataRetrieval::HandleError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError) {
        QMessageBox::critical(NULL, tr("Critical Serial Port Error"), m_serial->errorString());
        CloseSerialPort();
    }
}

/**
 * @brief Close out the serial port before destructing
 */
DataRetrieval::~DataRetrieval()
{
    CloseSerialPort();
}
