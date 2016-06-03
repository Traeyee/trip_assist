#include <QApplication>
#include <QDebug>
#include "map.h"
#include "config.h"
#include <cstdio>
#include "start.h"

extern int seq;
extern int customer[15][MAXN];
extern QDateTime dateTime;
extern Route route[50];
extern int custOnWay[15];

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Initializaion
    Block blocks[ROW * COLUMN];
    seq = 0;    
    int i, j;
    for(i = 0; i < 15; i ++)
    {
	custOnWay[i] = 0;
	for(j = 0; j < MAXN; j ++)
	    customer[i][j] = -1;
    }
    dateTime = QDateTime::currentDateTime();
    
    int n;
    n = loadMap(blocks, route, ROW, COLUMN);
//    n = test(blocks, route, ROW, COLUMN);
    start w(blocks, ROW, COLUMN, n);
    w.show();
    
    return a.exec();
}

