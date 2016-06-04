#ifndef INQUIRY_H
#define INQUIRY_H

#include <QDialog>
#include <QLabel>
#include "config.h"
#include <QTextEdit>

namespace Ui {
class Inquiry;
}

class Inquiry : public QDialog//查询界面
{
    Q_OBJECT

public:
    explicit Inquiry(QWidget *parent = 0);
    ~Inquiry();

private slots:
    void on_iqr_clicked();

private:
    QTextEdit* context;
    Ui::Inquiry *ui;
};

//void comboxUpdate();

#endif // INQUIRY_H
