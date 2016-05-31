#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGridLayout>
#include <QWidget>
#include <QtCore>
#include "config.h"


extern int seq;
extern int customer[15][50];
extern QDateTime dateTime;

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
int loadMap(Block* blocks, Route* route, int row, int column);

#endif
