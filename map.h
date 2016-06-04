#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QThread>
#include "config.h"


class Block : public QLabel//地图单元（一个方块）
{
    Q_OBJECT
  public:
    explicit Block(QWidget *parent = 0);
    void setting(int No, int isCity);//设置属性
  private:
    int No;//城市编号
    bool isCity;//是否属于城市
};
class Route//班次
{
  public:
    int startCity, endCity;//起点城市与终点城市
    unsigned char kind;//交通工具种类
    int price;//价格
    int dist;//距离
    QTime begin, end;//开始、结束时间
    int step[ROW + COLUMN];//路径踪迹
};

class OneTrip : public QThread//乘客线程
{
    Q_OBJECT
  public:
    OneTrip(int seqq);
    protected:
    void run();
    public slots:
  private:
    int number;//乘客序号
    int routeSeq;//路径序号
    int position;//现在位置
};

int loadMap(Block* blocks1, Route* route1, int row, int column);//读取地图
int testMap(Block* blocks1, Route* route1, int row, int column);//测试地图
int test(Block* blocks1, Route* route1, int row, int column);//测试函数


extern int cityCount;//城市数量
extern int routeCount;//班次数量
extern int seq;//乘客序号
extern int customer[15][MAXN];//乘客路径
extern QDateTime dateTime;//当前时间
extern Route route[50];//班次
extern int custOnWay[15];//判断乘客是否在路上

#endif
