#ifndef NEWTRIP_H
#define NEWTRIP_H

#include <QDialog>
#include <QComboBox>

namespace Ui {
class NewTrip;
}

class NewTrip : public QDialog//开始旅程的界面
{
    Q_OBJECT

public:
    explicit NewTrip(int n, QWidget *parent = 0);
    ~NewTrip();

private slots:
    void on_NewTrip_accepted();

private:
    QComboBox midP[11];//途径城市
    Ui::NewTrip *ui;
};

#endif // NEWTRIP_H
