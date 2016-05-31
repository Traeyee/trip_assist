#include "start.h"
#include "ui_start.h"
#include <QtCore>
#include <QWidget>
#include "newtrip.h"
#include "map.h"
#include "config.h"
#include <cstdio>
#include <QPainter>



start::start(Block* blocks, int r, int c, int n, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    row = r;
    column = c;
    cityNum = n;
    int i, j;
    ui->gridLayout->setSpacing(0);
    for(i = 0; i < row; i ++)
    for(j = 0; j < column; j ++)
        ui->gridLayout->addWidget(blocks + i * row + j, i, j);
//强制设置窗体大小
//    setLayout(mainLayout);
  //setFixedSize(510,450);

    //建立时间
    sysTime.setHMS(6, 0, 0);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    timer->start(1000);
    //ui->statusBar->showMessage(tr("Coded by sosuke"));
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

void start::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //设置一个矩形
    QRectF rect(10, 10, 490, 401);
    painter.drawRect(rect);
   // painter.setPen(QColor(Qt::red));
   // painter.drawText(rect, Qt::AlignHCenter, "yafeilinux");

    QPixmap pix;
    pix.load("../painter_1/piano.png");
    painter.drawPixmap(800, 800, 500, 500, pix);
    painter.setPen(QColor(Qt::red));
    painter.drawText(410,80,"开启新的旅程吧！");
}
