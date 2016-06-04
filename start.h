#ifndef START_H
#define START_H

#include <QWidget>
#include <QTime>
#include "map.h"

namespace Ui {
class start;
}

class start : public QWidget//开始界面
{
    Q_OBJECT
//protected:
//    void paintEvent(QPaintEvent*);

public:
    explicit start(Block* blocks, int r, int c, int n, QWidget *parent = 0);
    ~start();
    QTime sysTime;//系统时间
    public slots:
	void timeUpdate();//更新时间

private slots:
    void on_startTrip_clicked();
    void on_inquiry_clicked();

private:
    int row;//行
    int column;//列
    int cityNum;//城市数量
    Ui::start *ui;
};

#endif // START_H
