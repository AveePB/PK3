# PK3 Logger
Aplikacja to logger, który zapisuje informacje dotyczące zachowań programu do pliku .log. To prosta wersja wykorzystująca wymagane elementy C++ z zajęć labolatoryjnych.

## Korzystanie z programu
Menu jest dość łatwe do interakcji. Gdy pojawia się numerowane menu należy wciśnąć numer, który jest obok interesującej nas operacji np. 1. 

> Logi są zapisywane do pliku *logs_from_sensors.log* w tym samym folderu, gdzie został program uruchomiony.
## Struktura miniprojektu
W celu pokazania możliwości loggera, program jest wyposażony w interfejs, który oferuje możliwość tworzenia nowych logów, przeglądania wcześniej zapisanych oraz zapisanie logów do pliku *logs_from_sensors.log*.

## Realizacja wymagań przedmiotu PK3
1. **Szablony**: wykorzystano szablon domyślny do zdefiniowania klasy wektora i listy jednokierunkowej.
2. **Funkcja lambda/algorytmy na strukturze**: znaleziono zastosowanie przy metodzie pozwalającej na podanie jako argument funkcji własnego predykatu. 
3. **Interfejs iteratorów**: został stworzony dla zdefiniowanych kontenerów.
4. **Inteligentne wskaźniki**: zaimplementowane je w klasie Node do wskazania na następny węzeł. Zostały także wykorzystane podczas przepisywania wartości w wektorze.
5. **Własna implementacja kontenera**: wektor i lista jednokierunkowa.
