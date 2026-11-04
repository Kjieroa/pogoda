# 🌦️ System pomiarów stacji pogodowej

## 📌 Opis projektu

Projekt przedstawia program napisany w języku **C++**, służący do obsługi pomiarów stacji pogodowych.

Program umożliwia wczytywanie danych z pliku tekstowego, przechowywanie ich w strukturze `vector`, wyszukiwanie pomiaru z minimalną temperaturą oraz wyszukiwanie pomiarów przekraczających określony próg temperatury.

---

## ⚙️ Funkcjonalności programu

- 📂 **Wczytywanie danych z pliku** – odczytywanie pomiarów z pliku `dane.txt`.
- 🌡️ **Wyszukiwanie minimalnej temperatury** – znalezienie rekordu z najniższą temperaturą wraz z pozostałymi danymi.
- 🔎 **Wyszukiwanie pomiarów powyżej progu** – wyświetlanie pomiarów, których temperatura przekracza podaną wartość.
- 📋 **Wyświetlanie wszystkich pomiarów** – prezentowanie wszystkich rekordów zapisanych w wektorze.
- ⚠️ **Obsługa błędów** – wykorzystanie mechanizmu `try-catch` do obsługi nieprawidłowych danych i błędów odczytu pliku.

---

## 🛠️ Wykorzystane technologie

- **C++**
- `iostream` – obsługa wejścia i wyjścia.
- `fstream` – obsługa plików.
- `sstream` – przetwarzanie danych tekstowych.
- `vector` – przechowywanie pomiarów.
- `string` – obsługa tekstu.
- `stdexcept` – obsługa wyjątków.

---

## 📁 Struktura projektu

    pogoda/
    ├── main.cpp
    ├── dane.txt
    └── README.md

---

## 📄 Format pliku dane.txt

Dane pomiarowe przechowywane są w pliku tekstowym `dane.txt`.

Każdy rekord składa się z czterech wartości oddzielonych średnikami:

1. **ID stacji** – identyfikator stacji pogodowej.
2. **Data** – data wykonania pomiaru.
3. **Temperatura** – temperatura w stopniach Celsjusza.
4. **Wiatr** – wartość pomiaru wiatru.

### Przykładowa zawartość pliku:

    STO1;2026-03-01;20.5;12.5;
    STO2;2026-04-01;14.2;11.2;
    STO3;2026-04-05;32.5;15.2;
    STO1;2026-04-10;8.4;9.5;
    STO4;2026-04-15;28.7;13.1;
    STO2;2026-05-01;35.2;17.8;

---

## 🧱 Struktura programu

### 1. Struktura `Pomiar`

Struktura przechowuje pojedynczy rekord pomiarowy.

Zawiera następujące pola:

- `idStacji` – identyfikator stacji pogodowej (`string`).
- `data` – data pomiaru (`string`).
- `temperatura` – temperatura (`double`).
- `wiatr` – wartość pomiaru wiatru (`double`).

### 2. Klasa `Pomiary`

Klasa odpowiada za przechowywanie i obsługę wszystkich pomiarów pogodowych.

Pomiary przechowywane są w prywatnym wektorze:

    vector<Pomiar> baza;

### 3. Metody klasy `Pomiary`

| Metoda | Opis |
|---|---|
| `wczytajZPliku()` | Wczytuje dane z pliku tekstowego. |
| `znajdzTemperatureMinimalna()` | Znajduje pomiar z najniższą temperaturą i zwraca cały rekord. |
| `wyszukajPowyzejProgu()` | Wyszukuje pomiary z temperaturą większą od podanego progu. |
| `wyswietlPomiar()` | Wyświetla pojedynczy rekord pomiarowy. |
| `wyswietlWszystkie()` | Wyświetla wszystkie pomiary zapisane w wektorze. |

---

## ▶️ Działanie programu

Po uruchomieniu program wykonuje następujące operacje:

1. Tworzy obiekt klasy `Pomiary`.
2. Wczytuje dane z pliku `dane.txt`.
3. Wyświetla wszystkie wczytane pomiary.
4. Wyszukuje rekord z minimalną temperaturą.
5. Wyświetla pomiary, których temperatura przekracza **25°C**.

### Przykładowe wywołanie wyszukiwania:

    stacja.wyszukajPowyzejProgu(25);

Program wyświetli wszystkie rekordy, w których temperatura jest większa niż 25 stopni Celsjusza.

---

## ⚠️ Obsługa błędów

Program wykorzystuje mechanizm wyjątków `try-catch`.

Obsługiwane sytuacje:

- Brak możliwości otwarcia pliku.
- Brak wymaganych danych w rekordzie.
- Niepoprawny format wartości liczbowych.
- Próba znalezienia minimalnej temperatury w pustej bazie pomiarów.

W przypadku wykrycia błędu program wyświetla odpowiedni komunikat.

---

## 💻 Kompilacja programu

Do skompilowania programu można wykorzystać kompilator `g++`.

    g++ main.cpp -o pogoda

### Uruchomienie programu

**Windows:**

    pogoda.exe

**Linux:**

    ./pogoda

---

## 🎯 Cel projektu

Celem projektu jest wykorzystanie podstawowych elementów języka C++ w praktyce, w szczególności:

- Struktur (`struct`).
- Klas i metod.
- Wektorów (`vector`).
- Operacji na plikach tekstowych.
- Przetwarzania danych wejściowych.
- Wyszukiwania i filtrowania rekordów.
- Obsługi wyjątków (`try-catch`).

---

## 👨‍💻 Autor

Projekt edukacyjny – system obsługi pomiarów stacji pogodowej napisany w języku **C++**.
