# StickyNotes - Aplikacja do Notatek w C++/Qt

**StickyNotes** to zaawansowana, a zarazem intuicyjna aplikacja desktopowa do tworzenia i zarządzania notatkami, napisana w języku C++ z wykorzystaniem frameworka Qt 6. Projekt ten demonstruje kluczowe koncepcje programowania obiektowego, zarządzania interfejsem użytkownika oraz operacji na plikach.


## 1. Główne Funkcjonalności

Aplikacja oferuje szeroki wachlarz funkcji, które ułatwiają organizację pracy i zapisków:

* **Zarządzanie Notatkami:** Główne okno aplikacji wyświetla przejrzystą listę wszystkich Twoich notatek, umożliwiając szybki dostęp.
* **Dedykowane Okno Edycji:** Każda notatka (zarówno nowa, jak i istniejąca) otwiera się w osobnym, dedykowanym oknie, co pozwala na pracę z wieloma notatkami jednocześnie.
* **Formatowanie:** W oknie edycji możesz dostosować wygląd tekstu, zmieniając czcionkę i jej rozmiar.
* **Priorytetyzacja:** Każdą notatkę można oznaczyć jednym z pięciu poziomów priorytetu (od "Bardzo niski" do "Bardzo wysoki (Pilne)"), co pomaga w organizacji zadań.
* **Przypinanie Okna:** Funkcja "Przypnij (zawsze na wierzchu)" pozwala utrzymać okno wybranej notatki nad wszystkimi innymi aplikacjami, co jest idealne do robienia szybkich zapisków podczas pracy.
* **Trwałość Ustawień:** Wszystkie opcje notatki (czcionka, rozmiar, priorytet, stan przypięcia) są zapisywane razem z jej treścią i automatycznie przywracane przy ponownym otwarciu w jendym pliku .txt.
* **Tryb Zarządzania:** Specjalny tryb, który pozwala na zaznaczenie wielu notatek na liście przytrzymując przycisk ```ctrl``` i wykonanie na nich operacji masowych, takich jak jednoczesne usunięcie.
* **Automatyzacja:** Aplikacja automatycznie tworzy folder `notatki` w swojej lokalizacji, przechowując w nim wszystkie notatki.

## 2. Struktura Projektu

Projekt jest zorganizowany w sposób modułowy, co ułatwia jego zrozumienie i dalszy rozwój. Główne pliki to:
```
StickyNotes/
│
├── notatki/                  # Automatycznie tworzony folder na pliki notatek (.txt)
│
├── notatka.h                 # Plik nagłówkowy klasy Notatka (okno edycji)
├── notatka.cpp               # Plik źródłowy klasy Notatka
├── notatka.ui                # Plik interfejsu
│
├── stickynotes.h             # Plik nagłówkowy klasy StickyNotes (okno główne)
├── stickynotes.cpp           # Plik źródłowy klasy StickyNotes
├── stickynotes.ui            # Plik interfejsu
│
├── main.cpp                  # Główny plik aplikacji, punkt startowy
└── StickyNotes.pro           # Plik projektu qmake, zarządza kompilacją
```
### Opis Klas

* **`StickyNotes`** (`QMainWindow`): Jest to główna klasa aplikacji, reprezentująca okno menedżera notatek. Odpowiada za wyświetlanie listy notatek, zarządzanie trybami pracy (normalny/zarządzanie) oraz otwieranie okien edycji dla poszczególnych notatek.
* **`Notatka`** (`QWidget`): Klasa reprezentująca pojedyncze okno edycji notatki. Jest w pełni samodzielna – odpowiada za wczytywanie, edycję, formatowanie i zapisywanie treści oraz opcju pojedynczej notatki. Komunikuje się z oknem głównym za pomocą mechanizmu sygnałów i slotów.

## 3. Szczegółowy Opis Kluczowych Funkcji

### Klasa `StickyNotes`

* **`StickyNotes(QWidget *parent)` (Konstruktor)**
    * **Opis:** Inicjalizuje główne okno aplikacji.
    * **Działanie:** Ustawia interfejs użytkownika z pliku `.ui`, programistycznie ukrywa `panelZarzadzania`, sprawdza istnienie folderu `notatki` (i tworzy go w razie potrzeby) oraz wywołuje `odswiezListeNotatek()`, aby załadować notatki przy starcie.
    * **Używane klasy:** `QDir`, `QCoreApplication`.

* **`void odswiezListeNotatek()` (Slot publiczny)**
    * **Opis:** Odświeża listę notatek w głównym oknie.
    * **Działanie:** Czyści `QListWidget`, a następnie odczytuje zawartość folderu `notatki`, filtrując pliki `.txt`, i dodaje ich nazwy do listy.
    * **Używane klasy:** `QDir`, `QFileInfoList`, `QListWidget`.

* **`void on_przyciskZarzadzaj_clicked()` (Slot prywatny)**
    * **Opis:** Włącza lub wyłącza "tryb zarządzania".
    * **Działanie:** Działa jak przełącznik. Wywołuje funkcje pomocnicze `wejdzWTrybZarzadzania()` lub `wyjdzZTrybuZarzadzania()` w zależności od aktualnego stanu aplikacji (przechowywanego w zmiennej `m_trybZarzadzania`).

* **`void on_przyciskUsunZaznaczone_clicked()` (Slot prywatny)**
    * **Opis:** Usuwa wszystkie zaznaczone na liście notatki.
    * **Działanie:** Pobiera listę zaznaczonych elementów z `QListWidget`, prosi użytkownika o potwierdzenie, a następnie w pętli usuwa odpowiednie pliki z dysku za pomocą `QFile::remove()`. Na koniec odświeża listę.
    * **Używane klasy:** `QList<QListWidgetItem*>`, `QMessageBox`, `QFile`.

### Klasa `Notatka`

* **`void wczytajNotatke(const QString &sciezkaPliku)`**
    * **Opis:** Wczytuje dane notatki z pliku i konfiguruje okno edycji.
    * **Działanie:** Otwiera plik `.txt`, a następnie w pętli czyta go linia po linii. Analizuje nagłówek (linie przed separatorem `---`), odczytując wartości dla czcionki, rozmiaru, priorytetu i stanu przypięcia. Resztę pliku wczytuje jako treść notatki. Na koniec ustawia wszystkie kontrolki UI (np. `QComboBox`, `QCheckBox`, `QTextEdit`) zgodnie z wczytanymi danymi.
    * **Używane klasy:** `QFile`, `QTextStream`, `QStringList`, `QFont`.

* **`void zapiszDoPliku()`**
    * **Opis:** Zapisuje aktualny stan notatki (treść i opcje) do pliku `.txt`.
    * **Działanie:** Otwiera plik do zapisu, nadpisując jego zawartość. Zapisuje w nim kolejne linie nagłówka (`Klucz: Wartość`) na podstawie aktualnego stanu kontrolek UI. Po zapisaniu nagłówka dodaje separator `---`, a następnie zapisuje całą treść z `QTextEdit`. Na koniec emituje sygnał `notatkaZmieniona()`.
    * **Używane klasy:** `QFile`, `QTextStream`.

* **`void on_checkPrzypnij_toggled(bool checked)` (Slot prywatny)**
    * **Opis:** Włącza lub wyłącza tryb "zawsze na wierzchu" dla okna notatki.
    * **Działanie:** Manipuluje flagami okna. Pobiera aktualne flagi za pomocą `windowFlags()`, a następnie dodaje (`|`) lub usuwa (`& ~`) flagę `Qt::WindowStaysOnTopHint`. Na koniec wywołuje `show()`, aby system operacyjny zastosował zmiany.

* **`void notatkaZmieniona()` (Sygnał)**
    * **Opis:** Jest to sygnał (nie funkcja), który nie ma implementacji. Służy do komunikacji.
    * **Działanie:** Jest emitowany (`emit notatkaZmieniona();`) po zapisaniu lub usunięciu notatki. Główne okno `StickyNotes` ma slot `odswiezListeNotatek` podłączony do tego sygnału, dzięki czemu automatycznie aktualizuje swoją listę, gdy w podrzędnym oknie zajdą zmiany.

## 4. Wykorzystanie Koncepcji Programowania Obiektowego

Projekt `StickyNotes` jest zbudowany na elementach programowania obiektowego:

* **Klasy i Obiekty:** Cały projekt opiera się na dwóch głównych klasach: `StickyNotes` i `Notatka`. Obiekty (instancje) tych klas są tworzone w czasie działania programu, np. `Notatka *oknoNotatki = new Notatka();` tworzy nowy obiekt okna edycji.
* **Hermetyzacja (Enkapsulacja):** Dane członkowskie klas (`m_sciezkaKatalogu`, `m_trybZarzadzania` w `StickyNotes` czy `m_sciezkaPliku` w `Notatka`) są zadeklarowane jako `private`. Dostęp do nich i manipulacja nimi odbywa się wyłącznie poprzez publiczne metody (interfejs) klasy, np. `wczytajNotatke(...)`. Chroni to wewnętrzny stan obiektu przed niekontrolowanymi modyfikacjami z zewnątrz.
* **Konstruktory i Destruktory:** Obie klasy posiadają **konstruktory** (`StickyNotes(...)`, `Notatka(...)`), które inicjalizują obiekty, ustawiają UI i przygotowują stan początkowy. **Destruktory** (`~StickyNotes()`, `~Notatka()`) są odpowiedzialne za zwalnianie zasobów, np. `delete ui;` zwalnia pamięć przydzieloną na interfejs.
* **Dziedziczenie:** Jest to fundamentalny mechanizm wykorzystywany w projekcie. Nasze klasy dziedziczą po klasach z biblioteki Qt:
    * `class StickyNotes : public QMainWindow` – nasza klasa dziedziczy wszystkie cechy i funkcje głównego okna aplikacji.
    * `class Notatka : public QWidget` – nasza klasa dziedziczy zachowanie standardowego widżetu.
    Dzięki dziedziczeniu nie musimy pisać od zera kodu odpowiedzialnego za rysowanie okna, obsługę zdarzeń myszy czy pętlę zdarzeń – wszystko to dostajemy "w spadku" od klas bazowych Qt.
* **Operatory:** W projekcie wykorzystywane są przeciążone operatory, np.:
    * Operator `<<` w klasie `QTextStream` do zapisu danych do pliku.
    * Operatory bitowe `|` (OR), `&` (AND), `~` (NOT).

