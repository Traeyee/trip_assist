#include <QApplication>
#include "map.h"
#include "config.h"
#include <cstdio>
#include "start.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Initializaion
    int i;
    Block blocks[ROW * COLUMN];
    start w(blocks, ROW, COLUMN);
    loadMap(blocks, ROW, COLUMN);
    w.show();
    
    return a.exec();
}
