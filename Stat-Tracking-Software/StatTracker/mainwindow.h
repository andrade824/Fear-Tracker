#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "feardata.h"
#include "feardatanode.h"
#include "dataretrieval.h"
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = 0);
    ~MainWindow();

public slots:
    // Open up a serial port
    void OpenSerialPort();

    // Display data about the node being hovered over
    void displayHoveredData(FearDataNode data);

    // Clear out the textboxes used for the hovered data
    void clearHovereredData();

private slots:
    // Close the window on File->Exit
    void on_action_Exit_triggered();

    // Set which mode the graphs are in
    void on_actionChange_Mode_toggled(bool mode);

private:
    // Fill a combo box with information about every serial port
    void FillPortsInfo();

private:
    Ui::MainWindow * ui;
    FearData * m_data;
    DataRetrieval * m_retrieval;
    QComboBox * m_cmbSerialPort;
    QPushButton * m_btnConnect;
};

#endif // MAINWINDOW_H
