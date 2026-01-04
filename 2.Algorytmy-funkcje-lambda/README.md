# Ćw 2: Algorytmy STL i funkcje lambda (przetwarzanie danych, kontenery, wyrażenia lambda)

## Ważne pojęcia

### Algorytmy niemodyfikujące
Operacje, które przeglądają kontener, ale nie zmieniają jego zawartości ani kolejności elementów (np. `std::for_each`, `std::count_if`). W systemach autonomicznych służą one do monitorowania stanów bez ryzyka zmiany danych źródłowych.

### Algorytmy modyfikujące
Algorytmy, które zmieniają zawartość kontenera poprzez przesuwanie, nadpisywanie lub usuwanie elementów (np. `std::sort`, `std::transform`, `std::remove_if`). Pozwalają na dynamiczne zarządzanie priorytetami przeszkód.

### Wyrażenia lambda
Funkcje anonimowe definiowane bezpośrednio w miejscu użycia. Pozwalają na przekazanie dedykowanej logiki do algorytmów STL bez konieczności definiowania zewnętrznych funkcji. Składnia: `[capture](params){body}`.

### Klauzula przechwytywania (Capture Clause)
Część lambdy `[]`, która decyduje, jakie zmienne z lokalnego zakresu są dostępne wewnątrz funkcji. Możemy przechwytywać przez kopię `[x]` (wartość stała w momencie tworzenia) lub przez referencję `[&x]` (dostęp do aktualnej wartości zmiennej).

### Erase-Remove Idiom
Standardowa technika C++ służąca do fizycznego usuwania elementów z kontenerów typu `std::vector`. Algorytm `remove_if` logicznie przesuwa elementy do usunięcia na koniec, a metoda `.erase()` faktycznie zwalnia miejsce i zmienia rozmiar kontenera.



### Predykat jednoargumentowy
Funkcja lub lambda przyjmująca jeden argument i zwracająca wartość typu `bool`. Jest to "instrukcja wyboru" dla algorytmów takich jak `remove_if` czy `count_if`.

## Cel zadania
Implementacja logiki przetwarzania danych z czujników pojazdu, obejmująca filtrację błędnych odczytów, sortowanie obiektów według dystansu oraz masowe przeliczanie jednostek miar.

## Zadania do wykonania

### Filtracja danych (Zadanie 1)
Wykorzystanie algorytmu `std::remove_if` wraz z lambdą w celu oczyszczenia wektora z odczytów nierealnych (np. wartości ujemne lub powyżej zakresu pracy sensora).

### Sortowanie priorytetów (Zadanie 2)
Zastosowanie `std::sort` z niestandardowym komparatorem w postaci lambdy, aby uporządkować wykryte przeszkody (klasa `Obstacle`) od najbliższej do najdalszej.

### Zliczanie zagrożeń (Zadanie 3)
Użycie `std::count_if` z lambdą **przechwytującą zmienną** `danger_count`, aby określić liczbę obiektów znajdujących się w krytycznej odległości od pojazdu.

### Transformacja jednostek (Zadanie 4)
Użycie `std::transform` do konwersji wszystkich danych w kontenerze (np. zamiana centymetrów na metry) z natychmiastowym nadpisaniem oryginalnych wartości.

### Raportowanie przez for_each (Zadanie 5)
Zastąpienie tradycyjnych pętli pętlą `std::for_each` w celu wywołania metod wyświetlających informacje (`printToConsole`) dla każdego elementu zestawu danych.