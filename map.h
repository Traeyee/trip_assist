#ifndef MAP_H
#define MAP_H

#include <QLabel>

class Block : public QLabel
{
    Q_OBJECT
    
  public:
  signals:
  protected:
  private:
    int No;
    bool isCity;
    int x, y;
    
};




#endif
