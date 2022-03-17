#include <iostream>
#include <cstring>

struct List {//список данных
	int a;//данные
	struct List* next;
	struct List* last;
};
void copy_List(List* from, List* to) {//функция копирования списка
	while (from->next != NULL) {//циклом проходим весь список и копируем его
		from = from->next;
		to->next = new List;
		to->next->a = from->a;
		to->next->next = NULL;
		to->next->last = to;
		to = to->next;
	}
}
void del_List(List* _list) {//функция очистки списка
	List* hlp;
	while (_list != NULL) {
		hlp = _list->next;
		delete _list;
		_list = hlp;
	}
}
class list {
	List* List_;
public:
	list() {//конструктор по умолчанию
		List_ = NULL;
		//std::cout << "\nThe default constructor worked successfully\n";
	}
	list(int a) {//конструктор
		List_ = new List;
		List_->a = a;
		List_->next = NULL;
		List_->last = NULL;
		//std::cout << "\nThe constructor worked successfully\n";
	}
	list (const list & _list_) {
		if (_list_.List_ != NULL) {//создание 1-го с звена
			List_ = new List;
			List_->a = _list_.List_->a;
			List_->last = NULL;
			List_->next = NULL;
			if (_list_.List_->next != NULL) {//копирование остальных звеньев
				copy_List(_list_.List_, List_);
			}
		}
		else {//если список пуст
			List_ = NULL;
		}
		//std::cout << "\nThe costructor copy worked successfully\n";
	}
	list & operator = (const list & _list_) {
		if (this == &_list_) {
			return *this;
		}
		del_List(List_);//очищаем список
		List_ = NULL;
		if (_list_.List_ != NULL) {//создание 1-го с звена
			List_ = new List;
			List_->a = _list_.List_->a;
			List_->last = NULL;
			List_->next = NULL;
			if (_list_.List_->next != NULL) {//копирование остальных звеньев
				copy_List(_list_.List_, List_);
			}
		}
		else {//если список пуст
			List_ = NULL;
		}
		//std::cout << "\nThe operator = worked successfully\n";
		return *this;
	}
	~list() {//деструктор
		del_List(List_);
		List_ = NULL;
		//std::cout << "\nThe destructor worked successfully\n";
	}
	void push_front(int a) {// функция добавления элемента в начало
		if (List_ != NULL) {
			List* hlp;
			hlp = new List;
			hlp->a = a;
			hlp->last = NULL;
			hlp->next = List_;
			List_->last = hlp;
			List_ = hlp;
			hlp = NULL;
		}
		else {
			List_ = new List;
			List_->a = a;
			List_->last = NULL;
			List_->next = NULL;
		}
		return;
	}
	void push_back(int a) {// функция добавления элемента в конец
		if (List_ != NULL) {
			List* hlp = List_;
			while (hlp->next != NULL) {
				hlp = hlp->next;
			}
			hlp->next = new List;
			hlp->next->a = a;
			hlp->next->last = hlp;
			hlp->next->next = NULL;
			hlp = NULL;
		}
		else {
			List_ = new List;
			List_->a = a;
			List_->last = NULL;
			List_->next = NULL;
		}
		return;
	}
	int front() {//чтение первого элемента списка
		if (List_ != NULL) {
			return List_->a;
		}
		else {
			std::cout << "The List is empty\n";
		}
		return 0;
	}
	int back() {//чтение последнего элемента списка 
		if (List_ != NULL) {
			int a;
			List* hlp = List_;
			while (hlp->next != NULL) {
				hlp = hlp->next;
			}
			a = hlp->a;
			hlp = NULL;
			return a;
		}
		else {
			std::cout << "The List is empty\n";
		}
		return 0;
	}
	void pop_front() {//удаление первого элемента списка
		if (List_ != NULL) {
			if (List_->next == NULL) {
				delete List_;
				List_ = NULL;
			}
			else {
				List* hlp = List_->next;
				hlp->last = NULL;
				delete List_;
				List_ = hlp;
				hlp = NULL;
			}
		}
		return;
	}
	void pop_back() {//удаление последнего элемента списка
		if (List_ != NULL) {
			if (List_->next == NULL) {
				delete List_;
				List_ = NULL;
			}
			else {
				List* hlp = List_->next;
				while (hlp->next != NULL) {
					hlp = hlp->next;
				}
				hlp->last->next = NULL;
				delete hlp;
				hlp = NULL;
			}
		}
		return;
	}
	void insert(int p, int x) {//добавление элемента x перед позицией p(нумерация с 1)
		int k = size();
		if (k < p - 1) {
			std::cout << "An element with this position does not exist\n";
		}
		else if (k == p - 1) {
			push_back(x);
		}
		else if (p == 1) {
			push_front(x);
		}
		else {
			List* hlp = List_;
			while (p != 2) {
				hlp = hlp->next;
				p--;
			}//сейчас hlp указывает на элемент после, которого вставится новый
			List* hlp2;
			hlp2 = new List;
			hlp2->a = x;
			hlp2->last = hlp;
			hlp2->next = hlp->next;
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
			List* hlp = List_;
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
		if (List_ != NULL) {
			return 0;
		}
		else {
			return 1;
		}
	}
	int size(){//текущее число элементов
		int size = 0;
		List* hlp = List_;
		while (hlp != NULL) {
			hlp = hlp->next;
			size++;
		}
		hlp = NULL;
		return size;
	}
	void print() {//функция вывода списка
		List* hlp = List_;
		while (hlp != NULL) {
			std::cout << hlp->a << " ";
			hlp = hlp->next;
		}
		std::cout << std::endl;
		return;
	}
};
int main() {
	list l1(3);
	list l2;
	l2.push_back(2);
	l2.push_front(1);
	l2.push_back(3);
	l1.push_front(2);
	l1.push_back(4);
	l1.push_back(5);
	l1.push_front(1);
	l1.print();
	l2.print();
	if (l1.empty()) {
		std::cout << "l1 is empty\n";
	}
	else {
		std::cout << "l1 is not empty\n";
	}
	if (l2.empty()) {
		std::cout << "l2 is empty\n";
	}
	else {
		std::cout << "l2 is not empty\n";
	}
	std::cout << "back l1 = " << l1.back() << std::endl;
	std::cout << "front l1 = " << l1.front() << std::endl;
	std::cout << "size l1 = " << l1.size() << std::endl;
	std::cout << "back l2 = " << l2.back() << std::endl;
	std::cout << "front l2 = " << l2.front() << std::endl;
	std::cout << "size l2 = " << l2.size() << std::endl;
	list l3(l1);
	list l4;
	l4 = l2;
	//работа с l1  и l2
	l1.pop_back();
	l1.pop_front();
	l2.pop_back();
	l2.pop_front();
	l1.print();
	l2.print();
	if (l1.empty()) {
		std::cout << "l1 is empty\n";
	}
	else {
		std::cout << "l1 is not empty\n";
	}
	std::cout << "back l1 = " << l1.back() << std::endl;
	std::cout << "front l1 = " << l1.front() << std::endl;
	std::cout << "size l1 = " << l1.size() << std::endl;
	std::cout << "back l2 = " << l2.back() << std::endl;
	std::cout << "front l2 = " << l2.front() << std::endl;
	std::cout << "size l2 = " << l2.size() << std::endl;
	l2.pop_back();
	l2.pop_front();
	l2.print();
	std::cout << "back l2 = " << l2.back() << std::endl;
	std::cout << "front l2 = " << l2.front() << std::endl;
	std::cout << "size l2 = " << l2.size() << std::endl;
	if (l2.empty()) {
		std::cout << "l2 is empty\n";
	}
	else {
		std::cout << "l2 is not empty\n";
	}
	// работа с l3 и l4
	l3.print();
	l4.print();
	l4.insert(1, 10);
	l4.insert(7, 10);
	l4.insert(3, 100);
	l4.insert(5, 1000);
	l4.insert(7, 10000);
	l4.print();
	l4.erase(2);
	l4.erase(5);
	l4.print();

	l3.erase(6);
	l3.erase(1);
	l3.erase(4);
	l3.print();
	l3.erase(2);
	std::cout << "back l3 = " << l3.back() << std::endl;
	std::cout << "front l3 = " << l3.front() << std::endl;
	std::cout << "size l3 = " << l3.size() << std::endl;
	l3.erase(2);
	l3.erase(1);
	if (l3.empty()) {
		std::cout << "l3 is empty\n";
	}
	else {
		std::cout << "l3 is not empty\n";
	}
	return 0;
}
