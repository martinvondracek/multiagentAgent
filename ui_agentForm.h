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
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_agentForm
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *agentForm)
    {
        if (agentForm->objectName().isEmpty())
            agentForm->setObjectName(QString::fromUtf8("agentForm"));
        agentForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(agentForm);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::NoButton|QDialogButtonBox::Ok);

        retranslateUi(agentForm);
        QObject::connect(buttonBox, SIGNAL(accepted()), agentForm, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), agentForm, SLOT(reject()));

        QMetaObject::connectSlotsByName(agentForm);
    } // setupUi

    void retranslateUi(QDialog *agentForm)
    {
        agentForm->setWindowTitle(QApplication::translate("agentForm", "agentForm", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class agentForm: public Ui_agentForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGENTFORM_H
