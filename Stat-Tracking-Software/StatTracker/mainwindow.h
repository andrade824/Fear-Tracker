#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "feardata.h"
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
    void OpenSerialPort();

private:
    void FillPortsInfo();

private:
    Ui::MainWindow * ui;
    FearData * m_data;
    DataRetrieval * m_retrieval;
    QComboBox * m_cmbSerialPort;
    QPushButton * m_btnConnect;
};

#endif // MAINWINDOW_H
