#include "inquiry.h"
#include "ui_inquiry.h"

Inquiry::Inquiry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inquiry)
{
    ui->setupUi(this);
}

Inquiry::~Inquiry()
{
    delete ui;
}
