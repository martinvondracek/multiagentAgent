/********************************************************************************
** Form generated from reading UI file 'agentForm.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGENTFORM_H
#define UI_AGENTFORM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_agentForm
{
public:
    QPushButton *koniecButton;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QWidget *layoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *pripojComportButton;
    QLineEdit *comportEdit;
    QPushButton *odpojComportButton;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLineEdit *ipEdit;
    QLabel *label_3;
    QLineEdit *ipPortEdit;
    QPushButton *odpojServerButton;
    QPushButton *pripojServerButton;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QPushButton *dopreduButton;
    QPushButton *dolavaButton;
    QPushButton *zastavButton;
    QPushButton *dopravaButton;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_3;
    QLabel *label_10;
    QLabel *label_4;
    QLabel *xLabel;
    QLineEdit *x0Edit;
    QLabel *label_5;
    QLabel *yLabel;
    QLineEdit *y0Edit;
    QLabel *label_6;
    QLabel *zLabel;
    QLineEdit *z0Edit;
    QPushButton *nastavAktPolohuButton;

    void setupUi(QDialog *agentForm)
    {
        if (agentForm->objectName().isEmpty())
            agentForm->setObjectName(QString::fromUtf8("agentForm"));
        agentForm->resize(582, 385);
        koniecButton = new QPushButton(agentForm);
        koniecButton->setObjectName(QString::fromUtf8("koniecButton"));
        koniecButton->setGeometry(QRect(460, 330, 85, 26));
        label_11 = new QLabel(agentForm);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(0, 10, 581, 26));
        label_11->setAlignment(Qt::AlignCenter);
        label_12 = new QLabel(agentForm);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(70, 50, 111, 26));
        label_13 = new QLabel(agentForm);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(350, 50, 131, 26));
        label_14 = new QLabel(agentForm);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(110, 180, 111, 26));
        label_15 = new QLabel(agentForm);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(360, 200, 111, 26));
        layoutWidget = new QWidget(agentForm);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 80, 222, 60));
        formLayout = new QFormLayout(layoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        pripojComportButton = new QPushButton(layoutWidget);
        pripojComportButton->setObjectName(QString::fromUtf8("pripojComportButton"));

        formLayout->setWidget(0, QFormLayout::FieldRole, pripojComportButton);

        comportEdit = new QLineEdit(layoutWidget);
        comportEdit->setObjectName(QString::fromUtf8("comportEdit"));

        formLayout->setWidget(1, QFormLayout::LabelRole, comportEdit);

        odpojComportButton = new QPushButton(layoutWidget);
        odpojComportButton->setObjectName(QString::fromUtf8("odpojComportButton"));

        formLayout->setWidget(1, QFormLayout::FieldRole, odpojComportButton);

        layoutWidget1 = new QWidget(agentForm);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(310, 80, 221, 90));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        ipEdit = new QLineEdit(layoutWidget1);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));

        gridLayout->addWidget(ipEdit, 0, 1, 1, 2);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        ipPortEdit = new QLineEdit(layoutWidget1);
        ipPortEdit->setObjectName(QString::fromUtf8("ipPortEdit"));

        gridLayout->addWidget(ipPortEdit, 1, 1, 1, 2);

        odpojServerButton = new QPushButton(layoutWidget1);
        odpojServerButton->setObjectName(QString::fromUtf8("odpojServerButton"));

        gridLayout->addWidget(odpojServerButton, 2, 2, 1, 1);

        pripojServerButton = new QPushButton(layoutWidget1);
        pripojServerButton->setObjectName(QString::fromUtf8("pripojServerButton"));

        gridLayout->addWidget(pripojServerButton, 2, 0, 1, 2);

        layoutWidget2 = new QWidget(agentForm);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(290, 230, 269, 60));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        dopreduButton = new QPushButton(layoutWidget2);
        dopreduButton->setObjectName(QString::fromUtf8("dopreduButton"));

        gridLayout_2->addWidget(dopreduButton, 0, 1, 1, 1);

        dolavaButton = new QPushButton(layoutWidget2);
        dolavaButton->setObjectName(QString::fromUtf8("dolavaButton"));

        gridLayout_2->addWidget(dolavaButton, 1, 0, 1, 1);

        zastavButton = new QPushButton(layoutWidget2);
        zastavButton->setObjectName(QString::fromUtf8("zastavButton"));

        gridLayout_2->addWidget(zastavButton, 1, 1, 1, 1);

        dopravaButton = new QPushButton(layoutWidget2);
        dopravaButton->setObjectName(QString::fromUtf8("dopravaButton"));

        gridLayout_2->addWidget(dopravaButton, 1, 2, 1, 1);

        layoutWidget3 = new QWidget(agentForm);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(30, 210, 217, 142));
        gridLayout_3 = new QGridLayout(layoutWidget3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        label_10 = new QLabel(layoutWidget3);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_3->addWidget(label_10, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 1, 0, 1, 1);

        xLabel = new QLabel(layoutWidget3);
        xLabel->setObjectName(QString::fromUtf8("xLabel"));

        gridLayout_3->addWidget(xLabel, 1, 1, 1, 1);

        x0Edit = new QLineEdit(layoutWidget3);
        x0Edit->setObjectName(QString::fromUtf8("x0Edit"));

        gridLayout_3->addWidget(x0Edit, 1, 2, 1, 1);

        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 2, 0, 1, 1);

        yLabel = new QLabel(layoutWidget3);
        yLabel->setObjectName(QString::fromUtf8("yLabel"));

        gridLayout_3->addWidget(yLabel, 2, 1, 1, 1);

        y0Edit = new QLineEdit(layoutWidget3);
        y0Edit->setObjectName(QString::fromUtf8("y0Edit"));

        gridLayout_3->addWidget(y0Edit, 2, 2, 1, 1);

        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 3, 0, 1, 1);

        zLabel = new QLabel(layoutWidget3);
        zLabel->setObjectName(QString::fromUtf8("zLabel"));

        gridLayout_3->addWidget(zLabel, 3, 1, 1, 1);

        z0Edit = new QLineEdit(layoutWidget3);
        z0Edit->setObjectName(QString::fromUtf8("z0Edit"));

        gridLayout_3->addWidget(z0Edit, 3, 2, 1, 1);

        nastavAktPolohuButton = new QPushButton(layoutWidget3);
        nastavAktPolohuButton->setObjectName(QString::fromUtf8("nastavAktPolohuButton"));

        gridLayout_3->addWidget(nastavAktPolohuButton, 4, 0, 1, 3);


        retranslateUi(agentForm);
        QObject::connect(koniecButton, SIGNAL(clicked()), agentForm, SLOT(close()));

        QMetaObject::connectSlotsByName(agentForm);
    } // setupUi

    void retranslateUi(QDialog *agentForm)
    {
        agentForm->setWindowTitle(QApplication::translate("agentForm", "agentForm", 0, QApplication::UnicodeUTF8));
        koniecButton->setText(QApplication::translate("agentForm", "Koniec", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("agentForm", "Info", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("agentForm", "Pripojenie robota", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("agentForm", "Pripojenie k serveru", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("agentForm", "Lokaliz\303\241cia", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("agentForm", "Manu\303\241lne riadenie", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("agentForm", "Comport:", 0, QApplication::UnicodeUTF8));
        pripojComportButton->setText(QApplication::translate("agentForm", "Pripoj", 0, QApplication::UnicodeUTF8));
        comportEdit->setText(QApplication::translate("agentForm", "COM1", 0, QApplication::UnicodeUTF8));
        odpojComportButton->setText(QApplication::translate("agentForm", "Odpoj", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("agentForm", "IP:", 0, QApplication::UnicodeUTF8));
        ipEdit->setText(QApplication::translate("agentForm", "000.000.000.000", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("agentForm", "Port:", 0, QApplication::UnicodeUTF8));
        ipPortEdit->setText(QApplication::translate("agentForm", "8080", 0, QApplication::UnicodeUTF8));
        odpojServerButton->setText(QApplication::translate("agentForm", "Odpoj", 0, QApplication::UnicodeUTF8));
        pripojServerButton->setText(QApplication::translate("agentForm", "Pripoj", 0, QApplication::UnicodeUTF8));
        dopreduButton->setText(QApplication::translate("agentForm", "Dopredu", 0, QApplication::UnicodeUTF8));
        dolavaButton->setText(QApplication::translate("agentForm", "Do\304\276ava", 0, QApplication::UnicodeUTF8));
        zastavButton->setText(QApplication::translate("agentForm", "Zastav", 0, QApplication::UnicodeUTF8));
        dopravaButton->setText(QApplication::translate("agentForm", "Doprava", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("agentForm", "Poloha", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("agentForm", "X:", 0, QApplication::UnicodeUTF8));
        xLabel->setText(QApplication::translate("agentForm", "0", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("agentForm", "Y:", 0, QApplication::UnicodeUTF8));
        yLabel->setText(QApplication::translate("agentForm", "0", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("agentForm", "Uhol:", 0, QApplication::UnicodeUTF8));
        zLabel->setText(QApplication::translate("agentForm", "0", 0, QApplication::UnicodeUTF8));
        nastavAktPolohuButton->setText(QApplication::translate("agentForm", "Nastav ako aktu\303\241lnu polohu", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class agentForm: public Ui_agentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGENTFORM_H
