#include "start.h"
#include "ui_start.h"
#include <QtCore>
#include <QWidget>
#include "newtrip.h"
#include "system.h"
#include "map.h"
#include "config.h"
#include <cstdio>

start::start(Block* blocks, int r, int c, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::start)
{
    ui->setupUi(this);
    row = r;
    column = c;
    int i, j;    
    mainLayout = new QGridLayout(this);
    for(i = 0; i < row; i ++)
	for(j = 0; j < column; j ++)
	    mainLayout->addWidget(blocks + i * row + j, i, j);
//强制设置窗体大小
    setLayout(mainLayout);
    setFixedSize(sizeHint());
}

start::~start()
{
    delete ui;
}

void start::on_pushButton_clicked()
{
    NewTrip n;
    n.exec();
}
