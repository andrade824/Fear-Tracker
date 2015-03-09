#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
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

    ui->triGraph->setDataStore(m_data);
    ui->timeline->setDataStore(m_data);

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
    connect(ui->triGraph, SIGNAL(dataHovered(FearDataNode)), this, SLOT(displayHoveredData(FearDataNode)));
    connect(ui->triGraph, SIGNAL(noHovering()), this, SLOT(clearHovereredData()));
    connect(ui->timeline, SIGNAL(markersMoved(quint64,quint64)), ui->triGraph, SLOT(getAnalyzeData(quint64,quint64)));
    connect(m_data, SIGNAL(newDataStored(FearData*)), ui->triGraph, SLOT(getRealtimeData()));
    connect(m_data, SIGNAL(newDataStored(FearData*)), ui->timeline, SLOT(displayLatestData()));
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

/**
 * @brief Display data about the node that's currently being hovered over
 *
 * @param data The node who's info to display
 */
void MainWindow::displayHoveredData(FearDataNode data)
{
    ui->leTime->setText(Utilities::milliToTime(data.GetTime()));
    ui->leHeartRate->setText(QString::number(data.GetHeartRate()));
    ui->leSweat->setText(QString::number(data.GetSweat()));
    ui->leAccel->setText(QString::number(data.GetAccelLevel()));
    ui->leFearScore->setText(QString::number(data.GetFearLevel()));
}

/**
 * @brief Clear out the textboxes used for displaying hovered data
 */
void MainWindow::clearHovereredData()
{
    ui->leTime->setText("");
    ui->leHeartRate->setText("");
    ui->leSweat->setText("");
    ui->leAccel->setText("");
    ui->leFearScore->setText("");
}

/**
 * @brief Fill the serial ports combo box with all available serial ports
 */
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

/**
 * @brief Close the window on File->Exit
 */
void MainWindow::on_action_Exit_triggered()
{
    this->close();
}

/**
 * @brief Switches between Real-time mode and analyzing mode
 *
 * @param mode True if in real-time mode
 */
void MainWindow::on_actionChange_Mode_toggled(bool mode)
{
    // Real-time mode
    if(mode)
    {
        ui->actionChange_Mode->setText("Analyze Mode");
        ui->triGraph->setMode(TriGraph::MODE_REALTIME);
        ui->timeline->enableMarkers(false);
    }
    // Analyze mode
    else
    {
        ui->actionChange_Mode->setText("Real-time Mode");
        ui->triGraph->setMode(TriGraph::MODE_ANAYLZE);
        ui->timeline->enableMarkers(true);
    }
}
