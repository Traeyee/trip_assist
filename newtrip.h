#ifndef NEWTRIP_H
#define NEWTRIP_H

#include <QDialog>

namespace Ui {
class NewTrip;
}

class NewTrip : public QDialog
{
    Q_OBJECT

public:
    explicit NewTrip(int n, QWidget *parent = 0);
    ~NewTrip();

private:
    Ui::NewTrip *ui;
};

#endif // NEWTRIP_H
