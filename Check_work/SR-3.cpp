#include <iostream>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <list>
#include <iterator>
#include <list>

using namespace std;

template <typename S>

void print_cont(const S& cont) {
	typename S::const_iterator itr;
	for (itr = cont.begin(); itr != cont.end(); itr++) {
		cout << *itr << " ";
	}
	std::cout << std::endl;

	typename S::const_reverse_iterator it;
	for (it = cont.rbegin(); it != cont.rend(); it++) {
		cout << *it << " ";
	}
	std::cout << std::endl;
}

template <typename VEC, typename LST>

void _insert_(VEC & vec, const LST & lst) {
	int count_it_vec = 0;
	typename LST::const_iterator itl = lst.begin();
	for (;(itl != lst.end()) && (count_it_vec < vec.size());) {
		typename VEC::iterator itv = vec.begin();
		advance(itv, count_it_vec);
		itv++;
		vec.emplace(itv, *itl);
		count_it_vec += 3;
		itl++;
		if (itl == lst.end()){
			break;
		}
		itl++;
	}
}
template <typename Even>

void _double1_(vector <Even> & vec) {
	int count_it_vec = 0;
	Even hlp;
	for (;count_it_vec < vec.size();) {
		typename::vector<char>::iterator itv = vec.begin();
		advance(itv, count_it_vec);
		hlp = *itv;
		itv++;
		vec.emplace(itv, hlp);
		count_it_vec += 3;
	}
}

template <typename Even2>

void _double2_(list <Even2> & lst) {
	int count_it_lst = 1;
	Even2 hlp;
	for (; count_it_lst < lst.size();) {
		typename::list<Even2>::iterator itl = lst.begin();
		advance(itl, count_it_lst);
		hlp = *itl;
		itl++;
		lst.insert(itl, hlp);
		count_it_lst += 3;
	}
}

int main() {
	std::cout << "tasks 1-2"<< std::endl;
	std::vector <int> vect1 = { 3, 2, 4, 1, 5 };
	const std::vector <char> vect2 = { 'a', 'b', 'c', 'd', 'e' };
	std::vector <char> vect3 = { 'a', 'b', 'c', 'd', 'e' };
	list <int> lst1 = { 5, 6, 9, 3, 2, 7 };
	list <int> lst2 = { 9, 8, 7, 6 };
	print_cont(vect1);
	std::cout << std::endl;
	print_cont(vect2);
	std::cout << std::endl;
	print_cont(lst1);
	std::cout << "task 3" << std::endl;
	_insert_(vect1, lst1);
	print_cont(vect1);
	std::cout << std::endl;
	_insert_(vect1, lst2);
	print_cont(vect1);
	std::cout << "task4" << std::endl;
	print_cont(vect3);
	_double1_(vect3);
	print_cont(vect3);
	std::cout << std::endl;
	print_cont(lst1);
	_double2_(lst1);
	print_cont(lst1);
	return 0;
}