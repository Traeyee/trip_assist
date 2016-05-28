#include <QApplication>
#include "map.h"
#include "config.h"
#include <cstdio>
#include "start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Initializaion
    int n;
    Block blocks[ROW * COLUMN];
    n = loadMap(blocks, ROW, COLUMN);
    start w(blocks, ROW, COLUMN, n);
    w.show();
    
    return a.exec();
}
