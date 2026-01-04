#include <iostream>
#include <memory>

namespace mz {

	/**
	 * @brief Klasa węzła.
	 */
	template <typename T>
	class Node {
	
	public:
		T data;
		std::unique_ptr<Node<T>> next;

		/**
		 * @brief Konstruktor inicjalizujący klasę węzła.
		 * @param value Wartość węzła.
		 */
		Node(T value) : data(value) { }
	};


	/**
	 * @brief Klasa prymitywnej listy.
	 */
	template <typename T>
	class CustomList {
	
	private:
		std::unique_ptr<Node<T>> head;

	public:
		/**
		 * @brief Domyślny konstruktor, inicjalizuje głowę jako nullptr.
		 */
		CustomList() : head(nullptr) { }

		/**
		 * @brief Funkcja dodająca element na początek listy.
		 * 
		 * @param value Wartość nowego elementu.
		 */
		void push_front(T value) {
			// Stwórz inteligentny wskaźnik 
			std::unique_ptr<Node<T>> new_head = std::make_unique<Node<T>>(value);

			// Przypisz nową głowę
			new_head->next = std::move(head);
			this->head = std::move(new_head);
		}

		/**
		 * @brief Wypisuje wartości tablicy do konsoli.
		 */
		void printToConsole() const {
			// Stwórz surowy wskaźnik
			Node<T>* currNode = head.get();
			std::cout << "CustomList elements: [";

			// Przejrzyj wszystkie elementy listy
			while (currNode) {
				// Wyświetl wartość do konsoli i przejdź do następnego węzła
				std::cout << currNode->data << ", ";
				currNode = currNode->next.get();
			}

			std::cout << "] \n";
		}


		/**
		 * @brief Klasa iterator będąca customowy iteratorem klasy CustomList.
		 */
		class Iterator {
		private:
			Node<T>* current; // Służy nam tylko do podglądania.

		public:
			/**
			 * @brief Konstruktor przypisujący aktulany wskaźnik.
			 * @param ptr aktualny wskaźnik.
			 */
			Iterator(Node<T>* ptr) : current(ptr) { }

			/**
			 * @brief Funkcja przeciążająca operator dereferencji (pobieranie danych *it).
			 */
			T& operator*() { return current->data; };

			/**
			 * @brief Funkcja przeciążająca operator inkrementacji przedni (++it). Celem jest przejście do następnego elementu.
			 */
			Iterator& operator++() {
				if (current) current = current->next.get();
				return *this; // Zwaraca wartość samego siebie (Iteratora)
			}

			/**
			 * @brief Funkcja przeciążająca operator inkrementacji tylnej (it++). Celem jest przejście do następnego elementu.
			 */
			Iterator& operator++(int) {
				if (current) current = current->next.get();
				return *this; // Zwaraca wartość samego siebie (Iteratora)
			}

			/**
			 * @brief Funckja przeciążająca operator porównania (!=). Celem jest sprawdzenie czy iteratory nie wskazują na ten sam element.
			 * @param other Inny iterator.
			 * @return Wartość boolean.
			 */
			bool operator!=(const Iterator& other) const {
				return this->current != other.current;
			}
		};

		/**
		 * @brief Funkcja zwracająca iterator do pierwszego elementu.
		 * 
		 * @return Iterator pierwszego elementu. 
		 */
		Iterator begin() { return Iterator(this->head.get()); }

		/**
		 * @brief Funkcja zwracająca iterator do ostatniego elementu.
		 *
		 * @return Iterator ostatniego elementu. Czyli nullptr
		 */
		Iterator end() { return Iterator(nullptr); }
	};
}