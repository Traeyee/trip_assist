#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include <QThread>
#include "config.h"


class Block : public QLabel
{
    Q_OBJECT
  public:
    explicit Block(QWidget *parent = 0);
    void setting(int No, int isCity);
  private:
    int No;
    bool isCity;
};
class Route
{
  public:
    int startCity, endCity;
    unsigned char kind;
    int price;
    int dist;
    QTime begin, end;
    int step[ROW + COLUMN];
};

class OneTrip : public QThread
{
    Q_OBJECT
  public:
    OneTrip(int seqq);
    protected:
    void run();
    public slots:
  private:
    int number;
    int routeSeq;
    int position;
};

int loadMap(Block* blocks1, Route* route1, int row, int column);
int test(Block* blocks1, Route* route1, int row, int column);


extern int cityCount;
extern int routeCount;
extern int seq;
extern int customer[15][MAXN];
extern QDateTime dateTime;
extern Route route[50];
extern int custOnWay[15];

#endif
