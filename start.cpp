#include "start.h"
#include "ui_start.h"
#include <QtCore>
#include <QWidget>
#include "newtrip.h"
#include "map.h"
#include "config.h"
#include "inquiry.h"
#include <cstdio>
#include <QPainter>
#include <QLabel>
#include <QMovie>
#include <QTime>
#include <QtGui>
#include <fstream>

extern QDateTime dateTime;
extern ofstream output;
/*void gifplay(QLabel*label)
{
    label->show();
}
void gifclose(QLabel*label)
{
    label->close();
}
*/
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
    {
	for(j = 0; j < column; j ++)
	{
	    blocks[i * COLUMN + j].setP(i * COLUMN + j);
	    ui->gridLayout->addWidget(blocks + i * COLUMN + j, i, j);
	}
    }
//强制设置窗体大小
//    setLayout(mainLayout);
  //setFixedSize(510,450);

    //建立时间
    sysTime.setHMS(6, 0, 0);
    dateTime.setTime(sysTime);
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timeUpdate()));
    timer->start(1000);
/*
    //开启动画
    QMovie*movie;
    movie = new QMovie("E:/Coding/workspace/Sosuke_trip_maker/pic/GIF1.gif");
    QLabel *label = new QLabel ("",0);
    label->setGeometry(300,300,500,500);
    label->setMovie(movie);
    label->setScaledContents(true);
    movie->start();
    gifplay(label);
    t.start();
    while(t.elapsed()<5000)
    {
        QApplication::processEvents();
    }
    gifclose(label);

    return a.exec();
*/


    //贴动态图
    QMovie*movie =new QMovie(":/pic/GIF1.gif");
    ui->label_2->setMovie(movie);
    movie->start();

    QMovie*movie1 =new QMovie(":/pic/text.gif");
    ui->label->setMovie(movie1);
    movie1->start();

    //按钮效果
    ui->startTrip->setStyleSheet("QPushButton{border-image: url(:/pic/樱花1.png);}"
                                "QPushButton:hover{border-image: url(:/pic/樱花2.png);}");



    ui->inquiry->setStyleSheet("QPushButton{border-image: url(:/pic/樱花3.png);}"
                               "QPushButton:hover{border-image: url(:/pic/樱花4.png);}");


}

start::~start()
{
    output << "本次服务结束" << endl;
    output.close();
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
    dateTime = dateTime.addSecs(TIMEUNIT);
    ui->sysTimeUi->setText(dateTime.toString("yyyy/MM/dd HH:mm"));
}

/*
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
*/

void start::on_inquiry_clicked()
{
    Inquiry i;
    i.exec();
}
