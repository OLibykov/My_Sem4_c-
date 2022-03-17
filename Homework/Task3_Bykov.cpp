#include <iostream>
#include <cstring>

class Data {
	char* name_firm;
	long long int phone_number;
	long long int order_number;
public:
	Data(const char* n_f, long long int p_n, long long int o_n) {
		name_firm = new char[strlen(n_f) + 1];
		std::copy(n_f, n_f + strlen(n_f) + 1, name_firm);
		phone_number = p_n;
		order_number = o_n;
	}
	Data(const Data & dat) {
		name_firm = new char[strlen(dat.name_firm) + 1];
		std::copy(dat.name_firm, dat.name_firm + strlen(dat.name_firm) + 1, name_firm);
		phone_number = dat.phone_number;
		order_number = dat.order_number;
	}
	~Data() {
		delete [] name_firm;
	}
	void print_data() {
		std::cout << name_firm << " " << phone_number << " " << order_number << std::endl;
	}
};
struct List {//список данных
	Data data;//данные
	struct List* next;
	struct List* last;
public:
	List(const Data & dat) : data(dat), next(NULL), last(NULL) {
	}
	List(const Data & dat, List* nex, List* las) : data(dat), next(nex), last(las) {
	}
	void print_nexus() {
		data.print_data();
	}
};

class list {
	List* List_beg;
	List* List_end;
public:
	list() {//конструктор по умолчанию
		List_beg = NULL;
		List_end = NULL;
		//std::cout << "\nThe default constructor worked successfully\n";
	}
	list(const Data & dat) {//конструктор
		List_beg = new List(dat);
		List_end = List_beg;
		//std::cout << "\nThe constructor worked successfully\n";
	}
	~list() {
		List* hlp;
		while (List_beg != List_end) {
			hlp = List_beg->next;
			delete List_beg;
			List_beg = hlp;
		}
		delete List_end;
	}
	void push_front(const Data & dat) {// функция добавления элемента в начало
		if (List_beg != NULL) {
			List* hlp;
			hlp = new List(dat, List_beg, NULL);
			List_beg->last = hlp;
			List_beg = hlp;
			hlp = NULL;
		}
		else {
			List_beg = new List(dat);
			List_end = List_beg;
		}
		return;
	}
	void push_back(const Data & dat) {// функция добавления элемента в конец
		if (List_end != NULL) {
			List* hlp;
			hlp = new List(dat, NULL, List_end);
			List_end->next = hlp;
			List_end = hlp;
			hlp = NULL;
		}
		else {
			List_beg = new List(dat);
			List_end = List_beg;
		}
		return;
	}
	Data front() {//чтение первого элемента списка
		if (List_beg != NULL) {
			return List_beg->data;
		}
		else {
			std::cout << "list is empty" << std::endl;
			Data d0("error", 0, 0);
			return d0;
		}
	}
	Data back() {//чтение последнего элемента списка 
		if (List_end != NULL) {
			return List_end->data;
		}
		else {
			std::cout << "list is empty" << std::endl;
			Data d0("error", 0, 0);
			return d0;
		}
	}
	void pop_front() {//удаление первого элемента списка
		if (List_beg != NULL) {
			if (List_beg->next == NULL) {
				delete List_beg;
				List_beg = NULL;
				List_end = NULL;
			}
			else {
				List* hlp = List_beg->next;
				hlp->last = NULL;
				delete List_beg;
				List_beg = hlp;
				hlp = NULL;
			}
		}
		else {
			std::cout << "You can't delete an item from an empty list" << std::endl;
		}
		return;
	}
	void pop_back() {//удаление последнего элемента списка
		if (List_end != NULL) {
			if (List_end->last == NULL) {
				delete List_end;
				List_end = NULL;
				List_beg = NULL;
			}
			else {
				List* hlp = List_end->last;
				hlp->next = NULL;
				delete List_end;
				List_end = hlp;
				hlp = NULL;
			}
		}
		else {
			std::cout << "You can't delete an item from an empty list" << std::endl;
		}
		return;
	}
void insert(int p, const Data & dat) {//добавление элемента x перед позицией p(нумерация с 1)
		int k = size();
		if (k < p - 1) {
			std::cout << "An element with this position does not exist\n";
		}
		else if (k == p - 1) {
			push_back(dat);
		}
		else if (p == 1) {
			push_front(dat);
		}
		else {
			List* hlp = List_beg;
			while (p != 2) {
				hlp = hlp->next;
				p--;
			}//сейчас hlp указывает на элемент после, которого вставится новый
			List* hlp2;
			hlp2 = new List(dat, hlp->next, hlp);
			hlp->next->last = hlp2;
			hlp->next = hlp2;
			hlp = NULL;
			hlp2 = NULL;
		}
		return;
	}
	void erase(int p) {//удаление элемента из позиции p(нумерация с 1)
		int k = size();
		if (k < p) {
			std::cout << "An element with this position does not exist\n";
		}
		else if (k == p) {
			pop_back();
		}
		else if (p == 1) {
			pop_front();
		}
		else {
			List* hlp = List_beg;
			while (p != 2) {
				hlp = hlp->next;
				p--;
			}//сейчас hlp указывает на элемент, который находится слева от удаляемого
			List* hlp2 = hlp->next;
			hlp2->next->last = hlp;
			hlp->next = hlp2->next;
			delete hlp2;
			hlp = NULL;
			hlp2 = NULL;
		}
		return;
	}
	int empty() {//проверка на пустоту
		if (List_beg != NULL) {
			return 0;
		}
		else {
			return 1;
		}
	}
	int size() {//текущее число элементов
		int size = 0;
		List* hlp = List_beg;
		while (hlp != NULL) {
			hlp = hlp->next;
			size++;
		}
		hlp = NULL;
		return size;
	}
	void print() {//функция вывода списка
		List* hlp = List_beg;
		while (hlp != NULL) {
			(*hlp).print_nexus();
			hlp = hlp->next;
		}
		std::cout << std::endl;
		return;
	}
};
int main() {
	Data d1("Roga_i_kopyta", 89999999999, 1);
	Data d2("Hell", 66666666666, 2);
	Data d3("Luck", 77777777777, 3);
	Data d4("Sber", 900, 4);
	Data d5("Durka", 007, 5);
	list l1(d2);
	l1.push_front(d1);
	l1.push_back(d3);
	l1.push_front(d4);
	if (l1.empty()) {
		std::cout << "size:" << l1.size() << " empty" << std::endl;
	}
	else {
		std::cout << "size:" << l1.size() << std::endl;
	}
	l1.push_front(d5);
	std::cout << "LIST IS FULL:" << std::endl << std::endl;
	l1.print();
	std::cout << "FIRST AND LAST ELEMENTS:" << std::endl << std::endl;
	(l1.front()).print_data();
	(l1.back()).print_data();
	std::cout << std ::endl << "DELETE NEXUS 1, 2, 5:" << std::endl << std::endl;
	l1.pop_back();
	l1.pop_front();
	if (l1.empty()) {
		std::cout << "size:" << l1.size() << " empty" << std::endl;
	}
	else {
		std::cout << "size:" << l1.size() << std::endl;
	}
	l1.pop_front();
	(l1.front()).print_data();
	(l1.back()).print_data();
	std::cout << std::endl  << "DELETE NEXUS 3, 4:" << std::endl << std::endl;
	l1.pop_back();
	l1.pop_back();
	if (l1.empty()){
		std::cout << "size:" << l1.size() << " empty" << std::endl;
	}
	else {
		std::cout << "size:" << l1.size() << std::endl;
	}
	std::cout << "FINISH" << std::endl << std::endl;
	l1.print();
	std::cout << "TEST ERASE AND INSERT" << std::endl << std::endl;
	l1.erase(1);
	l1.insert(2, d2);

	l1.insert(1, d3);
	l1.insert(2, d4);
	l1.insert(1, d1);
	l1.insert(2, d5);
	std::cout << "intermediate output" << std::endl << std::endl;
	l1.print();
	l1.erase(4);
	l1.erase(1);
	l1.print();
	l1.insert(2, d2);
	l1.print();
	l1.erase(1);
	l1.erase(1);
	l1.erase(1);
	if (l1.empty()) {
		std::cout << "Victory!" << std::endl;
	}
	else {
		std::cout << "error" << std::endl;
	}
	return 0;
}
