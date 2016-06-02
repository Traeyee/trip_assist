#include "newtrip.h"
#include "ui_newtrip.h"
#include "config.h"
#include <QVBoxLayout>
#include <QDebug>
#include "map.h"
#include "inquiry.h"

extern int cityCount;
extern int routeCount;
extern int seq;
extern int customer[15][MAXN];
extern Route route[50];

NewTrip::NewTrip(int n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
    
    int i, j;
    for(i = 0; i < 11; i ++)
    {
	for(j = 0; j < n; j ++)
	{
	    midP[i].addItem(QString("%1").arg(j, 2, 10, QLatin1Char('0')));
	    midP[i].setCurrentIndex(-1);
	}
	ui->cityLayout->addWidget(midP + i);
    }
}

NewTrip::~NewTrip()
{
    delete ui;
}

void findRoute(int& n, int k, int* prev, int rc[][20], int* cm)
{
    if(prev[k] == k)
	return ;
    else
    {
	findRoute(n, prev[k], prev, rc,  cm);
	cm[n ++] = rc[prev[k]][k];
    }
    return ;
}

int priceDijstra(int src, int dest, Route* route1, int* cm)
{
    int c[cityCount][cityCount], rc[20][20];
    int v[cityCount] = {0}, prev[cityCount] = {0}, d[cityCount];
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
    findRoute(n, dest, prev, rc, cm);
    
    return n;
}

void NewTrip::on_NewTrip_accepted()
{
    if(ui->timeBtn->isChecked())
    {}
    else if(ui->priceBtn->isChecked())
    {
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
		    k += priceDijstra(i, j, route, customer[seq] + k);
	    }
	}
	customer[seq][k] = -1;
	OneTrip o1(seq);
	o1.start();
    }
    else if(ui->mixBtn->isChecked())
    {}
    seq %= 11;
 
}
