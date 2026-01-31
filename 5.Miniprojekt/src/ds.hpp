#ifndef DS_HPP
#define DS_HPP

// Biblioteki
#include <iostream>
#include <memory>

/**
 * @brief Przestrzeń nazw przechowywująca własnoręcznie napisane kontenery.
 */
namespace myds {

	/**
	 * @brief Własna implementacja wektora z biblioteki STL. 
	 */
	template<typename T>
	class CustomVector {
	private:
		const size_t DEFAULT_CAPACITY = 1; // < Domyślna wieklość tablicy.

		size_t actual_capacity; // < Rzeczywisty rozmiar tablicy. 
		size_t n_elements; // < Liczba zapełnionych elementów tablicy. 
		T* arr; // < Dynamicznie zaalokowana tablica.

		/**
		 * @brief Rozszerza tablicę elementów dwukrotnie.
		 */
		void extendArray() {
			// Stwórz tablicę pomocniczą 
			std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(2 * this->actual_capacity);

			for (size_t i = 0; i < n_elements; i++) new_arr[i] = this->arr[i];

			// Usuń starą tablicę i przenieś nową
			delete[] this->arr;
			this->arr = new_arr.release();
			this->actual_capacity *= 2;
		}

	public:
		/**
		 * @brief Inicjalizuje kontener bez żadnych elementów domyślnie.
		 */
		CustomVector() : actual_capacity(DEFAULT_CAPACITY), n_elements(0), arr(new T[DEFAULT_CAPACITY]) { }

		/**
		 * @brief Inicjalizuje tablicę kontenera na co najmniej n elementów.
		 * @param n Liczba elementów we wektorze.
		 */
		CustomVector(size_t n) : actual_capacity(2*n), n_elements(0), arr(new T[2*n]) { }

		/**
		 * @brief Konsturktor kopiujący tworzący głęboką kopię.
		 * @param other_vec Inny wektor na bazie którego tworzymy głęboką kopię.
		 */
		CustomVector(const CustomVector<T>& other_vec) : actual_capacity(other_vec.actual_capacity), n_elements(other_vec.n_elements), arr(new T[other_vec.actual_capacity]) {
			// Initialize array elements with the same values
			for (size_t i = 0; i < other_vec.n_elements; i++)
				this->arr[i] = other_vec.arr[i];
		}

		/**
		 * @brief Konstruktor przenoszący, przenosi dane z innego obiektu i go przywaraca do postaci domyślnej.
		 * @param other_vec Inny wektor.
		 */
		CustomVector(CustomVector<T>&& other_vec) {
			// Przypisz dane z innego obiektu 
			this->actual_capacity = other_vec.actual_capacity;
			this->n_elements = other_vec.n_elements;
			this->arr = other_vec.arr;

			// Opróżnij inny obiekt
			other_vec.actual_capacity = DEFAULT_CAPACITY;
			other_vec.n_elements = 0;
			other_vec.arr = new T[DEFAULT_CAPACITY];
		}

		/**
		 * @brief Usuwa zaalokowaną pamięć.
		 */
		~CustomVector() { delete[] arr; }
		
		/**
		 * @brief Zwraca liczbę zapełnionych elementów kontenera.
		 * @return Liczba zapełnionych elementów kontenera.
		 */
		size_t size() const { return this->n_elements; }
		
		/**
		 * @brief Dodaje element do kontenera i inkrementuje liczbę zapełnionych elementów.
		 * @param val Wartość nowo dodanego elementu.
		 */
		void pushBack(const T& val) { 
			// Tablica jest zbyt mała
			if (n_elements == actual_capacity) extendArray();

			// Przypisz nowy element
			this->arr[this->n_elements++] = val;
		}

		/**
		 * @brief Dodaje element do kontenera i inkrementuje liczbę zapełnionych elementów.
		 * @param val Wartość nowo dodanego elementu.
		 */
		void pushBack(T&& val) { 
			// Tablica jest zbyt mała
			if (n_elements == actual_capacity) extendArray();
			
			// Przypisz nowy element
			this->arr[this->n_elements++] = std::move(val); 
		}

		/**
		 * @brief Zwalania aktualnie zajmowaną pamięć i przywraca wektora do stanu domyślnego.
		 */
		void clear() {
			// Usuń tablicę
			std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(DEFAULT_CAPACITY);
			delete[] arr;

			// Zaalokuj domyślną
			this->arr = new_arr.release();
			this->actual_capacity = DEFAULT_CAPACITY;
			this->n_elements = 0;
		}

		/**
		 * @brief Sprawdza czy wektor jest pusty.
		 * @return Prawda/Fałsz. 
		 */
		bool empty() const { return this->n_elements == 0; }

		/**
		 * @brief Zwraca stałą wartość elementu wektora pod indeksem.
		 * @param idx Unikalny indeks elementu wektora.
		 * @return Element odpowiadający indeksowi.
		 */
		const T& at(size_t idx) const {
			// Zgłoś wyjątek
			if (idx >= n_elements) throw std::out_of_range("Index out of bounds");
			return this->arr[idx];
		}

		/**
		 * @brief Nadpisany operator, który zwraca stałą wartość elementu wektora pod indeksem.
		 * @param idx Unikalny indeks elementu wektora.
		 * @return Element odpowiadający indeksowi.
		 */
		 const T& operator[](size_t idx) const { return at(idx); }

		/**
		 * @brief Nadpisany operator, który zwraca referencję do elementu wektora pod indeksem. Używany jest do
		 * zmiany wartości elementu pod konkretnym indeksem.
		 * @param idx Unikalny indeks elementu wektora.
		 * @return Element odpowiadający indeksowi.
		 */
		 T& operator[](size_t idx) { 
			 // Zgłoś wyjątek
			 if (idx >= n_elements) throw std::out_of_range("Index out of bounds");
			 return this->arr[idx]; 
		 }

		 /**
		  * @brief Tworzy głęboką kopię, czyli przepisuje wszystkie elementy innego wektora.
		  * @param other_vec Inny wektor.
		  * @return Referencja do wektora. 
		  */
		 const CustomVector& operator=(const CustomVector<T>& other_vec) {
			 // Stwórz tablicę pomocniczą 
			 std::unique_ptr<T[]> new_arr = std::make_unique<T[]>(other_vec.actual_capacity);
			 for (size_t i = 0; i < other_vec.n_elements; i++) new_arr[i] = other_vec.arr[i];

			 // Usuń starą tablicę i przenieś nową
			 delete[] this->arr;
			 this->arr = new_arr.release();
			 this->actual_capacity = other_vec.actual_capacity;
			 this->n_elements = other_vec.n_elements;

			 return *this;
		 }

		 /**
		  * @brief Własna implementacja iteratora do struktury CustomVector. Służy nam do łatwego dostępu do danych.
		  */
		 class Iterator {
		 private:
			 T* arr; // < Wskaźnik podlądowy na tablicę.
			 size_t idx; // Aktualny indeks elementu.
			 size_t size; // < Liczba elementów we wektorze.

		 public:
			 /**
			  * @brief Konstruktor domyślny, zablokowany.
			  */
			 Iterator() = delete;

			 /**
			  * @brief Konstruktor inicjalizujący itearator.
			  * @param arr Wskaźnik do tablicy.
			  * @param size Rozmiar wektora.
			  * @param is_end Mówi nam czy tworzyć iterator do końca kontenera.
			  */
			 Iterator(T* arr, size_t size, bool is_end = false) : arr(arr), size(size), idx(0) { if (is_end) idx = size; }

			 /**
			  * @brief Przechodzi do kolejnego elementu wektora.
			  * @return Iterator do kolejnego elementu. 
			  */
			 Iterator& next() {
				 idx++;
				 return *this;
			 }

			 /**
			  * @brief Rozpakowywuje wartość chowaną pod konkretnym elementem.
			  * @return Wartość elementu wektora.
			  */
			 T& operator*() { return this->arr[idx]; }

			 /**
			  * @brief Rozpakowywuje wartość chowaną pod konkretnym elementem.
			  * @return Wartość elementu wektora
			  */
			 const T& operator*() const { return this->arr[idx]; }

			 /**
			  * @brief Nadpisany operator inkrementacji (++iter), który przechodzi do kolejnego elementu.
			  * @return Iterator do kolejnego elementu. 
			  */
			 Iterator& operator++() { return next(); }
			
			 /**
			  * @brief Nadpisany operator inkrementacji (iter++), który przechodzi do kolejnego elementu.
			  * @return Iterator do kolejnego elementu.
			  */
			 Iterator& operator++(int) { return next(); }

			 /**
			  * @brief Nadpisany operator przyrównania (==), który porównuje wartości indeksów.
			  * @param other_iter Inny iterator.
			  * @return Prawda/Fałsz 
			  */
			 bool operator==(const Iterator& other_iter) const { return this->idx == other_iter.idx; }

			 /**
			  * @brief Nadpisany operator przyrównania (!=), który porównuje wartości indeksów.
			  * @param other_iter Inny iterator.
			  * @return Prawda/Fałsz
			  */
			 bool operator!=(const Iterator& other_iter) const { return this->idx != other_iter.idx; }
		 };

		 /**
		  * @brief Tworzy iterator do pierwszego elementu wektora.
		  * @return Iterator do pierwszego elementu wektora. 
		  */
		 Iterator begin() const { return Iterator(this->arr, this->n_elements); }

		 /**
		 * @brief Tworzy iterator do końca wektora.
		 * @return Iterator do pierwszego elementu wektora.
		 */
		 Iterator end() const { return Iterator(this->arr, this->n_elements, true); }
	};

	/**
	 * @brief Własna implementacja listy jednokierunkowej. To kontener LIFO (Last in first out).
	 */
	template<typename T>
	class LinkedList {
	private:
		/**
		 * @brief Węzeł listy jednokierunkowej.
		 */
		class Node {
		public:
			std::unique_ptr<Node> next; // < Inteligentny wskaźnik do kolejnego elementu.
			T value; // < Wartość przechowywana we węźle.
		
			/**
			 * @brief Konstruktor domyślny, inicjalizujący pusty węzeł.
			 */
			Node() { }

			/**
			 * @brief Konstruktor kopiujący, zablokowany.
			 * @param other Inny obiekt.
			 */
			Node(const Node& other) = delete;

			/**
			 * @brief Konstruktor przenoszący, zablokowany.
			 * param other Inny obiekt.
			 */
			Node(const Node&& other) = delete;

			/**
			 * @brief Konstruktor, który przenosi inteligentny wskaźnik na następny element oraz tworzy nową wartość we węźle.
			 * @param next Inteligentny wskaźnik do następnego węzła.
			 * @param value Wartość przechowywana we węźle.
			 */
			Node(std::unique_ptr<Node>&& next, const T& value) : next(std::move(next)), value(value) { }

			/**
			 * @brief Konstruktor, który przenosi inteligentny wskaźnik na następny element oraz przenosi nową wartość do węzła.
			 * @param next Inteligentny wskaźnik do następnego węzła.
			 * @param value Wartość przechowywana we węźle.
			 */
			Node(std::unique_ptr<Node>&& next, const T&& value) : next(std::move(next)), value(std::move(value)) {}
		};

		std::unique_ptr<Node> head; // < Inteligentny wskaźnik na pierwszy element listy.

	public:
		/*
		* @brief Konstruktor domyślny, tworzący pustą listę.
		*/
		LinkedList() { }

		/**
		 * @brief Konstruktor kopiujący, zablokowany.
		 * @param other_list Inna lista.
		 */
		LinkedList(const LinkedList& other_list) = delete;

		/**
		 * @brief Konstruktor przenoszący, zablokowany.
		 * @param other_list Inna lista.
		 */
		LinkedList(const LinkedList&& other_list) = delete;

		/**
		 * @brief Dodaje nowy element na samą górę listy.
		 * @param value Wartość nowego węzła.
		 */
		void add(const T& value) {
			// Stwórz nowy węzeł
			std::unique_ptr<Node> new_head = std::make_unique<Node>(std::move(this->head), value);
			this->head = std::move(new_head);
		}

		/**
		 * @brief Przenosi nową wartość i dodaje węzeł na górę listy.
		 * @param value Wartość nowego węzła.
		 */
		void add(T&& value) {
			// Stwórz nowy węzeł
			std::unique_ptr<Node> new_head = std::make_unique<Node>(std::move(this->head), std::move(value));
			this->head = std::move(new_head);
		}

		/**
		 * @brief Usuwa pierwszy element listy.
		 */
		void pop() {
			// Jeśli nie jest pusta
			if (this->head.get()) 
				this->head = std::move(this->head.get()->next);
		}

		/**
		 * @brief Sprawdza czy lista jest pusta.
		 * @return Prawda/Fałsz. 
		 */
		bool empty() { return this->head.get() == nullptr; }

		/**
		  * @brief Własna implementacja iteratora do struktury LinkedList. Służy nam do łatwego dostępu do danych.
		  */
		class Iterator {
		private:
			Node* curr_node; // < Wskaźnik podlądowy na węzeł

		public:
			/**
			 * @brief Konstruktor domyślny, zablokowany.
			 */
			Iterator() = delete;

			/**
			 * @brief Konstruktor inicjalizujący itearator.
			 * @param curr_node Wskaźnik podglądowy.
			 */
			Iterator(Node* curr_node) : curr_node(curr_node) { }

			/**
			 * @brief Przechodzi do kolejnego elementu Listy.
			 * @return Iterator do kolejnego elementu.
			 */
			Iterator& next() {
				if (curr_node) curr_node = curr_node->next.get();
				return *this;
			}

			/**
			 * @brief Rozpakowywuje wartość chowaną pod konkretnym elementem.
			 * @return Wartość elementu listy.
			 */
			T& operator*() { return this->curr_node->value; }

			/**
			 * @brief Rozpakowywuje wartość chowaną pod konkretnym elementem.
			 * @return Wartość elementu listy.
			 */
			const T& operator*() const { return this->curr_node->value; }

			/**
			 * @brief Nadpisany operator inkrementacji (++iter), który przechodzi do kolejnego elementu.
			 * @return Iterator do kolejnego elementu.
			 */
			Iterator& operator++() { return next(); }

			/**
			 * @brief Nadpisany operator inkrementacji (iter++), który przechodzi do kolejnego elementu.
			 * @return Iterator do kolejnego elementu.
			 */
			Iterator& operator++(int) { return next(); }

			/**
			 * @brief Nadpisany operator przyrównania (==), który porównuje wskaźniki.
			 * @param other_iter Inny iterator.
			 * @return Prawda/Fałsz
			 */
			bool operator==(const Iterator& other_iter) const { return this->curr_node == other_iter.curr_node; }

			/**
			 * @brief Nadpisany operator przyrównania (!=), który porównuje wartości indeksów.
			 * @param other_iter Inny iterator.
			 * @return Prawda/Fałsz
			 */
			bool operator!=(const Iterator& other_iter) const { return this->curr_node != other_iter.curr_node; }
		};

		/**
		 * @brief Tworzy iterator będący na pierwszym elemencie.
		 * @return Iterator na pierwszym elemencie. 
		 */
		Iterator begin() const { return Iterator(this->head.get()); }

		/**
		 * @brief Tworzy iterator będący na końcu kontenera.
		 * @return Iterator na końcu kontenera.
		 */
		Iterator end() const { return Iterator(nullptr); }
	};
};
#endif