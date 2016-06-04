#include <QWidget>
#include <fstream>
#include <QGridLayout>
#include "map.h"
#include "inquiry.h"
#include <QDebug>
#include <sstream>
using namespace std;

int cityCount;
int routeCount;
int seq;
Customer customer[15];
QDateTime dateTime;
Route route[50];
int custOnWay[15];
//Linker* linker;
Block* theMap;
/*
void Linker::run()
{
    while(1)
	sleep(1);
}
*/
Block::Block(QWidget *parent) :
    QLabel(parent)
{
    No = -1;
    isCity = false;
    tripping = false;
    setPixmap(QPixmap(":/images/0"));
}

void Block::setting(int N, int isCit)
{
    No = N;
    if(isCit)
    {
	isCity = true;
	setPixmap(QPixmap(":/c" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
    }
    else
	setPixmap(QPixmap(":/images/" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
}
void Block::setP(int P) {
    position = P;
}
void Block::update(int noo, unsigned char k)
{
    if(noo == position)
    {
	if(tripping)
	{
	    if(No == -1)
	        setPixmap(QPixmap(":/images/0"));
	    else
	    {
		if(isCity)
		    setPixmap(QPixmap(":/c" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
		else
		    setPixmap(QPixmap(":/images/" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
	    }
	    tripping = false;
	}
	else
	{
	    QString temp("");
	    switch(k)
	    {
	    case 1:
		temp = temp + QString("x");
		break;
	    case 2:
		temp = temp + QString("y");
		break;
	    case 3:
		temp = temp + QString("z");
		break;
	    }
	    if(No == -1)
	        setPixmap(QPixmap(":/qrc/" + temp + "0.png"));
	    else
	    {
		if(isCity)
		    setPixmap(QPixmap(":/qrc/" + temp + "c" + QString("%1").arg(No, 2, 10, QLatin1Char('0')) + ".png"));
		else
		    setPixmap(QPixmap(":/qrc/" + temp  + QString("%1").arg(No, 2, 10, QLatin1Char('0')) + ".png"));
	    }
	    tripping = true;
	}
    }
}

OneTrip::OneTrip(int seqq)
{
    number = seqq;
    routeSeq = 0;
    position = -1;
}

void OneTrip::run()
{
    /*
    QTimer* timer = new QTimer;
    connect(timer, SIGNAL(timeout()), this, SLOT(routeUpdate()));
    */
//    qDebug() << "THREAD\n" ;
    int i;
    QTime temp;
    for(;customer[number].rt[routeSeq] != -1; routeSeq ++)
    {	
	temp = dateTime.time();
	sleep(difTime(route[customer[number].rt[routeSeq]].begin, temp) / TIMEUNIT);
	qDebug() << "HHHH" << endl;
	switch(route[customer[number].rt[routeSeq]].kind)
	{
	case AIR:
	    for(i = 0; i < route[customer[number].rt[routeSeq]].dist; i ++)
	    {
		position = route[customer[number].rt[routeSeq]].step[i];
		emit move(position, route[customer[number].rt[routeSeq]].kind);
		sleep(1);
		emit move(position, route[customer[number].rt[routeSeq]].kind);
	    }
	    break;
	case RAIL:
	    for(i = 0; i < route[customer[number].rt[routeSeq]].dist; i ++)
	    {
		position = route[customer[number].rt[routeSeq]].step[i];
		emit move(position, route[customer[number].rt[routeSeq]].kind);
		sleep(2);
		emit move(position, route[customer[number].rt[routeSeq]].kind);
	    }
	    break;
	case ROAD:
	    for(i = 0; i < route[customer[number].rt[routeSeq]].dist; i ++)
	    {
		position = route[customer[number].rt[routeSeq]].step[i];
		emit move(position, route[customer[number].rt[routeSeq]].kind);
		sleep(3);
		emit move(position, route[customer[number].rt[routeSeq]].kind);
	    }
	    break;
	}

    }
//    delete timer;
    customer[number].mn = 0;
    customer[number].durTime = 0;
    custOnWay[number] = 0;
//    comboxUdate();
}
/*
Linker::Linker(Block* m) {
    mapp = m;
}
void Linker::updateBlock(int pos, unsigned char k) {
    emit mv(mapp[pos].getNo(), k);
}
*/    
int loadMap(Block* blocks, Route* route, int row, int column)
{
    char temp[40];
    int i, j, k, l, m, s;
    int n = 0;
    ifstream input ("map.dat");
    if(input.is_open())
    {
	input >> temp;
	input >> n;
	cityCount = n;
	for(k = 0; k < n; k ++)
	{
	    input >> temp;
	    input >> m;
	    input >> temp;
	    input >> s;
	    input >> temp;
	    input >> i;
	    input.ignore();
	    input >> j;
	    //处理block的i和j问题
	    blocks[i * row + j].setting(m, 1);

	    input >> temp;
	    for(l = 1; l < s; l ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		//处理block
		blocks[i * row + j].setting(m, 0);
	    }
	}


	input >> temp;
	input >> m;
	routeCount = m;
	for(k = 0; k < m; k ++)
	{
	    input >> temp;
	    input >> l;
	    route[k].startCity = l;
	    input >> temp;
	    input >> l;
	    route[k].endCity = l;
	    input >> temp;
	    input >> l;
	    route[k].kind = (unsigned char)l;
	    input >> temp;
	    input >> l;
	    route[k].price = l;
	    input >> temp;
	    input >> l;
	    route[k].dist = l;
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].begin.setHMS(i, j, 0);
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].end.setHMS(i, j, 0);
	    input >> temp;
	    for(s = 0; s < route[k].dist; s ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		route[k].step[s] = i * COLUMN + j;
	    }
	}	
	input.close();
    }
    return n;
}

int difTime(QTime& t1, QTime& t2)
{
    int a1 = 0, a2 = 0;
    a1 += t1.hour() * 3600 + t1.minute() * 60;
    a2 += t2.hour() * 3600 + t2.minute() * 60;
    if(a1 > a2)
	return a1 - a2;
    else
	return a1 - a2 + 3600 * 24;
}

int testMap(Block* blocks, Route* route, int row, int column)
{
    char temp[40];
    int i, j, k, l, m, s;
    int n = 0;
    istringstream input;
    input.str("CITY_COUNT 10  NO 0 SQUARE 5 CENTRE 1-1 AREA 0-1 1-0 1-2 2-1  NO 1 SQUARE 4 CENTRE 1-4 AREA 1-3 2-3 2-4  NO 2 SQUARE 3 CENTRE 4-2 AREA 3-1 4-1  NO 3 SQUARE 4 CENTER 2-7 AREA 2-5 2-6 2-8  NO 4 SQUARE 5 CENTER 5-8 AREA 3-7 4-7 5-7 6-7  NO 5 SQUARE 4 CENTER 6-5 AREA 5-5 5-6 7-5  NO 6 SQUARE 5 CENTER 6-3 AREA 5-3 6-2 6-4 7-3  NO 7 SQUARE 11 CENTER 9-5 AREA 7-4 7-6 8-5 9-3 9-4 9-6 9-7 10-5 11-4 11-6  NO 8 SQUARE 20 CENTER 15-12 AREA 13-10 13-11 13-14 13-15 14-10 14-11 14-14 14-15 15-13 16-11 16-12 16-13 16-14 17-11 17-12 17-13 17-14 18-11 18-14  NO 9 SQUARE 24 CENTER 14-5 AREA 12-4 12-5 13-3 13-4 13-5 13-6 14-2 14-3 14-4 14-6 14-7 15-2 15-3 15-4 15-5 15-6 15-7 16-3 16-4 16-5 16-6 17-4 17-5  ROUTE_COUNT 36  START 0 END 2 KIND 2 PRICE 100 DISTANCE 4 BEGIN_TIME 07 00 END_TIME 07 40 ROUTE 2-1 3-1 4-1 4-2  START 1 END 0 KIND 3 PRICE 200 DISTANCE 5 BEGIN_TIME 12 15 END_TIME 13 30 ROUTE 2-4 2-3 1-3 1-2 1-1  START 2 END 1 KIND 1 PRICE 300 DISTANCE 3 BEGIN_TIME 20 00 END_TIME 20 15 ROUTE 3-3 2-4 1-4  START 5 END 6 KIND 3 PRICE 58 DISTANCE 2 BEGIN_TIME 9 00 END_TIME 9 30 ROUTE 6-4 6-3  START 5 END 6 KIND 2 PRICE 10 DISTANCE 2 BEGIN_TIME 14 00 END_TIME 14 20 ROUTE 6-4 6-3  START 6 END 2 KIND 3 PRICE 78 DISTANCE 2 BEGIN_TIME 10 00 END_TIME 10 30 ROUTE 5-3 4-2  START 6 END 2 KIND 1 PRICE 233 DISTANCE 2 BEGIN_TIME 10 00 END_TIME 10 10 ROUTE 5-2 4-2  START 2 END 0 KIND 3 PRICE 128 DISTANCE 4 BEGIN_TIME 11 00 END_TIME 12 00 ROUTE 4-1 3-1 2-1 1-1  START 0 END 1 KIND 3 PRICE 100 DISTANCE 3 BEGIN_TIME 14 00 END_TIME 14 45 ROUTE 1-2 1-3 1-4  START 2 END 6 KIND 2 PRICE 50 DISTANCE 2 BEGIN_TIME 19 00 END_TIME 19 20 ROUTE 5-3 6-3  START 6 END 5 KIND 2 PRICE 18 DISTANCE 2 BEGIN_TIME 22 00 END_TIME 22 20 ROUTE 6-4 6-5  START 1 END 3 KIND 2 PRICE 230 DISTANCE 4 BEGIN_TIME 15 00 END_TIME 15 40 ROUTE 2-4 2-5 2-6 2-7  START 3 END 4 KIND 3 PRICE 250 DISTANCE 4 BEGIN_TIME 8 00 END_TIME 9 00 ROUTE 3-7 4-7 5-7 5-8  START 3 END 4 KIND 2 PRICE 200 DISTANCE 5 BEGIN_TIME 9 30 END_TIME 10 20 ROUTE 3-7 4-7 5-7 6-7 5-8  START 4 END 5 KIND 2 PRICE 160 DISTANCE 4 BEGIN_TIME 11 30 END_TIME 12 10 ROUTE 5-7 5-6 5-5 6-5  START 4 END 5 KIND 3 PRICE 300 DISTANCE 4 BEGIN_TIME 11 30 END_TIME 12 30 ROUTE 5-7 5-6 5-5 6-5  START 5 END 4 KIND 3 PRICE 300 DISTANCE 4 BEGIN_TIME 13 00 END_TIME 14 00 ROUTE 5-5 5-6 5-7 5-8  START 5 END 4 KIND 1 PRICE 500 DISTANCE 3 BEGIN_TIME 14 00 END_TIME 14 15 ROUTE 6-6 6-7 5-8  START 5 END 1 KIND 1 PRICE 600 DISTANCE 5 BEGIN_TIME 9 00 END_TIME 9 25 ROUTE 5-5 4-5 3-5 2-4 1-4  START 1 END 5 KIND 1 PRICE 550 DISTANCE 5 BEGIN_TIME 10 00 END_TIME 10 25 ROUTE 2-4 3-4 4-4 5-5 6-5  START 5 END 0 KIND 1 PRICE 700 DISTANCE 5 BEGIN_TIME 10 00 END_TIME 10 25 ROUTE 5-4 4-3 3-2 2-1 1-1  START 5 END 3 KIND 1 PRICE 500 DISTANCE 4 BEGIN_TIME 15 00 END_TIME 15 20 ROUTE 5-6 4-7 3-7 2-7  START 5 END 7 KIND 1 PRICE 420 DISTANCE 3 BEGIN_TIME 17 00 END_TIME 17 15 ROUTE 7-5 8-5 9-5  START 5 END 7 KIND 2 PRICE 120 DISTANCE 3 BEGIN_TIME 12 00 END_TIME 12 30 ROUTE 7-5 8-5 9-5  START 5 END 7 KIND 3 PRICE 220 DISTANCE 3 BEGIN_TIME 14 00 END_TIME 14 45 ROUTE 7-5 8-5 9-5  START 7 END 5 KIND 2 PRICE 120 DISTANCE 3 BEGIN_TIME 15 00 END_TIME 15 30 ROUTE 8-5 7-5 6-5  START 7 END 5 KIND 3 PRICE 220 DISTANCE 3 BEGIN_TIME 16 00 END_TIME 16 45 ROUTE 8-5 7-5 6-5  START 7 END 9 KIND 2 PRICE 500 DISTANCE 5 BEGIN_TIME 12 00 END_TIME 12 50 ROUTE 10-5 11-6 12-5 13-5 14-5  START 7 END 9 KIND 3 PRICE 600 DISTANCE 6 BEGIN_TIME 18 00 END_TIME 19 30 ROUTE 10-5 11-4 12-4 13-4 14-4 14-5  START 7 END 9 KIND 1 PRICE 600 DISTANCE 5 BEGIN_TIME 19 00 END_TIME 19 25 ROUTE 10-5 11-5 12-5 13-5 14-5  START 9 END 7 KIND 1 PRICE 800 DISTANCE 5 BEGIN_TIME 10 00 END_TIME 10 25 ROUTE 13-5 12-5 11-5 10-5 9-5  START 9 END 7 KIND 1 PRICE 700 DISTANCE 5 BEGIN_TIME 13 00 END_TIME 13 25 ROUTE 13-5 12-5 11-5 10-5 9-5  START 9 END 7 KIND 1 PRICE 478 DISTANCE 5 BEGIN_TIME 22 00 END_TIME 22 25 ROUTE 13-5 12-5 11-5 10-5 9-5  START 9 END 5 KIND 1 PRICE 1024 DISTANCE 8 BEGIN_TIME 10 25 END_TIME 11 05 ROUTE 13-5 12-5 11-5 10-5 9-5 8-5 7-5 6-5  START 9 END 8 KIND 1 PRICE 999 DISTANCE 7 BEGIN_TIME 01 00 END_TIME 01 35 ROUTE 14-6 14-7 14-8 14-9 15-10 15-11 15-12  START 8 END 9 KIND 1 PRICE 999 DISTANCE 7 BEGIN_TIME 23 20 END_TIME 23 55 ROUTE 14-11 14-10 14-9 14-8 14-7 14-6 14-5");
    if(input)
    {
	input >> temp;
	input >> n;
	cityCount = n;
	for(k = 0; k < n; k ++)
	{
	    input >> temp;
	    input >> m;
	    input >> temp;
	    input >> s;
	    input >> temp;
	    input >> i;
	    input.ignore();
	    input >> j;
	    //处理block的i和j问题
	    blocks[i * row + j].setting(m, 1);

	    input >> temp;
	    for(l = 1; l < s; l ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		//处理block
		blocks[i * row + j].setting(m, 0);
	    }
	}


	input >> temp;
	input >> m;
	routeCount = m;
	for(k = 0; k < m; k ++)
	{	    
	    input >> temp;
	    input >> l;
	    route[k].startCity = l;
	    input >> temp;
	    input >> l;
	    route[k].endCity = l;
	    input >> temp;
	    input >> l;
	    route[k].kind = (unsigned char)l;
	    input >> temp;
	    input >> l;
	    route[k].price = l;
//	    qDebug() << k << " " << l << endl;
	    input >> temp;
	    input >> l;
	    route[k].dist = l;
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].begin.setHMS(i, j, 0);
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].end.setHMS(i, j, 0);
	    input >> temp;
	    for(s = 0; s < route[k].dist; s ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		route[k].step[s] = i * COLUMN + j;
	    }
	}
    }
    return n;
}
