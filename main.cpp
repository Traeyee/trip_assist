#include <QApplication>
#include <QDebug>
#include "map.h"
#include "config.h"
#include "start.h"

using namespace std;

extern int seq;
extern Customer customer[15];
extern QDateTime dateTime;
extern Route route[50];
extern int custOnWay[15];
//extern Linker* linker;
extern Block* theMap;
extern ofstream output;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Initializaion
    output.open("log.txt");
    Block blocks[ROW * COLUMN];
    seq = 0;    
    int i, j;
    for(i = 0; i < 15; i ++)
    {
	custOnWay[i] = 0;
	for(j = 0; j < MAXN; j ++)
	    customer[i].rt[j] = -1;
	customer[i].mn = 0;
	customer[i].durTime = 0;
	customer[i].tripNo = -1;
    }
    dateTime = QDateTime::currentDateTime();
//    linker = new Linker(blocks);
    /*
    for(i = 0; i < ROW * COLUMN; i ++)
	QObject::connect(linker, SIGNAL(mv(int, unsigned char)), blocks + i, SLOT(update(int, unsigned char)));
    */
    
    int n;
//    n = loadMap(blocks, route, ROW, COLUMN);
    n = testMap(blocks, route, ROW, COLUMN);
//    n = test(blocks, route, ROW, COLUMN);
//    qDebug() << routeCount << "ROUTE\n";
    
    start w(blocks, ROW, COLUMN, n);
    theMap = blocks;
    w.show();

//    delete linker;

    qDebug() << "END";
    return a.exec();
}

