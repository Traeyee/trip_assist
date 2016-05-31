#include <QWidget>
#include <fstream>
#include <QGridLayout>
#include "map.h"
#include <iostream>
using namespace std;

int seq;
int customer[15][50];
QDateTime dateTime;

Block::Block(QWidget *parent) :
    QLabel(parent)
{
    No = -1;
    isCity = false;    
    setPixmap(QPixmap(":/images/0"));  
}

void Block::setting(int N, int isCit)
{
    No = N;
    if(isCit)
	isCity = true;
    setPixmap(QPixmap(":/images/" +QString("%1").arg(No, 2, 10, QLatin1Char('0'))));
}

int loadMap(Block* blocks, Route* route, int row, int column)
{
    char temp[40];
    int i, j, k, l, m, s;
    int n = 0;
    ifstream input ("map.dat");
    if(input.is_open())
    {
	input >> temp;
	input >> n;
	for(k = 0; k < n; k ++)
	{
	    input >> temp;
	    input >> m;
	    input >> temp;
	    input >> s;
	    input >> temp;
	    input >> i;
	    input.ignore();
	    input >> j;
	    //处理block的i和j问题
	    blocks[i * row + j].setting(m, 1);

	    input >> temp;
	    for(l = 1; l < s; l ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		//处理block
		blocks[i * row + j].setting(m, 0);
	    }
	}


	input >> temp;
	input >> m;
	for(k = 0; k < m; k ++)
	{
	    input >> temp;
	    input >> l;
	    route[k].startCity = l;
	    input >> temp;
	    input >> l;
	    route[k].endCity = l;
	    input >> temp;
	    input >> l;
	    route[k].kind = (unsigned char)l;
	    input >> temp;
	    input >> l;
	    route[k].price = l;
	    input >> temp;
	    input >> l;
	    route[k].dist = l;
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].begin.setHMS(i, j, 0);
	    input >> temp;
	    input >> i;
	    input >> j;
	    route[k].end.setHMS(i, j, 0);
	    input >> temp;
	    for(s = 0; s < route[k].dist; s ++)
	    {
		input >> i;
		input.ignore();
		input >> j;
		route[k].step[0] = i * ROW + COLUMN;
	    }
	}	
	input.close();
    }
    return n;
}
