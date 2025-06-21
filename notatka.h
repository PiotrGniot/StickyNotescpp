#ifndef NOTATKA_H
#define NOTATKA_H

#include <QWidget>
#include <QFont>

namespace Ui {
class notatka;
}

class Notatka : public QWidget
{
    Q_OBJECT

public:
    explicit Notatka(QWidget *parent = nullptr);
    ~Notatka();

    // Metody publiczne do konfigurowania okna z zewnątrz
    void wczytajNotatke(const QString &sciezkaPliku);
    void ustawNowaNotatke(const QString &sciezkaPliku);

signals:
    // Sygnał wysyłany do głównego okna, gdy coś się zmieniło (zapis, usunięcie)
    void notatkaZmieniona();

private slots:
    // Przyciski do obslugi zapisu itd
    void on_przyciskZapisz_clicked();
    void on_przyciskZamknij_clicked();
    void on_PrzyciskUsun_clicked();
    void on_przyciskDuplikuj_clicked();


    // Przyciski do formatowania tekstu
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_spinWielkoscCzcionki_valueChanged(int arg1);

    // przypinanie notatki
    void on_checkPrzypnij_toggled(bool checked);

private:
    Ui::notatka *ui;
    QString m_sciezkaPliku; // sciezka do pliku notatki

    void zapiszDoPliku(); // zapisywanie notatki do pliku .txt
};

#endif // NOTATKA_H
