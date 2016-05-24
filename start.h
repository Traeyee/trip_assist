#ifndef START_H
#define START_H

#include <QWidget>
#include "map.h"

namespace Ui {
class start;
}

class start : public QWidget
{
    Q_OBJECT

public:
    explicit start(Block* blocks, int r, int c, QWidget *parent = 0);
    ~start();

private slots:
    void on_pushButton_clicked();
//    void slotSafe();
//    void slotExplode();
private:
    QGridLayout* mainLayout;
    int row;
    int column;
    Ui::start *ui;
};

#endif // START_H
