#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QSerialPortInfo>
#include <QScrollBar>

/**
 * @brief Constructor that sets up port information and connects any needed signals
 *
 * @param parent The parent of this window
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    serial(new QSerialPort(this)),
    graph(new Graph(this))
{
    ui->setupUi(this);

    FillPortsInfo();

    ui->verticalLayout->addWidget(graph);

    connect(serial, SIGNAL(error(QSerialPort::SerialPortError)), this,
               SLOT(HandleError(QSerialPort::SerialPortError)));

    connect(serial, SIGNAL(readyRead()), this, SLOT(ReadData()));

    connect(ui->btnConnect, SIGNAL(clicked()), this, SLOT(OpenSerialPort()));
}

/**
 * @brief Opens up a serial port based one the selected port in the
 *         serial port combo box
 */
void MainWindow::OpenSerialPort()
{
    serial->setPortName(ui->cmbSerialPort->currentText());
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);

    qDebug() << "Attempting to open serial port";
    if(serial->open(QIODevice::ReadWrite)) {
        ui->cmbSerialPort->setEnabled(false);
        qDebug() << "Connected to " << serial->portName() << "\n";
    } else {
        QMessageBox::critical(this, tr("Error D:"), tr("Can't connect :("));
    }
}

/**
 * @brief Closes the currently open serial port
 */
void MainWindow::CloseSerialPort()
{
    qDebug() << "Closing Serial Port: " << serial->portName();
    serial->close();
}

/**
 * @brief Fills the serial port combo box with the available port names
 */
void MainWindow::FillPortsInfo()
{
    ui->cmbSerialPort->clear();

    // Populate serial port combo box
    qDebug() << "Available Ports:";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "System Location: " << info.systemLocation() << "\n";

        ui->cmbSerialPort->addItem(info.portName());
    }
}

/**
 * @brief Reads a variable number of bytes from the serial port
 *         and prints the data out to the screen.
 */
void MainWindow::ReadData()
{
    QByteArray data = serial->readAll();
    qDebug() << "Data: " << QString(data);
    /*ui->pteConsole->insertPlainText(QString(data));

    // Auto-scroll the text edit
    QScrollBar * sb = ui->pteConsole->verticalScrollBar();
    sb->setValue(sb->maximum());*/

    graph->AddData(data);
}

void MainWindow::WriteData(const QByteArray & data)
{
    serial->write(data);
}

/**
 * @brief This slot is called if an error occurs while receiving or transmitting data serially
 * @param error The error that occurred
 */
void MainWindow::HandleError(QSerialPort::SerialPortError error)
{
    if(error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        CloseSerialPort();
    }
}

/**
 * @brief Makes sure any open serial ports are closed and that UI is destroyed
 */
MainWindow::~MainWindow()
{
    CloseSerialPort();
    delete ui;
}

/**
 * @brief File->Exit action
 */
void MainWindow::on_actionExit_triggered()
{
    this->close();
}
