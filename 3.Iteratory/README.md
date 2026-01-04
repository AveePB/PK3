# Ćw 3: Iteratory i własne kontenery (Zarządzanie pamięcią i STL)

## Cel projektu
Celem zadania było zaimplementowanie własnej struktury danych (lista jednokierunkowa) z wykorzystaniem bezpiecznych mechanizmów zarządzania pamięcią (`smart pointers`) oraz stworzenie iteratora umożliwiającego integrację kontenera z biblioteką standardową (STL). Projekt obejmuje również zaawansowane techniki iteracji oraz bezpiecznego usuwania elementów.

---

## Kluczowe pojęcia i technologie

### 1. Inteligentne wskaźniki (`std::unique_ptr`)
W strukturze listy wykorzystano `std::unique_ptr` do zarządzania węzłami (`Node`). Gwarantuje to:
* **Automatyczne zwalnianie pamięci**: Brak konieczności ręcznego wywoływania `delete`.
* **Wyłączną własność**: Każdy węzeł jest "właścicielem" następnego, co eliminuje wycieki pamięci.

### 2. Semantyka przenoszenia (`std::move`)
Ponieważ `unique_ptr` jest typem niekopiowalnym, operacje takie jak `push_front` wymagają użycia `std::move`. Pozwala to na bezpieczne przekazanie własności wskaźnika `head` do nowo tworzonego węzła.

### 3. Iteratory i Dereferencja
Zaimplementowany **Iterator** pełni rolę pomostu między danymi a algorytmami.
* **`operator*` (Dereferencja)**: Pozwala na dostęp do danych wewnątrz węzła. Odróżnia się od mnożenia tym, że jest operatorem jednoargumentowym.
* **`operator++` (Inkrementacja)**: Przesuwa iterator na kolejny węzeł. Wersja prefiksowa zwraca `*this` (referencję do samego siebie), co poprawia wydajność i umożliwia łańcuchowe wywołania.

### 4. Unieważnienie iteratora (Iterator Invalidation)
Podczas operacji usuwania (`erase`), dotychczasowe iteratory stają się nieważne. Rozwiązaniem jest przypisanie do iteratora wartości zwracanej przez funkcję `erase()`, która wskazuje na kolejny poprawny element.

## Realizacja zadań (Analiza kodu)

### Zadanie 1: Własna lista `CustomList`
Stworzono szablon klasy zarządzającej dynamiczną listą. Wykorzystuje ona mechanizm przenoszenia, aby wstawiać elementy na początek listy w czasie stałym $O(1)$.

### Zadanie 2: Implementacja własnego iteratora
Dzięki dopisaniu klasy `Iterator` oraz metod `begin()` i `end()`, własna lista obsługuje:
* Algorytm `std::for_each`.
* Nowoczesną pętlę `range-based for`.
* Własne lambdy przetwarzające dane.



### Zadanie 3: Iteratory odwrotne (`rbegin`, `rend`)
Zademonstrowano użycie iteratorów odwrotnych na kontenerze `std::vector`. 
* **Mechanizm**: `rbegin()` wskazuje na ostatni element, a `++it` przesuwa nas w stronę początku.
* **Zastosowanie**: Przeglądanie historii logów od najnowszego wpisu.



### Zadanie 4: Bezpieczne filtrowanie danych
Zrealizowano algorytm usuwania liczb nieparzystych z wektora. 
* **Zastosowana technika**: Pętla `while` z ręcznym sterowaniem iteratorem.
* **Bezpieczeństwo**: Wykorzystanie `it = ids.erase(it)` zapobiega awarii programu po usunięciu elementu z pamięci.
