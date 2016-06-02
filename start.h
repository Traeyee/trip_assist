#ifndef START_H
#define START_H

#include <QWidget>
#include <QTime>
#include "map.h"

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT
//protected:
//    void paintEvent(QPaintEvent*);

public:
    explicit start(Block* blocks, int r, int c, int n, QWidget *parent = 0);
    ~start();
    QTime sysTime;
    public slots:
    void timeUpdate();

private slots:
//    void slotSafe();
//    void slotExplode();
    void on_startTrip_clicked();

    void on_inquiry_clicked();

private:
    int row;
    int column;
    int cityNum;
    Ui::start *ui;
};

#endif // START_H
