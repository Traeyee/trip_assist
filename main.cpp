#include <QApplication>
#include <QDebug>
#include "map.h"
#include "config.h"
#include <cstdio>
#include "start.h"

extern int seq;
extern int customer[15][50];


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Initializaion
    seq = 8;

    
    int n;
    Block blocks[ROW * COLUMN];
    Route route[50];
    n = loadMap(blocks, route, ROW, COLUMN);
    start w(blocks, ROW, COLUMN, n);
    w.show();
    
    return a.exec();
}
