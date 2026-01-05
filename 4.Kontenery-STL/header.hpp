#include <iostream>

/**
 * @brief Klasa odpowiadająca za przechowywanie wiadomości.
 */
template <typename T>
class LogMessage {

	// Prywantne zmienne
private:
	int id;
	std::string msg;
	T priority;

public:

	/**
	 * @brief Konstruktor inicjalizujący identyfikator, wiadomość i priorytet dowolnego typu.
	 * 
	 * @param id Identyfikator wiadomości.
	 * @param msg Wiadomość loga.
	 * @param priority Stopień ważności.
	 */
	LogMessage(int id, std::string msg, T priority) : id(id), msg(msg), priority(priority) {}

	/**
	 * @brief Funkcja nadpisująca operator porównywania (<).
	 * 
	 * @param other inny obiekt tpu LogMessage. 
	 * @return wartość boolean, mówiącą że wiadomość ma mniejszy priorytet. 
	 */
	bool operator<(const LogMessage<T>& other) const {
		return this->priority < other.priority;
	}

	/**
	 * Funkcja getter zwracjąca wartość id.
	 * 
	 * @return id. 
	 */
	int getId() const {
		return this->id;
	}

	/**
	 * Funkcja getter zwracjąca wartość msg.
	 *
	 * @return msg.
	 */
	std::string getMsg() const {
		return this->msg;
	}

	/**
	 * Funkcja getter zwracjąca wartość priority.
	 *
	 * @return priority.
	 */
	T getPriority() const {
		return this->priority;
	}
};
