#include "stickynotes.h"
#include "ui_stickynotes.h"

// Dołączamy niezbędne nagłówki
#include <QCoreApplication>
#include <QDir>
#include <QListWidgetItem>
#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopServices>


StickyNotes::StickyNotes(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StickyNotes)
{
    ui->setupUi(this);
    ui->panelZarzadzania->setVisible(false);
    QIcon icon(":/ikona/zasoby/ikonka.png");
    setWindowIcon(icon);

    this->setWindowTitle("StickyNotes - Menedżer");

    // 1. Zdefiniuj ścieżkę do folderu z notatkami
    m_sciezkaKatalogu = QCoreApplication::applicationDirPath() + "/notatki";
    QDir dir(m_sciezkaKatalogu);

    // 2. Sprawdź, czy folder "notatki" istnieje. Jeśli nie, utwórz go.
    if (!dir.exists()) {
        dir.mkpath("."); // mkpath tworzy folder w bieżącej lokalizacji obiektu QDir
    }

    // 3. Wczytaj listę notatek przy pierwszym uruchomieniu
    odswiezListeNotatek();

    m_trybZarzadzania = false;
}

StickyNotes::~StickyNotes()
{
    delete ui;
}


void StickyNotes::odswiezListeNotatek()
{
    // 1. Wyczyść listę z poprzednich wpisów
    ui->listaNotatek->clear();

    // 2. Utwórz obiekt QDir dla naszego folderu z notatkami
    QDir katalog(m_sciezkaKatalogu);

    // 3. Ustaw filtry, aby wyszukiwać tylko pliki z rozszerzeniem .txt
    QStringList filtry;
    filtry << "*.txt";
    katalog.setNameFilters(filtry);
    katalog.setSorting(QDir::Name | QDir::Reversed); // Sortuj alfabetycznie, odwrócone

    // 4. Pobierz listę plików pasujących do filtra
    QFileInfoList listaPlikow = katalog.entryInfoList();

    // 5. Dodaj każdy znaleziony plik jako nowy element do widżetu QListWidget
    for (const QFileInfo &plikInfo : listaPlikow) {
        ui->listaNotatek->addItem(plikInfo.fileName());
    }
}


void StickyNotes::on_przyciskNowa_clicked()
{
    bool ok;
    // 1. Otwórz okno dialogowe proszące użytkownika o podanie nazwy pliku
    QString nazwaPliku = QInputDialog::getText(this, "Tworzenie nowej notatki",
                                               "Nazwa notatki:",
                                               QLineEdit::Normal, "", &ok);

    // 2. Sprawdź, czy użytkownik podał nazwę i kliknął "OK"
    if (ok && !nazwaPliku.isEmpty()) {
        // 3. Zbuduj pełną ścieżkę do nowego pliku .txt
        QString pelnaSciezka = m_sciezkaKatalogu + "/" + nazwaPliku + ".txt";

        // 4. Utwórz nową instancję okna edycji notatki
        Notatka *oknoNotatki = new Notatka();

        // 5. Połącz sygnał z okna Notatka z naszym slotem odświeżającym. To kluczowy krok!
        // Gdy oknoNotatki wyemituje sygnał notatkaZmieniona, automatycznie wykona się slot odswiezListeNotatek.
        connect(oknoNotatki, &Notatka::notatkaZmieniona, this, &StickyNotes::odswiezListeNotatek);

        // 6. Ustaw atrybut, aby okno samo zwolniło pamięć po zamknięciu
        oknoNotatki->setAttribute(Qt::WA_DeleteOnClose);

        // 7. Skonfiguruj okno dla nowej notatki, przekazując mu ścieżkę
        oknoNotatki->ustawNowaNotatke(pelnaSciezka);

        // 8. Pokaż okno edycji
        oknoNotatki->show();
    }
}


void StickyNotes::on_listaNotatek_itemDoubleClicked(QListWidgetItem *item)
{
    // 1. Pobierz nazwę pliku z klikniętego elementu
    QString nazwaPliku = item->text();

    // 2. Zbuduj pełną ścieżkę do pliku
    QString pelnaSciezka = m_sciezkaKatalogu + "/" + nazwaPliku;

    // 3. Utwórz nową instancję okna edycji
    Notatka *oknoNotatki = new Notatka();

    // 4. Połącz sygnał ze slotem, tak jak przy tworzeniu nowej notatki
    connect(oknoNotatki, &Notatka::notatkaZmieniona, this, &StickyNotes::odswiezListeNotatek);

    // 5. Ustaw atrybut zwalniania pamięci
    oknoNotatki->setAttribute(Qt::WA_DeleteOnClose);

    // 6. Skonfiguruj okno, tym razem wczytując dane z istniejącego pliku
    oknoNotatki->wczytajNotatke(pelnaSciezka);

    // 7. Pokaż okno
    oknoNotatki->show();
}


void StickyNotes::on_przyciskKosz_clicked()
{
    // 1. Sprawdź, czy jakikolwiek element na liście jest zaznaczony
    QListWidgetItem *wybranyElement = ui->listaNotatek->currentItem();
    if (!wybranyElement) {
        QMessageBox::warning(this, "Błąd", "Najpierw zaznacz notatkę, którą chcesz usunąć.");
        return;
    }

    // 2. Potwierdź operację z użytkownikiem
    auto odpowiedz = QMessageBox::question(this, "Potwierdzenie usunięcia",
                                           "Czy na pewno chcesz trwale usunąć notatkę '" + wybranyElement->text() + "'?",
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (odpowiedz == QMessageBox::Yes) {
        // 3. Usuń plik z dysku
        QString nazwaPliku = wybranyElement->text();
        QFile plik(m_sciezkaKatalogu + "/" + nazwaPliku);
        if (plik.remove()) {
            // 4. Odśwież listę, aby usunięty plik zniknął z widoku
            odswiezListeNotatek();
            ui->statusbar->showMessage("Notatka została usunięta.", 3000); // Wyświetl komunikat na 3 sekundy
        } else {
            QMessageBox::critical(this, "Błąd", "Nie udało się usunąć pliku z dysku.");
        }
    }
}

void StickyNotes::on_przyciskZarzadzaj_clicked()
{
    if (!m_trybZarzadzania) {
        wejdzWTrybZarzadzania();
    } else {
        wyjdzZTrybuZarzadzania();
    }
}

void StickyNotes::wejdzWTrybZarzadzania()
{
    m_trybZarzadzania = true;

    // Zmiana trybu zaznaczania listy
    ui->listaNotatek->setSelectionMode(QAbstractItemView::ExtendedSelection);

    // Pokaż panel z przyciskami
    ui->panelZarzadzania->setVisible(true);

    // Zmień tekst głównego przycisku i wyłącz go
    ui->przyciskZarzadzaj->setText("Tryb zarządzania");
    ui->przyciskZarzadzaj->setEnabled(false);

    ui->statusbar->showMessage("Tryb zarządzania aktywny. Możesz zaznaczyć wiele notatek. Przytrzymaj ctrl", 5000);
}

void StickyNotes::wyjdzZTrybuZarzadzania()
{
    m_trybZarzadzania = false;

    // Przywróć tryb pojedynczego zaznaczania
    ui->listaNotatek->setSelectionMode(QAbstractItemView::SingleSelection);

    // Wyczyść zaznaczenie
    ui->listaNotatek->clearSelection();

    // Ukryj panel zarządzania
    ui->panelZarzadzania->setVisible(false);

    // Przywracanie przycisku do stanu początkowego
    ui->przyciskZarzadzaj->setText("Zarządzaj");
    ui->przyciskZarzadzaj->setEnabled(true);

    ui->statusbar->clearMessage();
}


void StickyNotes::on_przyciskZakonczZarzadzanie_clicked()
{
    // wyjście z trybu zarządzania
    wyjdzZTrybuZarzadzania();
}

void StickyNotes::on_przyciskUsunZaznaczone_clicked()
{
    // 1. Pobierz listę wszystkich zaznaczonych elementów
    QList<QListWidgetItem*> zaznaczoneElementy = ui->listaNotatek->selectedItems();

    // 2. Sprawdź, czy cokolwiek zostało zaznaczone
    if (zaznaczoneElementy.isEmpty()) {
        QMessageBox::information(this, "Informacja", "Nie zaznaczono żadnych notatek do usunięcia.");
        return;
    }

    // 3. Potwierdź operację z użytkownikiem
    auto odpowiedz = QMessageBox::question(this, "Potwierdzenie usunięcia",
                                           QString("Czy na pewno chcesz trwale usunąć %1 zaznaczonych notatek?").arg(zaznaczoneElementy.size()),
                                           QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

    if (odpowiedz == QMessageBox::Yes) {
        int usunietoPomyslnie = 0;
        // 4. Przejdź pętlą przez wszystkie zaznaczone elementy i usuń odpowiadające im pliki
        for (QListWidgetItem* element : zaznaczoneElementy) {
            QString nazwaPliku = element->text();
            QFile plik(m_sciezkaKatalogu + "/" + nazwaPliku);
            if (plik.remove()) {
                usunietoPomyslnie++;
            }
        }

        ui->statusbar->showMessage(QString("Usunięto %1 notatek.").arg(usunietoPomyslnie), 4000);

        // 5. Na koniec odśwież widok listy
        odswiezListeNotatek();
    }
}


void StickyNotes::on_actionNowa_triggered()
{

    on_przyciskNowa_clicked();
}

void StickyNotes::on_actionKosz_triggered()
{

    on_przyciskKosz_clicked();
}

void StickyNotes::on_actionZamknij_program_triggered()
{

    QApplication::quit();
}

void StickyNotes::on_actionPomoc_triggered()
{
    QString link = "https://github.com/PiotrGniot/StickyNotescpp/blob/3022bfcd8a4e146b61445a6c0a12dbd82d1f6516/instrukcja.md";
    QDesktopServices::openUrl(QUrl(link));
}

