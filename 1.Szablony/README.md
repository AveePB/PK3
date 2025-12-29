# Ćw 1: Szablony (szablony klas i funkcji, dziedziczenie szablonów, szablon ogólny, szablon szczegółowy)

## Ważne pojęcia

### Polimorfizm statyczny
Statyczny polimorfizm to technika programowania, która pozwala na wybór zachowania w czasie kompilacji. W C++ statyczny polimorfizm jest realizowany za pomocą szablonów klas.

### Specjalizacja szablonu
Technika pozwalająca na zdefiniowanie zupełnie innej implementacji klasy dla konkretnego typu danych.

### Zastosowanie const
Zastosowanie modyfikatora const przy metodzie display(). Gwarantuje to, że funkcja jedynie odczytuje dane i nie zmienia stanu obiektu.

### Destruktor wirtualny
Kluczowy element w klasie bazowej, zapewniający poprawne zwolnienie pamięci klas pochodnych (DetailedSensorData) podczas pracy z polimorfizmem. Zapobiega wyciekom pamięci.

### Zastosowanie override
życie słowa kluczowego override w klasach pochodnych. Informuje ono kompilator, że intencją jest nadpisanie funkcji wirtualnej z klasy bazowej, co pozwala uniknąć błędów w sygnaturach funkcji.

### Dedukcja argumentów szablonu
Funkcjonalność kompilatora, która automatycznie rozpoznaje typ danych przekazywany do funkcji printInfo, co pozwala na krótszy zapis wywołania bez jawnego podawania typu w nawiasach ```< >```.

## Cel zadania
Stworzenie systemu wyświetlnia odczytanych informacji z czujników (lidar, kamera, informacja zwrotna itp.) przy użyciu szablonów.

## Zadania do wykonania

### Szablon ogólny klasy
Klasa ```SensorData<T>``` powinna przechowywać wartość odczytu oraz unikalne ID czujnika.

### Szablon szczegółowy klasy
Klasa ```SensorData<std::string>``` powinna być wysepcjalizowana dla wartości odczytu typu string. 

### Szablon dziedziczony
Klasa ```DetaliedSensorData<T>``` powinna dziedziczyć z szabolonu ```SensorData<T>``` oraz przechowywać dodatkową wiadomość zwrotną z czujnika.

### Szablon funkcji
Funkcja ```printInfo<T>``` logguje informacje do konsoli. Użyj dwóch jedno z wymuszeniem typu T, oraz z automatyczną dedukcją