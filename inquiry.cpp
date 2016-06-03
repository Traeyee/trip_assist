#include "inquiry.h"
#include "ui_inquiry.h"
#include "config.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

extern int customer[15][MAXN];
extern int custOnWay[15];

Inquiry::Inquiry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inquiry)
{
    ui->setupUi(this);

    int i, j;
    for(i = 0; i < 11; i ++)
	ui->customBox->addItem(QString("%1").arg(i, 2, 10, QLatin1Char('0')));
    
    lbNum = 0;
    for(i = 0; i < MAXN; i ++)
	lb[i] = NULL;
}

Inquiry::~Inquiry()
{
    delete ui;
}
/*
void comboxUpdate()
{
    
}
*/

void Inquiry::on_iqr_clicked()
{
    int i, j, k;
    for(i = 0; i < lbNum; i ++)
    {
	ui->screen->removeWidget(lb[i]);
	lb[i]->hide();
	lb[i] = NULL;
    }

    if(!custOnWay[ui->customBox->currentIndex()])
    {
	QLabel* l = new QLabel("Not on the way!");
	ui->screen->addWidget(l);
	lb[0] = l;
	lbNum = 1;
    }
    else
    {
	i = 0;
	lbNum = 0;
	k = ui->customBox->currentIndex();
	while(customer[k][i] != -1)
	{
	    QLabel* l = new QLabel(QString("%1").arg(customer[k][i], 2, 10, QLatin1Char('0')));
	    ui->screen->addWidget(l);
	    lb[i] = l;
	    lbNum ++;
	    i ++;
	}	
    }
}
