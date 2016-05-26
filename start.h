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

public:
    explicit start(Block* blocks, int r, int c, QWidget *parent = 0);
    ~start();
    QTime sysTime;

    public slots:
	void timeUpdate();

private slots:
//    void slotSafe();
//    void slotExplode();
    void on_startTrip_clicked();

private:
    QGridLayout* mainLayout;
    int row;
    int column;
    Ui::start *ui;
};

#endif // START_H
