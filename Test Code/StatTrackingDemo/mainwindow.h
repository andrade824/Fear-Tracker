#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtSerialPort/QtSerialPort>

#include "graph.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void FillPortsInfo();

public slots:
    void OpenSerialPort();
    void CloseSerialPort();

private slots:
    void WriteData(const QByteArray & data);
    void ReadData();

    void HandleError(QSerialPort::SerialPortError error);

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QSerialPort * serial;
    Graph * graph;
};

#endif // MAINWINDOW_H
