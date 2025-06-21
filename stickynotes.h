#ifndef STICKYNOTES_H
#define STICKYNOTES_H

#include <QMainWindow>
#include "notatka.h"

class QListWidgetItem;


QT_BEGIN_NAMESPACE
namespace Ui { class StickyNotes; }
QT_END_NAMESPACE

class StickyNotes : public QMainWindow
{
    Q_OBJECT

public:
    explicit StickyNotes(QWidget *parent = nullptr);
    ~StickyNotes();

public slots:
    // wczytuje z folderu pliki .txt i printuje je na QListWidget
    void odswiezListeNotatek();

private slots:

    void on_przyciskNowa_clicked(); //Tworzenie nowej notatki
    void on_przyciskZarzadzaj_clicked(); // zarzadzanie notatkami
    void on_przyciskKosz_clicked(); //usuwanie zaznaczonej jednej notatki


    void on_przyciskUsunZaznaczone_clicked(); //usuwanie kilku zaznaczonych notatek z ctrl
    void on_przyciskZakonczZarzadzanie_clicked(); // wychodzenie z trybu zarzadzania


    void on_listaNotatek_itemDoubleClicked(QListWidgetItem *item); //obsluga otwierania notatki z listy notatek


    void on_actionNowa_triggered(); //tworzenie notatki z menu
    void on_actionKosz_triggered(); //usuwanie zaznaczonej jednej notatki z menu
    void on_actionZamknij_program_triggered();// zarzadzanie notatkami z menu





    void on_actionPomoc_triggered();

private:
    Ui::StickyNotes *ui;
    QString m_sciezkaKatalogu;

    // tryb zarzadzania (true/false)
    bool m_trybZarzadzania;

    // przelaczanie tryby zarzadzania
    void wejdzWTrybZarzadzania();
    void wyjdzZTrybuZarzadzania();
};
#endif // STICKYNOTES_H
