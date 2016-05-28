#include "start.h"
#include "ui_start.h"
#include <QtCore>
#include <QWidget>
#include "newtrip.h"
#include "map.h"
#include "config.h"
#include <cstdio>

start::start(Block* blocks, int r, int c, int n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    row = r;
    column = c;
    cityNum = n;
    int i, j;
    ui->gridLayout->setSpacing(30);
    for(i = 0; i < row; i ++)
	for(j = 0; j < column; j ++)
	    ui->gridLayout->addWidget(blocks + i * row + j, i, j);
//强制设置窗体大小
//    setLayout(mainLayout);
    //  setFixedSize(850,700);

    //建立时间
    sysTime.setHMS(6, 0, 0);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    timer->start(1000);
}

start::~start()
{
    delete ui;
}

void start::on_startTrip_clicked()
{
    NewTrip newTrip(cityNum);
    newTrip.exec();
}

void start::timeUpdate()
{
    sysTime = sysTime.addSecs(TIMEUNIT);
    ui->sysTimeUi->setText(sysTime.toString("HH:mm"));
}
