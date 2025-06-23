/********************************************************************************
** Form generated from reading UI file 'stickynotes.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STICKYNOTES_H
#define UI_STICKYNOTES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StickyNotes
{
public:
    QAction *actionNowa;
    QAction *actionKosz;
    QAction *actionZamknij_program;
    QAction *actionZarz_dzaj;
    QAction *actionPomoc;
    QWidget *centralwidget;
    QPushButton *przyciskNowa;
    QPushButton *przyciskKosz;
    QPushButton *przyciskZarzadzaj;
    QListWidget *listaNotatek;
    QWidget *panelZarzadzania;
    QHBoxLayout *horizontalLayout;
    QPushButton *przyciskUsunZaznaczone;
    QPushButton *przyciskZakonczZarzadzanie;
    QMenuBar *menubar;
    QMenu *menuPlik;
    QMenu *menuPomoc;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StickyNotes)
    {
        if (StickyNotes->objectName().isEmpty())
            StickyNotes->setObjectName("StickyNotes");
        StickyNotes->resize(450, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StickyNotes->sizePolicy().hasHeightForWidth());
        StickyNotes->setSizePolicy(sizePolicy);
        StickyNotes->setMinimumSize(QSize(450, 600));
        StickyNotes->setMaximumSize(QSize(450, 600));
        actionNowa = new QAction(StickyNotes);
        actionNowa->setObjectName("actionNowa");
        actionKosz = new QAction(StickyNotes);
        actionKosz->setObjectName("actionKosz");
        actionZamknij_program = new QAction(StickyNotes);
        actionZamknij_program->setObjectName("actionZamknij_program");
        actionZarz_dzaj = new QAction(StickyNotes);
        actionZarz_dzaj->setObjectName("actionZarz_dzaj");
        actionPomoc = new QAction(StickyNotes);
        actionPomoc->setObjectName("actionPomoc");
        actionPomoc->setMenuRole(QAction::MenuRole::TextHeuristicRole);
        centralwidget = new QWidget(StickyNotes);
        centralwidget->setObjectName("centralwidget");
        przyciskNowa = new QPushButton(centralwidget);
        przyciskNowa->setObjectName("przyciskNowa");
        przyciskNowa->setGeometry(QRect(70, 10, 101, 51));
        przyciskKosz = new QPushButton(centralwidget);
        przyciskKosz->setObjectName("przyciskKosz");
        przyciskKosz->setGeometry(QRect(180, 10, 101, 51));
        przyciskZarzadzaj = new QPushButton(centralwidget);
        przyciskZarzadzaj->setObjectName("przyciskZarzadzaj");
        przyciskZarzadzaj->setGeometry(QRect(290, 10, 101, 51));
        listaNotatek = new QListWidget(centralwidget);
        listaNotatek->setObjectName("listaNotatek");
        listaNotatek->setGeometry(QRect(10, 120, 421, 431));
        QFont font;
        font.setPointSize(14);
        listaNotatek->setFont(font);
        listaNotatek->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CursorShape::PointingHandCursor)));
        panelZarzadzania = new QWidget(centralwidget);
        panelZarzadzania->setObjectName("panelZarzadzania");
        panelZarzadzania->setGeometry(QRect(70, 70, 321, 42));
        horizontalLayout = new QHBoxLayout(panelZarzadzania);
        horizontalLayout->setObjectName("horizontalLayout");
        przyciskUsunZaznaczone = new QPushButton(panelZarzadzania);
        przyciskUsunZaznaczone->setObjectName("przyciskUsunZaznaczone");

        horizontalLayout->addWidget(przyciskUsunZaznaczone);

        przyciskZakonczZarzadzanie = new QPushButton(panelZarzadzania);
        przyciskZakonczZarzadzanie->setObjectName("przyciskZakonczZarzadzanie");

        horizontalLayout->addWidget(przyciskZakonczZarzadzanie);

        StickyNotes->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StickyNotes);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 450, 22));
        menuPlik = new QMenu(menubar);
        menuPlik->setObjectName("menuPlik");
        menuPomoc = new QMenu(menubar);
        menuPomoc->setObjectName("menuPomoc");
        StickyNotes->setMenuBar(menubar);
        statusbar = new QStatusBar(StickyNotes);
        statusbar->setObjectName("statusbar");
        StickyNotes->setStatusBar(statusbar);

        menubar->addAction(menuPlik->menuAction());
        menubar->addAction(menuPomoc->menuAction());
        menuPlik->addAction(actionNowa);
        menuPlik->addAction(actionKosz);
        menuPlik->addSeparator();
        menuPlik->addAction(actionZamknij_program);
        menuPomoc->addAction(actionPomoc);

        retranslateUi(StickyNotes);

        QMetaObject::connectSlotsByName(StickyNotes);
    } // setupUi

    void retranslateUi(QMainWindow *StickyNotes)
    {
        StickyNotes->setWindowTitle(QCoreApplication::translate("StickyNotes", "StickyNotes", nullptr));
        actionNowa->setText(QCoreApplication::translate("StickyNotes", "Nowa", nullptr));
        actionKosz->setText(QCoreApplication::translate("StickyNotes", "Kosz", nullptr));
        actionZamknij_program->setText(QCoreApplication::translate("StickyNotes", "Zamknij program", nullptr));
        actionZarz_dzaj->setText(QCoreApplication::translate("StickyNotes", "Zarz\304\205dzaj", nullptr));
        actionPomoc->setText(QCoreApplication::translate("StickyNotes", "Pomoc", nullptr));
#if QT_CONFIG(tooltip)
        actionPomoc->setToolTip(QCoreApplication::translate("StickyNotes", "Pomoc", nullptr));
#endif // QT_CONFIG(tooltip)
        przyciskNowa->setText(QCoreApplication::translate("StickyNotes", "Nowa notatka", nullptr));
        przyciskKosz->setText(QCoreApplication::translate("StickyNotes", "Kosz", nullptr));
        przyciskZarzadzaj->setText(QCoreApplication::translate("StickyNotes", "Zarz\304\205dzaj", nullptr));
        przyciskUsunZaznaczone->setText(QCoreApplication::translate("StickyNotes", "Usu\305\204 zaznaczone", nullptr));
        przyciskZakonczZarzadzanie->setText(QCoreApplication::translate("StickyNotes", "Zako\305\204cz zarz\304\205dzanie", nullptr));
        menuPlik->setTitle(QCoreApplication::translate("StickyNotes", "Plik", nullptr));
        menuPomoc->setTitle(QCoreApplication::translate("StickyNotes", "Pomoc", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StickyNotes: public Ui_StickyNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STICKYNOTES_H
