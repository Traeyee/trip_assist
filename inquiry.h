#ifndef INQUIRY_H
#define INQUIRY_H

#include <QDialog>

namespace Ui {
class Inquiry;
}

class Inquiry : public QDialog
{
    Q_OBJECT

public:
    explicit Inquiry(QWidget *parent = 0);
    ~Inquiry();

private:
    Ui::Inquiry *ui;
};

#endif // INQUIRY_H
