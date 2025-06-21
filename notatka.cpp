#include "notatka.h"
#include "qlineedit.h"
#include "ui_notatka.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QInputDialog>

Notatka::Notatka(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::notatka)
{
    ui->setupUi(this);
    ui->comboPriorytet->setCurrentIndex(2); // Domyślnie "Średni"
}

Notatka::~Notatka()
{
    delete ui;
}


void Notatka::wczytajNotatke(const QString &sciezkaPliku)
{
    m_sciezkaPliku = sciezkaPliku;
    this->setWindowTitle(QFileInfo(sciezkaPliku).baseName());
    QFile plik(m_sciezkaPliku);

    if (!plik.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Błąd", "Nie można otworzyć pliku notatki.");
        return;
    }

    QTextStream in(&plik);
    QString trescNotatki;
    bool wTrybieMetadanych = true;

    // Ustawiamy domyślne wartości, na wypadek gdyby plik nie miał nagłówka
    QFont czcionka("Arial");
    int rozmiar = 11;
    QString priorytet = "3 - Średni";
    bool czyPrzypieta = false;

    while (!in.atEnd()) {
        QString linia = in.readLine();
        if (wTrybieMetadanych && linia == "---") {
            wTrybieMetadanych = false;
            continue; // Przechodzimy do następnej linii (już z treścią)
        }

        if (wTrybieMetadanych) {
            // Przetwarzamy linie z metadanymi
            QStringList czesci = linia.split(':', Qt::KeepEmptyParts);
            if (czesci.size() == 2) {
                QString klucz = czesci[0].trimmed();
                QString wartosc = czesci[1].trimmed();

                if (klucz == "Czcionka") czcionka.setFamily(wartosc);
                else if (klucz == "Rozmiar") rozmiar = wartosc.toInt();
                else if (klucz == "Priorytet") priorytet = wartosc;
            }
        } else {
            // Jesteśmy już po separatorze, więc wszystko jest treścią
            trescNotatki.append(linia + "\n");
        }
    }
    plik.close();

    // Jeśli plik nie miał separatora, cała zawartość jest traktowana jako treść
    if (wTrybieMetadanych) {
        trescNotatki = ui->textEdit->toPlainText(); // Błąd w logice, pobieramy całość z pliku
        plik.open(QIODevice::ReadOnly | QIODevice::Text); // Otwórz ponownie
        trescNotatki = plik.readAll();
        plik.close();
    }



    ui->fontComboBox->setCurrentFont(czcionka);
    ui->spinWielkoscCzcionki->setValue(rozmiar);
    ui->comboPriorytet->setCurrentText(priorytet);
    ui->textEdit->setText(trescNotatki.trimmed());
    ui->textEdit->setCurrentFont(czcionka);
    ui->textEdit->setFontPointSize(rozmiar);

    ui->checkPrzypnij->setChecked(czyPrzypieta);
    if (czyPrzypieta) {
        this->setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    }
}


void Notatka::ustawNowaNotatke(const QString &sciezkaPliku)
{
    m_sciezkaPliku = sciezkaPliku;
    this->setWindowTitle(QFileInfo(sciezkaPliku).baseName() + " (Nowa)");
}


void Notatka::zapiszDoPliku()
{
    QFile plik(m_sciezkaPliku);
    if (!plik.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QMessageBox::critical(this, "Błąd", "Nie można zapisać pliku notatki.");
        return;
    }

    QTextStream out(&plik);

    // Zapisujemy nagłówek z metadanymi
    out << "Czcionka: " << ui->fontComboBox->currentFont().family() << "\n";
    out << "Rozmiar: " << ui->spinWielkoscCzcionki->value() << "\n";
    out << "Priorytet: " << ui->comboPriorytet->currentText() << "\n";

    out << "Przypieta: " << (ui->checkPrzypnij->isChecked() ? "tak" : "nie") << "\n";

    // Zapisujemy separator
    out << "---\n";

    // Zapisujemy właściwą treść
    out << ui->textEdit->toPlainText();

    plik.close();
    qDebug() << "Zapisano notatkę w formacie TXT:" << m_sciezkaPliku;

    emit notatkaZmieniona();
    this->setWindowTitle(QFileInfo(m_sciezkaPliku).baseName());
}


void Notatka::on_przyciskZapisz_clicked() { zapiszDoPliku(); }
void Notatka::on_przyciskZamknij_clicked() { this->close(); }
void Notatka::on_fontComboBox_currentFontChanged(const QFont &f) { ui->textEdit->setCurrentFont(f); }
void Notatka::on_spinWielkoscCzcionki_valueChanged(int size) { ui->textEdit->setFontPointSize(size); }


void Notatka::on_PrzyciskUsun_clicked()
{
    auto odpowiedz = QMessageBox::question(this, "Potwierdzenie usunięcia",
                                           "Czy na pewno chcesz trwale usunąć tę notatkę?",
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (odpowiedz == QMessageBox::Yes) {
        QFile plik(m_sciezkaPliku);
        if (plik.remove()) {
            qDebug() << "Usunięto plik:" << m_sciezkaPliku;
            emit notatkaZmieniona();
            this->close();
        } else {
            QMessageBox::critical(this, "Błąd", "Nie udało się usunąć pliku.");
        }
    }
}



void Notatka::on_przyciskDuplikuj_clicked()
{
    // 1. Zapytaj o nazwę dla duplikatu
    bool ok;
    QString nowaNazwa = QInputDialog::getText(this, "Duplikuj notatkę", "Podaj nową nazwę:",
    QLineEdit::Normal, QFileInfo(m_sciezkaPliku).baseName() + " (kopia)", &ok);

    if (ok && !nowaNazwa.isEmpty()) {
        // 2. Zapisz najpierw bieżący stan edytowanej notatki
        zapiszDoPliku();

        // 3. Skopiuj bieżący plik pod nową nazwę
        QString nowaSciezka = QFileInfo(m_sciezkaPliku).path() + "/" + nowaNazwa + ".txt";
        if (QFile::copy(m_sciezkaPliku, nowaSciezka)) {
            // 4. Poinformuj główne okno o zmianie, aby odświeżyło listę
            emit notatkaZmieniona();
            QMessageBox::information(this, "Sukces", "Notatka została zduplikowana.");
        } else {
            QMessageBox::critical(this, "Błąd", "Nie udało się utworzyć duplikatu.");
        }
    }
}


void Notatka::on_checkPrzypnij_toggled(bool checked) // funkcja do obslugi przypinania notatki
{

    Qt::WindowFlags flags = this->windowFlags();

    if (checked) {

        this->setWindowFlags(flags | Qt::WindowStaysOnTopHint);
    } else {

        this->setWindowFlags(flags & ~Qt::WindowStaysOnTopHint);
    }

    this->show();
}
