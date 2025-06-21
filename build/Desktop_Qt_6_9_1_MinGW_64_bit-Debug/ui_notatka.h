/********************************************************************************
** Form generated from reading UI file 'notatka.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTATKA_H
#define UI_NOTATKA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_notatka
{
public:
    QPushButton *przyciskZapisz;
    QPushButton *przyciskDuplikuj;
    QPushButton *przyciskZamknij;
    QPushButton *PrzyciskUsun;
    QTextEdit *textEdit;
    QFontComboBox *fontComboBox;
    QSpinBox *spinWielkoscCzcionki;
    QComboBox *comboPriorytet;
    QCheckBox *checkPrzypnij;

    void setupUi(QWidget *notatka)
    {
        if (notatka->objectName().isEmpty())
            notatka->setObjectName("notatka");
        notatka->resize(500, 600);
        notatka->setMinimumSize(QSize(500, 600));
        notatka->setMaximumSize(QSize(500, 600));
        przyciskZapisz = new QPushButton(notatka);
        przyciskZapisz->setObjectName("przyciskZapisz");
        przyciskZapisz->setGeometry(QRect(70, 30, 75, 51));
        przyciskDuplikuj = new QPushButton(notatka);
        przyciskDuplikuj->setObjectName("przyciskDuplikuj");
        przyciskDuplikuj->setGeometry(QRect(160, 30, 75, 51));
        przyciskZamknij = new QPushButton(notatka);
        przyciskZamknij->setObjectName("przyciskZamknij");
        przyciskZamknij->setGeometry(QRect(340, 30, 75, 51));
        PrzyciskUsun = new QPushButton(notatka);
        PrzyciskUsun->setObjectName("PrzyciskUsun");
        PrzyciskUsun->setGeometry(QRect(250, 30, 75, 51));
        textEdit = new QTextEdit(notatka);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(10, 190, 471, 391));
        fontComboBox = new QFontComboBox(notatka);
        fontComboBox->setObjectName("fontComboBox");
        fontComboBox->setGeometry(QRect(20, 100, 162, 22));
        spinWielkoscCzcionki = new QSpinBox(notatka);
        spinWielkoscCzcionki->setObjectName("spinWielkoscCzcionki");
        spinWielkoscCzcionki->setGeometry(QRect(200, 100, 71, 22));
        spinWielkoscCzcionki->setButtonSymbols(QAbstractSpinBox::ButtonSymbols::PlusMinus);
        spinWielkoscCzcionki->setMinimum(2);
        spinWielkoscCzcionki->setMaximum(128);
        spinWielkoscCzcionki->setValue(11);
        comboPriorytet = new QComboBox(notatka);
        comboPriorytet->addItem(QString());
        comboPriorytet->addItem(QString());
        comboPriorytet->addItem(QString());
        comboPriorytet->addItem(QString());
        comboPriorytet->addItem(QString());
        comboPriorytet->setObjectName("comboPriorytet");
        comboPriorytet->setGeometry(QRect(290, 100, 161, 22));
        checkPrzypnij = new QCheckBox(notatka);
        checkPrzypnij->setObjectName("checkPrzypnij");
        checkPrzypnij->setGeometry(QRect(380, 0, 111, 31));

        retranslateUi(notatka);

        QMetaObject::connectSlotsByName(notatka);
    } // setupUi

    void retranslateUi(QWidget *notatka)
    {
        notatka->setWindowTitle(QCoreApplication::translate("notatka", "Form", nullptr));
        przyciskZapisz->setText(QCoreApplication::translate("notatka", "Zapisz", nullptr));
        przyciskDuplikuj->setText(QCoreApplication::translate("notatka", "Duplikuj", nullptr));
        przyciskZamknij->setText(QCoreApplication::translate("notatka", "Zamknij", nullptr));
        PrzyciskUsun->setText(QCoreApplication::translate("notatka", "Usu\305\204", nullptr));
        spinWielkoscCzcionki->setSuffix(QCoreApplication::translate("notatka", " px", nullptr));
        spinWielkoscCzcionki->setPrefix(QString());
        comboPriorytet->setItemText(0, QCoreApplication::translate("notatka", "5 - Bardzo wysoki (Pilne)", nullptr));
        comboPriorytet->setItemText(1, QCoreApplication::translate("notatka", "4 - Wysoki", nullptr));
        comboPriorytet->setItemText(2, QCoreApplication::translate("notatka", "3 - \305\232redni", nullptr));
        comboPriorytet->setItemText(3, QCoreApplication::translate("notatka", "2 - Niski", nullptr));
        comboPriorytet->setItemText(4, QCoreApplication::translate("notatka", "1 - Bardzo niski", nullptr));

#if QT_CONFIG(tooltip)
        checkPrzypnij->setToolTip(QCoreApplication::translate("notatka", "<html><head/><body><p>Notatka po zaznaczeniu tej opcji zostanie przypi\304\231ta i b\304\231dzie zawsze na wierzchu</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkPrzypnij->setText(QCoreApplication::translate("notatka", "Przypnij notatk\304\231", nullptr));
    } // retranslateUi

};

namespace Ui {
    class notatka: public Ui_notatka {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTATKA_H
