#include "newtrip.h"
#include "ui_newtrip.h"
#include "config.h"
#include <QVBoxLayout>
#include <QDebug>
#include "map.h"

extern int seq;

NewTrip::NewTrip(int n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
    
    int i, j;
    for(i = 0; i < 11; i ++)
    {
//	QComboBox* midP = new QComboBox[9];
	for(j = 0; j < n; j ++)
	    midP[i].addItem(QString("%1").arg(j, 2, 10, QLatin1Char('0')));
	ui->cityLayout->addWidget(midP + i);
    }
}

NewTrip::~NewTrip()
{
    delete ui;
}

/*
void Dijstra(int src, double c[][MAXN], double* d, int n, int* prev)
{
    int i, j, k, flagg;
    double temp;
    int v[n] = {0};
    
    for(i = 0; i < n; i ++)
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
    
    for(k = 1; k < n; k++)
    {
	temp = INF;;
	for(i = 0; i < n; i ++)	
	    if(! v[i] && d[i] < temp)
	    {
		temp = d[i];
		flagg = i;
	    }

	v[flagg] = 1;
	for(i = 0; i < n; i ++)	
	    if(! v[i])	    
		if(d[flagg] + c[flagg][i] < d[i])
		{
		    d[i] = d[flagg] + c[flagg][i];
		    prev[i] = flagg;
		}	
    }
    
}
void findRoute(int k, int* prev)
{
    if(prev[k] == k)
	cout << k << " ";
    else
    {
	findRoute(prev[k], prev);
	cout << k << " ";
    }
    return ;
}
*/
void NewTrip::on_NewTrip_accepted()
{
    if(ui->timeBtn->isChecked())
	return ;
    else if(ui->priceBtn->isChecked())
    {
	seq ++;
	qDebug() << seq << endl;
    }
    else if(ui->mixBtn->isChecked())
	return;
}
