#ifndef INQUIRY_H
#define INQUIRY_H

#include <QDialog>
#include <QLabel>
#include "config.h"

namespace Ui {
class Inquiry;
}

class Inquiry : public QDialog
{
    Q_OBJECT

public:
    explicit Inquiry(QWidget *parent = 0);
    ~Inquiry();

private slots:
    void on_iqr_clicked();

private:
    int lbNum;
    QLabel* lb[MAXN];
    Ui::Inquiry *ui;    
};

//void comboxUpdate();

#endif // INQUIRY_H
