#include "newtrip.h"
#include "ui_newtrip.h"
#include "config.h"
#include <QVBoxLayout>
#include <QDebug>
#include "map.h"
#include "inquiry.h"
#include <QtGui>
#include <QTime>
#include <QMessageBox>

extern int cityCount;
extern int routeCount;
extern int seq;
extern Customer customer[15];
extern Route route[50];
extern int custOnWay[15];
//extern Linker* linker;
extern Block* theMap;

static int rc[20][20];

NewTrip::NewTrip(int n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
    
    int i, j;
    for(i = 0; i < 11; i ++)
    {
	for(j = 0; j < n; j ++)	
	    midP[i].addItem(QString("%1").arg(j, 2, 10, QLatin1Char('0')));

	midP[i].setCurrentIndex(-1);
	ui->cityLayout->addWidget(midP + i);
    }

    //按钮效果
    ui->OK->setStyleSheet("QPushButton{border-image: url(:/pic/button5.png);}"
			  "QPushButton:hover{border-image: url(:/pic/button6.png);}");



    ui->exit->setStyleSheet("QPushButton{border-image: url(:/pic/button3.png);}"
			    "QPushButton:hover{border-image: url(:/pic/button4.png);}");
    
}

NewTrip::~NewTrip()
{
    delete ui;
}

int priceDijstra(int src, int dest, Route* route1, int* cm)//价格优先策略
{
    int c[20][20];
    int v[20] = {0}, prev[20] = {0}, d[20];
    int i, j, k, flagg, temp;
    
    for(i = 0; i < cityCount; i ++)
    {
	for(j = 0; j < cityCount; j ++)
	    c[i][j] = INF;
	c[i][i] = 0;
    }
    for(i = 0; i < routeCount; i ++)
	if(route1[i].price < c[route1[i].startCity][route1[i].endCity])
	{
	    c[route1[i].startCity][route1[i].endCity] = route1[i].price;
	    rc[route1[i].startCity][route1[i].endCity] = i;
//	    qDebug() << route1[i].startCity << " " << route1[i].endCity << " RC " << i  << " " << rc[route1[i].startCity][route1[i].endCity]<< endl;
	}
    for(i = 0; i < cityCount; i ++)
    {
	if(c[src][i] >= 0)
	{
	    d[i] = c[src][i];
	    prev[i] = src;
	}
	else
	    d[i] = INF;
    }
    d[src] = 0;
    v[src] = 1;
    for(k = 1; k < cityCount; k++)
    {
	temp = INF;
	for(i = 0; i < cityCount; i ++)	
	    if(! v[i] && d[i] < temp)
	    {
		temp = d[i];
		flagg = i;
	    }

	v[flagg] = 1;
	for(i = 0; i < cityCount; i ++)	
	    if(! v[i])	    
		if(d[flagg] + c[flagg][i] < d[i])
		{
		    d[i] = d[flagg] + c[flagg][i];
		    prev[i] = flagg;
		}	
    }
    
    int n = 0;
    temp = dest;
    while(temp != prev[temp])
    {
	n ++;
	temp = prev[temp];
    }
    for(i = n - 1, temp = dest; i >= 0; i --)
    {
//	qDebug() << rc[prev[temp]][temp] << endl;
	cm[i] = rc[prev[temp]][temp];
	temp = prev[temp];
    }
    
    return n;
}
int timeLimDijstra(int src, int dest, Route* route1, int* cm)//限制时间策略
{
    return priceDijstra(src, dest, route1, cm);
}
int timeDijstra(int src, int dest, Route* route1, int* cm)//时间优先策略
{
    int c[20][20], d[20], temp;
    int v[20] = {0}, prev[20] = {0};
    int i, j, k, flagg;
    bool notFound = false;
    QTime endTime[20], standard;

    standard.setHMS(0, 0, 0);
    for(i = 0; i < cityCount; i ++)
    {
	for(j = 0; j < cityCount; j ++)
	    c[i][j] = INF;
	c[i][i] = 0;
    }
    for(i = 0; i < routeCount; i ++)
    {
	temp = route1[i].dist * ((int)route1[i].kind) * TIMEUNIT;
	if(temp < c[route1[i].startCity][route1[i].endCity])
	{
	    c[route1[i].startCity][route1[i].endCity] = temp;
	    rc[route1[i].startCity][route1[i].endCity] = i;
//	    qDebug() << route1[i].startCity << " " << route1[i].endCity << " RC " << i  << " " << rc[route1[i].startCity][route1[i].endCity]<< endl;
	}
    }
    prev[src] = src;
    v[src] = 1;
    k = src;
    while(c[k][dest] >= INF)
    {
	temp = INF;
	flagg = k;
	for(i = 0; i < cityCount; i ++)
	    if((!v[i]) && c[k][i] < temp)
	    {
		temp = c[k][i];
		flagg = i;
	    }
	if(k == flagg)
	    return priceDijstra(src, dest, route1, cm);
	v[flagg] = 1;
	prev[flagg] = k;
	k = flagg;
    }
    v[dest] = 1;
    prev[dest] = k;
    
    int n = 0;
    k = dest;
    while(k != prev[k])
    {
	n ++;
	k = prev[k];
    }
    for(i = n - 1, k = dest; i >= 0; i --)
    {
//	qDebug() << rc[prev[k]][k] << endl;
	cm[i] = rc[prev[k]][k];
	k = prev[k];
    }
    
    return n;
}

void NewTrip::on_NewTrip_accepted()
{
    int stra = 0;
    if(ui->priceBtn->isChecked())
	stra = 1;
    else if(ui->timeBtn->isChecked())
	stra = 2;
    else if(ui->mixBtn->isChecked())
	stra = 3;
    int i, j, k;
    for(i = 0, k = 0; i < 11; i = j)
    {
	j = i + 1;
	if(midP[i].currentIndex() == -1)
	    continue;
	else
	{
	    while(midP[j].currentIndex() == -1 && j < 11)
		j ++;
	    if(j < 11)
	    {
		switch(stra)
		{
		case 1:
		    k += priceDijstra(midP[i].currentIndex(), midP[j].currentIndex(), route, customer[seq].rt + k);
		    break;
		case 2:
		    k += timeDijstra(midP[i].currentIndex(), midP[j].currentIndex(), route, customer[seq].rt + k);
		    break;
		case 3:
		    k += timeLimDijstra(midP[i].currentIndex(), midP[j].currentIndex(), route, customer[seq].rt + k);
		    break;
		}
	    }
	}
    }
    qDebug() << seq << " seq " << k << endl;
    customer[seq].rt[k] = -1;
    customer[seq].mn += route[customer[seq].rt[0]].price;
    customer[seq].durTime += (int)route[customer[seq].rt[0]].kind * route[customer[seq].rt[0]].dist * TIMEUNIT;
    QTime endTime(route[customer[seq].rt[0]].end.hour(), route[customer[seq].rt[0]].end.minute());
    for(i = 1; customer[seq].rt[i] != -1; i++)
    {
	customer[seq].mn += route[customer[seq].rt[i]].price;
	customer[seq].durTime += difTime(route[customer[seq].rt[i]].begin, endTime);
	endTime = route[customer[seq].rt[i]].end;
    }

    if(stra == 3 && customer[seq].durTime > ui->hs->value() * 3600 + ui->mins->value() * 60)
    {
	if (QMessageBox::Yes == QMessageBox::question(this,
						      tr("注意"),
						      tr("不存在符合要求的路径！"),
						      QMessageBox::Yes | QMessageBox::No,
						      QMessageBox::Yes))
	    1;/*
	else {
	    QMessageBox::information(this, tr("Hmmm..."), tr("I'm sorry!"));
	    }*/
    }
    else
    {
	custOnWay[seq] = 1;
	OneTrip* o1 = new OneTrip(seq);
//    qDebug() << "DDD" << endl;
	for(i = 0; i < ROW * COLUMN; i ++)
	    QObject::connect(o1, SIGNAL(move(int, unsigned char)), theMap + i, SLOT(update(int, unsigned char)));
//    QObject::connect(o1, SIGNAL(move(int, unsigned char)), linker, SLOT(updateBlock(int, unsigned char)));    
//    qDebug() << "EEE" << endl;
	o1->start();
    
	seq = (seq + 1) % 11;
    }
}
