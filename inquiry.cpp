#include "inquiry.h"
#include "ui_inquiry.h"
#include "config.h"
#include <QDebug>
#include <QTextEdit>
#include "map.h"

extern Customer customer[15];
extern int custOnWay[15];
extern Route route[50];

Inquiry::Inquiry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inquiry)
{
    ui->setupUi(this);

    int i, j;
    for(i = 0; i < 11; i ++)
	ui->customBox->addItem(QString("%1").arg(i, 2, 10, QLatin1Char('0')));
    context = new QTextEdit;


    //按钮效果
    ui->iqr->setStyleSheet("QPushButton{border-image: url(:/pic/樱花3.png);}"
                               "QPushButton:hover{border-image: url(:/pic/樱花4.png);}");
}

Inquiry::~Inquiry()
{
    delete ui;
    delete context;
}
/*
void comboxUpdate()
{
    
}
*/

void Inquiry::on_iqr_clicked()
{
    int i, j, k;
    if(!custOnWay[ui->customBox->currentIndex()])
	context->setText(QString("Not on the way!"));


    else
    {	
	i = 0;
	k = ui->customBox->currentIndex();
	QString str("");

	str = str + QString("乘客当前城市：%1\n").arg(route[customer[k].tripNo].startCity, 2, 10, QLatin1Char('0'));
	str = str + QString("乘客于班次%1上 ").arg(customer[k].tripNo, 2, 10, QLatin1Char('0'));
	str = str + QString("乘客将乘坐");
	switch(route[customer[k].tripNo].kind)
	{
	case AIR:
	    str = str + QString("飞机");
	    break;
	case RAIL:
	    str = str + QString("火车");
	    break;
	case ROAD:
	    str = str + QString("汽车");
	    break;
	}
	str = str + QString("\n\n");
	
	while(customer[k].rt[i] != -1)
	{
	    str = str + QString("班次：%1  ").arg(customer[k].rt[i], 2, 10, QLatin1Char('0'));
	    str = str + QString("起点：%1  ").arg(route[customer[k].rt[i]].startCity, 2, 10, QLatin1Char('0'));
	    str = str + QString("终点：%1\n").arg(route[customer[k].rt[i]].endCity, 2, 10, QLatin1Char('0'));
	    str = str + QString("交通工具：");
	    switch(route[customer[k].rt[i]].kind)
	    {
	    case 1:
		str = str + QString("飞机  ");
		break;
	    case 2:
		str = str + QString("火车  ");
		break;
	    case 3:
		str = str + QString("汽车  ");
		break;
	    }
	    str = str + QString("价格：%1\n").arg(route[customer[k].rt[i]].price, 2, 10, QLatin1Char('0'));
	    str = str + QString("开始时间：") + route[customer[k].rt[i]].begin.toString("HH:mm  ");
	    str = str + QString("结束时间：") + route[customer[k].rt[i]].end.toString("HH:mm\n\n");
	    i ++;
	}
	context->setText(str);

	ui->moneyCost->setText(QString("%1元").arg(customer[k].mn));
	QTime temp(0, 0, customer[k].durTime);
	ui->timeCost->setText(QString("%1小时%2分钟").arg(customer[k].durTime / 3600).arg(customer[k].durTime % 3600 / 60));
    }
    
    ui->screen->setBackgroundRole(QPalette::Dark);
    context->setReadOnly(true);
    ui->screen->setWidget(context);
    ui->screen->show();

    
}
