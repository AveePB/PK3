# Ćwiczenie 4: Kontenery asocjacyjne i adaptery biblioteki STL

## Cel projektu
Celem ćwiczenia było zapoznanie się z zaawansowanymi strukturami danych dostępnymi w bibliotece STL (Standard Template Library). Projekt koncentruje się na efektywnym wyszukiwaniu danych, eliminacji duplikatów oraz modelowaniu przepływu informacji za pomocą dedykowanych adapterów (kolejki i stosu).

## Kluczowe pojęcia i technologie

### 1. Kontenery asocjacyjne (`std::map`, `std::set`)
W przeciwieństwie do kontenerów sekwencyjnych, dane są tu przechowywane w sposób uporządkowany (zazwyczaj przy użyciu struktur drzewiastych).
* **`std::map`**: Przechowuje pary klucz-wartość. Pozwala na szybki dostęp do danych na podstawie unikalnego klucza. Złożoność wyszukiwania wynosi $O(\log n)$.
* **`std::set`**: Przechowuje wyłącznie unikalne klucze w porządku rosnącym. Próba wstawienia duplikatu jest automatycznie ignorowana przez kontener.

### 2. Kolejka Priorytetowa (`std::priority_queue`)
Jest to adapter, który zarządza elementami w taki sposób, aby na szczycie (`top()`) zawsze znajdował się element o najwyższym priorytecie. Wymaga to zdefiniowania relacji porządku (np. przeciążenia operatora `<` w klasie `LogMessage`).

### 3. Logika LIFO vs FIFO
To dwa podstawowe modele dostępu do danych w adapterach:
* **FIFO (First-In, First-Out)**: Zasada działania kolejki (`std::queue`). Pierwszy element dodany do kontenera jest pierwszym, który go opuszcza.
* **LIFO (Last-In, First-Out)**: Zasada działania stosu (`std::stack`). Ostatni element dodany na szczyt jest pierwszym pobieranym.

## Analiza realizacji zadań

### Zadanie 1: Zarządzanie opisami sensorów (`std::map`)
Zaimplementowano bazę danych sensorów, gdzie kluczem jest `int` (identyfikator), a wartością `std::string` (opis).
* **Nadpisywanie danych**: Kod demonstruje, że przypisanie nowej wartości do istniejącego klucza (`sensors[13] = ...`) skutkuje aktualizacją rekordu.
* **Bezpieczne wyszukiwanie**: Wykorzystano metodę `.find()`, która pozwala sprawdzić istnienie klucza przed próbą dostępu, unikając niejawnego tworzenia pustych elementów przez operator `[]`.

### Zadanie 2: Unikalne kody systemowe (`std::set`)
Stworzono zbiór kodów statusowych pojazdu.
* **Eliminacja duplikatów**: Mimo wielokrotnego dodawania kodu `100` i `204`, zbiór zachował tylko po jednej kopii każdego z nich.
* **Weryfikacja**: Pokazano, jak za pomocą `.find()` sprawnie sprawdzić obecność kodu błędu w systemie.

### Zadanie 3: Priorytetyzacja logów (`std::priority_queue`)
Użyto kolejki priorytetowej do obsługi komunikatów systemowych typu `LogMessage`.
* **Porządek wyjścia**: Elementy są pobierane nie według kolejności dodania, lecz według wartości priorytetu (od najwyższego do najniższego).
* **Metody**: Wykorzystano `top()` do odczytu i `pop()` do usuwania przetworzonych logów.

### Zadanie 4: Modelowanie kolejek rzeczywistych (`std::queue`, `std::stack`)
Zademonstrowano różnicę w działaniu dwóch podstawowych adapterów:
* **Myjnia (Kolejka)**: Pierwsze auto, które wjechało ("Audi R8"), jako pierwsze opuściło kolejkę.
* **Stos książek (Stos)**: Ostatnia książka położona na stosie ("Frieren") została z niego zdjęta jako pierwsza.
