#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newtrip.h"
#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTimer *theTimer = new QTimer(this);
    connect(theTimer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    theTimer->start(3000);
    ui->LcdTimer->setDigitCount(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartTrip_clicked()
{
    NewTrip n;
    n.exec();
}
void MainWindow::timerUpdate()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    QString strTime = dateTime.toString("yyyy-MM-dd hh:mm:ss dddd");
    ui->TimeLabel->setText(strTime);
    ui->LcdTimer->display(strTime);
}
