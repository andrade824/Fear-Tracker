#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_data(new FearData)
{
    ui->setupUi(this);

    connect(m_data, SIGNAL(newDataStored(FearData*)), ui->triGraph, SLOT(displayLatestData(FearData*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
