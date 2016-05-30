#include "newtrip.h"
#include "ui_newtrip.h"
#include "config.h"
#include <QVBoxLayout>

NewTrip::NewTrip(int n, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
    
    int i, j;
    for(i = 0; i < 9; i ++)
    {
//	QComboBox* midP = new QComboBox[9];
	for(j = 0; j < n; j ++)
	    midP[i].addItem(QString("%1").arg(j, 2, 10, QLatin1Char('0')));
	ui->cityLayout->addWidget(midP + i);
    }
    for(i = 0; i < n; i ++)
    {
	ui->startP->addItem(QString("%1").arg(i, 2, 10, QLatin1Char('0')));
    	ui->endP->addItem(QString("%1").arg(i, 2, 10, QLatin1Char('0')));
    }
}

NewTrip::~NewTrip()
{
    delete ui;
}

void NewTrip::on_NewTrip_accepted()
{
    if(ui->timeBtn->isChecked())
    {
	NewTrip n1(1);
	n1.exec();
    }
    else if(ui->priceBtn->isChecked())
	return ;
    else if(ui->mixBtn->isChecked())
	return;
}
