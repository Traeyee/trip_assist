/********************************************************************************
** Form generated from reading UI file 'newtrip.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWTRIP_H
#define UI_NEWTRIP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_NewTrip
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewTrip)
    {
        if (NewTrip->objectName().isEmpty())
            NewTrip->setObjectName(QStringLiteral("NewTrip"));
        NewTrip->resize(400, 300);
        buttonBox = new QDialogButtonBox(NewTrip);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(290, 20, 81, 241));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(NewTrip);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewTrip, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewTrip, SLOT(reject()));

        QMetaObject::connectSlotsByName(NewTrip);
    } // setupUi

    void retranslateUi(QDialog *NewTrip)
    {
        NewTrip->setWindowTitle(QApplication::translate("NewTrip", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class NewTrip: public Ui_NewTrip {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWTRIP_H
