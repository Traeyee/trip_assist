#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QGridLayout>
#include <QWidget>

class Block:public QLabel
{
    Q_OBJECT
  public:
    explicit Block();
//    void initial();
    void setting(int No, int isCity);
//    explicit Block(bool mine_flag,QWidget* parent=0);
//    void setNumber(int number);
//    bool isMine()const;
  signals:
//    void explode();
//    void safe();
  protected:
//    void mousePressEvent(QMouseEvent* event);
  private:
    int No;
    bool isCity;
};

void loadMap(Block* blocks, int row, int column);

#endif
