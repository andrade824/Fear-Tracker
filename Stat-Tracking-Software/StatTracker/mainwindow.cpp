#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QSerialPortInfo>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_data(new FearData(this)),
    m_retrieval(new DataRetrieval(this))
{
    ui->setupUi(this);

    // Setup the serial ports combo box
    m_cmbSerialPort = new QComboBox(ui->statusBar);
    ui->statusBar->addPermanentWidget(m_cmbSerialPort);

    // Setup the connect button
    m_btnConnect = new QPushButton(ui->statusBar);
    m_btnConnect->setText("Connect");
    ui->statusBar->addPermanentWidget(m_btnConnect);

    // Fill in the ports combo box
    FillPortsInfo();

    // Connect everything up
    connect(m_data, SIGNAL(newDataStored(FearData*)), ui->triGraph, SLOT(displayLatestData(FearData*)));
    connect(m_retrieval, SIGNAL(newDataRetrieved(FearDataNode)), m_data, SLOT(AddData(FearDataNode)));
    connect(m_btnConnect, SIGNAL(clicked()), this, SLOT(OpenSerialPort()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OpenSerialPort()
{
    m_retrieval->OpenSerialPort(m_cmbSerialPort->currentText());
    m_btnConnect->setEnabled(false);
}

void MainWindow::FillPortsInfo()
{
    m_cmbSerialPort->clear();

    // Populate serial port combo box
    qDebug() << "Available Ports:";
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        qDebug() << "Name        : " << info.portName();
        qDebug() << "Description : " << info.description();
        qDebug() << "Manufacturer: " << info.manufacturer();
        qDebug() << "System Location: " << info.systemLocation() << "\n";

        m_cmbSerialPort->addItem(info.portName());
    }

    if(m_cmbSerialPort->count() == 0)
    {
        m_cmbSerialPort->addItem("No Serial Ports");
        m_cmbSerialPort->setEnabled(false);
        m_btnConnect->setEnabled(false);
    }
}
