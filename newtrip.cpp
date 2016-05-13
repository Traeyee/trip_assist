#include "newtrip.h"
#include "ui_newtrip.h"

NewTrip::NewTrip(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewTrip)
{
    ui->setupUi(this);
}

NewTrip::~NewTrip()
{
    delete ui;
}
