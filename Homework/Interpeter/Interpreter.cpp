#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>


using namespace std;

enum type_of_lex {
    LEX_NULL, /*0*/
    LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE, LEX_INT, /*8*/
    LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_TRUE, LEX_WHILE, LEX_WRITE, LEX_FOR, LEX_GOTO, LEX_BREAK, /*18*/
    LEX_STRING, /*19*/
    LEX_FIN, /*20*/
    LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_LFIG, LEX_RFIG, LEX_EQ, LEX_LSS, /*30*/
    LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, /*38*/
    LEX_PERCENT, /*39*/
    LEX_NUM, /*40*/
    LEX_STR,/*41*/
    LEX_ID, /*42*/
	POLIZ_LABEL,/*43*/
	POLIZ_ADDRESS,/*44*/
	POLIZ_GO,/*45*/
	POLIZ_FGO,/*46*/
    LEX_QUOTES, /*47*/
	UNARY_MINUS/*48*/
};

char* TRANSLATE[] = {    "NULL", /*0*/
    "AND", "BEGIN", "BOOL", "ELSE", "END", "IF", "FALSE", "INT", /*8*/
    "NOT", "OR", "PROGRAM", "READ", "TRUE", "WHILE", "WRITE", "FOR", "GOTO", "BREAK", /*18*/
    "STRING", /*19*/
    "FIN", /*20*/
    "SEMICOLON", "COMMA", "COLON", "ASSIGN", "LPAREN", "RPAREN", "LFIG", "RFIG", "EQ", "LSS", /*30*/
    "GTR", "PLUS", "MINUS", "TIMES", "SLASH", "LEQ", "NEQ", "GEQ", /*38*/
    "PERCENT", /*39*/
    "NUM", /*40*/
    "STR",/*41*/
    "ID", /*42*/
	"POLIZ_LABEL",/*43*/
	"POLIZ_ADDRESS",/*44*/
	"POLIZ_GO",/*45*/
	"POLIZ_FGO",/*46*/
    "QUOTES", /*47*/
	"UNARY_MINUS"/*48*/
};
class lex_val{
    int i_val;
	string s_val;
	bool b_val;
	int c_val;
public:

    lex_val(int i = 0, string s = "", bool b = true, int c = 0){
        i_val = i;
        s_val = s;
		b_val = b;
		c_val = c;
    }

    int get_i(){
        return i_val;
    }

    string get_s(){
        return s_val;
    }
	bool get_b(){
		return b_val;
	}
	int get_c(){
        return c_val;
    }
    void set_i(int i){
        i_val = i;
    }

    void set_s(string s){
        s_val.clear();
        s_val = s;
    }
	void set_b(bool b){
        b_val = b;
    }
	void set_c(int c){
        c_val = c;
    }
};

/////////////////////////  Lex  //////////////////////////

class Lex {
    type_of_lex t_lex;
    lex_val v_lex;
public:
    Lex(type_of_lex t = LEX_NULL, int i = 0, string s = "", bool b = false, int c = 0) : t_lex(t), v_lex(i, s, b, c) {}

    type_of_lex get_type() { return t_lex; }

    lex_val get_value() { return v_lex; }

    friend ostream &operator<<(ostream &s, Lex l) {
        if (l.t_lex == LEX_STR) {
            s << '(' << TRANSLATE[l.t_lex] << ',' << l.v_lex.get_s() << ");" << "\n";
        } else{
            s << '(' << TRANSLATE[l.t_lex] << ',' << l.v_lex.get_i() << ");" << "\n";
        }
        return s;
    }
};

/////////////////////  Ident  ////////////////////////////

class Ident {
    char *name;
    bool declare;
	bool mark;
    type_of_lex type;
    bool assign;
	int poliz_mark;
    lex_val value;
public:
    Ident() {
        declare = false;
        assign = false;
		mark = false;
    }

    char *get_name() { return name; }

    void put_name(const char *n) {
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    bool get_declare() { return declare; }

    void put_declare() { declare = true; }

    type_of_lex get_type() { return type; }

    void put_type(type_of_lex t) { type = t; }

    bool get_assign() { return assign; }

    void put_assign() { assign = true; }

    lex_val get_value() { return value; }

    void put_value(lex_val v) { value = v; }
	
	void set_mark(bool m) {mark = m; }
	
	bool get_mark() { return mark; }
	
	void set_poliz_mark (int n) {poliz_mark = n;} 

    int get_poliz_mark () {return poliz_mark;} 
};

//////////////////////  Tabl_ident  ///////////////////////

class Tabl_ident {
    Ident *p;
    int size;
    int top;
public:
    Tabl_ident(int max_size) {
        p = new Ident[size = max_size];
        top = 1;
    }

    ~Tabl_ident() { delete[] p; }

    Ident &operator[](int k) { return p[k]; }

    int put(const char *buf, bool mark);
	
	int get_top(){return top;}
	
};

int Tabl_ident::put(const char *buf, bool mark) {
    for (int j = 1; j < top; j++){
        if (!strcmp(buf, p[j].get_name())){
			if (mark){
				p[j].set_mark(mark);
				return j;
			}
			return j;
        }
	}
    p[top].put_name(buf);
	p[top].set_mark(mark);
    ++top;
    return top - 1;
}

////////////////////////////////////////////////////////////////////

Tabl_ident TID(100);
string TS[100];

/////////////////////  Scanner  //////////////////////////////

class Scanner {
    enum state {
        H, IDENT, NUMB, COM, ALE, DELIM, NEQ, STRING //5)assign less equal, 6)delimiter 
    };
    static char *TW[];
    static type_of_lex words[];
    static char *TD[];
    static type_of_lex dlms[];
    state CS;
    FILE *fp;
    char c;
    char buf[80];
    int buf_top;

    void clear() {
        buf_top = 0;
        for (int j = 0; j < 80; j++)
            buf[j] = '\0';
    }

    void add() {
        buf[buf_top++] = c;
    }

    int look(const char *buf, char **list) {
        int i = 0;
        while (list[i]) {
            if (!strcmp(buf, list[i]))
                return i;
            ++i;
        }
        return 0;
    }

    void gc() {
        c = fgetc(fp);
    }

public:
    Scanner(const char *program) {
        fp = fopen(program, "r");
        CS = H;
        clear();
        gc();
    }

    Lex get_lex();
	void analyze();
};

char *Scanner::TW[] = {"", "and", "begin", "bool", "else", "end", "if", "false", "int", "not", "or", "program",
                       "read", "true", "while", "write", "for", "goto", "break", "string", NULL};

type_of_lex Scanner::words[] = {LEX_NULL, LEX_AND, LEX_BEGIN, LEX_BOOL, LEX_ELSE, LEX_END, LEX_IF, LEX_FALSE,
                                LEX_INT,
                                LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ, LEX_TRUE, LEX_WHILE, LEX_WRITE,  LEX_FOR, LEX_GOTO, LEX_BREAK,
                                LEX_STRING, LEX_NULL};

char *Scanner::TD[] = {"", "@", ";", ",", ":", "=", "(", ")", "{", "}", "==", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", "%","\"",
                       NULL};

type_of_lex Scanner::dlms[] = {LEX_NULL, LEX_FIN, LEX_SEMICOLON, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_LPAREN, LEX_RPAREN, LEX_LFIG, LEX_RFIG,
                               LEX_EQ,
                               LEX_LSS, LEX_GTR, LEX_PLUS, LEX_MINUS, LEX_TIMES, LEX_SLASH, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_PERCENT, LEX_QUOTES,
                               LEX_NULL};

Lex Scanner::get_lex() {
    int d, j;
    CS = H;
	clear();
	
    do {
        switch (CS) {
            case H:
                if (c == ' ' || c == '\n' || c == '\r' || c == '\t')
                    gc();
                else if (c == '\"') {
                    clear();
                    gc();
                    add();
                    gc();
                    CS = STRING;
                }
                else if (isalpha(c)) {
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                } else if (isdigit(c)) {
                    d = c - '0';
                    gc();
                    CS = NUMB;
                } else if (c == '/') {
                    gc();
                    if (c == '*') {
                        CS = COM;
                        gc();
                    }
                    else{
                        return Lex(LEX_SLASH, 14);
                    }
                } else if (c == '=' || c == '<' || c == '>') {
                    clear();
                    add();
                    gc();
                    CS = ALE;
                } else if (c == EOF)
                    return Lex(LEX_FIN);
                else if (c == '!') {
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                } else
                    CS = DELIM;
                break;
            case IDENT:
                if (isalpha(c) || isdigit(c)) {
                    add();
                    gc();
                } else if (j = look(buf, TW)){
					if (words[j] == LEX_TRUE) {return Lex(words[j], 0, "", true, 2);}
					if (words[j] == LEX_FALSE) {return Lex(words[j], 0, "", false, 2);}
                    return Lex(words[j], j);
				}
                else if (c == ':'){
                    j = TID.put(buf, 1);
                    return Lex(LEX_ID, j);
                }
                else {
                    j = TID.put(buf, 0);
                    return Lex(LEX_ID, j);
                }
                break;
            case NUMB:
                if (isdigit(c)) {
                    d = d * 10 + (c - '0');
                    gc();
                } else
                    return Lex(LEX_NUM, d, "", true, 0);
                break;
            case COM:
                if (c == '*') {
                    gc();
                    if (c == '/'){
                        gc();
                        CS = H;
                    }
                } else if (c == EOF)
                    throw c;
                else
                    gc();
                break;
            case ALE:
                if (c == '=') {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                } else {
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                }
                break;
            case NEQ:
                if (c == '=') {
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(LEX_NEQ, j);
                } else
                    throw '!';
                break;
            case DELIM:
                clear();
                add();
                if (j = look(buf, TD)) {
                    gc();
                    return Lex(dlms[j], j);
                } else
                    throw c;
                break;
            case STRING:
                if (c != '\"' && c != EOF) {
                    add();
                    gc();
                } else if (c != '\"'){
                    throw "wrong string";
                /*} else if (j = look(buf, TW)) {
                    gc();
                    return Lex(words[j], j);*/
                } else {
                    gc();
                    return Lex(LEX_STR, 0, buf, true, 1);
                }
        }//end switch
    } while (true);
}

void Scanner::analyze(){
	Lex current_lex;
	current_lex = get_lex();
	while (current_lex.get_type() != LEX_FIN){
		cout << current_lex;
		current_lex = get_lex();
	}
	cout << current_lex;
	cout << endl << "analyze complete" << endl;
	return;
}

//lexical analisys done

template<class T, int max_size>
class Stack {
    T s[max_size];
    int top;
public:
    Stack() { top = 0; }

    void reset() { top = 0; }

    void push(T i);

    T pop();
	
    bool is_empty() { return top == 0; }

    bool is_full() { return top == max_size; }
};

template<class T, int max_size>
void Stack<T, max_size>::push(T i) {
    if (!is_full())
        s[top++] = i;
    else
        throw "Stack_is_full";
}

template<class T, int max_size>
T Stack<T, max_size>::pop() {
    if (!is_empty())
        return s[--top];
    else
        throw "stack_is_empty";
}

/////////////////////////  Poliz  /////////////////////////////

class Poliz {
    Lex *p;
    int size;
    int free;
public:
    Poliz(int max_size) {
        p = new Lex[size = max_size];
        free = 0;
    }

    ~Poliz() { delete[] p; }

    void put_lex(Lex l) {
        p[free] = l;
        free++;
    }

    void put_lex(Lex l, int place) { p[place] = l; }

    void blank() { free++; }

    int get_free() { return free; }

    Lex &operator[](int index) {
        if (index > size)
            throw "POLIZ:out of array";
        else if (index >= free)
            throw "POLIZ:indefinite element of array";
        else
            return p[index];
    }

    void print() {
        for (int i = 0; i < free; ++i)
            cout << i << ") "<< p[i];
    }
};
class Label {
	int ID;
	int POL;
public:
	Label(int id, int pol) : ID(id), POL(pol){}
	int get_ID() {return ID;}
	int get_POL() {return POL;}
	void set_ID(int id) { ID = id;}
	void set_POL(int pol) { POL = pol;}
};

class Parser {
    Lex curr_lex;
	int init_id;
    type_of_lex c_type;
	type_of_lex init;
    lex_val c_val;
    Scanner scan;
	bool assign;
	int in_cycle;
    Stack<int, 100> st_int;
    Stack<type_of_lex, 100> st_lex;
	int break_[100];
	int count_break[100];
	int run_break = 0;
	int top_break = 0;
	vector <Label> lab;
    void P();

    void D1();

    void D();

    void S();

    void V();

    void C();

    void CI();

    void E();
	
	void E0();

    void E1();

    void E2();

    void E3();

    void E4();

    void E5();

    void CI1();


    void dec(type_of_lex type);

    void check_id();

    void check_op();

    void check_not();
	
	void check_unary_minus();

    void eq_type();

    void eq_bool();

    void check_id_in_read();

    void gl() {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }

public:
    Poliz prog;
    Parser(const char *program) : scan(program), prog(1000) 
    {assign = true; in_cycle = 0;
		for (int i = 0; i < 100; i++){
			break_[i] = 0;
			count_break[i] = 0;
		}
	}

    void analyze();
};

void Parser::analyze() {
    gl();
    P();
    prog.print();
    cout << endl << "Poliz is ready!!!" << endl;
	cout << "-------------------------------------------------------" << endl;
}

void Parser::P() {
    if (c_type == LEX_PROGRAM)
        gl();
    else
        throw curr_lex;
    if (c_type == LEX_LFIG){
        gl();
    }
    else{
        throw curr_lex;
    }
    D();
    while (c_type != LEX_RFIG){
        S();
    }
	vector<Label>::iterator p = lab.begin();
	int id_, pol_;
	while (p != lab.end()){
		id_ = (*p).get_ID();
		pol_ = (*p).get_POL();
		if (!TID[id_].get_declare()){
			throw "undeclared label";
		}
		else {
			prog[pol_] = Lex(POLIZ_LABEL, TID[id_].get_poliz_mark());
		}
		++p;
	}
    gl();
    if (c_type != LEX_FIN)
        throw curr_lex;
}

void Parser::D() {
    while (c_type == LEX_INT || c_type == LEX_BOOL || c_type == LEX_STRING) {
		st_int.reset();
		init = c_type;
        gl();
        D1();
		if (init == LEX_STRING) init = LEX_STR;
        if (c_type == LEX_SEMICOLON){
			dec(init);
            gl();
        }
        else{
            throw curr_lex;
        }
    }
}

void Parser::D1() {
    if (c_type != LEX_ID)
        throw curr_lex;
    else {
        st_int.push(c_val.get_i());
	    init_id = c_val.get_i();
        gl();
        V();
        while (c_type == LEX_COMMA) {
            gl();
            if (c_type != LEX_ID)
                throw curr_lex;
            else {
                st_int.push(c_val.get_i());
			    init_id = c_val.get_i();
                gl();
                V();
            }
        }
    }
}

void Parser::V(){
    if (c_type == LEX_ASSIGN){
		TID[init_id].put_assign();
        gl();
        C();
    }
}

void Parser::C(){
    if (c_type == LEX_STR){
		if (init == LEX_STRING){
			TID[init_id].put_value(lex_val(0, c_val.get_s(), true, 1));
			gl();
		}
		else {
			throw "type of constant and variable are different";
		}
    }
    else if (c_type == LEX_TRUE){
		if (init == LEX_BOOL){	
			TID[init_id].put_value(lex_val(0, "", true, 2));
			gl();
		}
		else {
			throw "type of constant and variable are different";
		}
	}
	else if (c_type == LEX_FALSE){
		if (init == LEX_BOOL){	
			TID[init_id].put_value(lex_val(0, "", false, 2));
			gl();
		}
		else {
			throw "type of constant and variable are different";
		}
    }
    else{
        CI();
    }
}

void Parser::CI(){
    if (c_type == LEX_PLUS){
        gl();
		if (c_type == LEX_NUM){
			if (init == LEX_INT){	
				TID[init_id].put_value(lex_val(c_val.get_i(), "", true, 0));
				gl();
			}
		}
		else {
			throw "type of constant and variable are different";
		}
    }
	else if (c_type == LEX_NUM){
		if (init == LEX_INT){	
			TID[init_id].put_value(lex_val(c_val.get_i(), "", true, 0));
			gl();
		}
		else {
			throw "type of constant and variable are different";
		}
    }
	else if (c_type == LEX_MINUS){
        gl();
		if (c_type == LEX_NUM){
			if (init == LEX_INT){
				TID[init_id].put_value(lex_val(-(c_val.get_i()), "", true, 0));
				gl();
			}
			else {
				throw "type of constant and variable are different";
			}
		}
    }
    else{
        throw curr_lex;
    }
}


void Parser::S() {
	int rub;
    int pl0, pl1, pl2, pl3;
    //if (!E) goto pl2; S1 goto l3; pl2: S2; pl3:
    if (c_type == LEX_IF) {
        gl();
        if (c_type != LEX_LPAREN){
            throw curr_lex;
        }
        gl();
        E();
		eq_bool();
		pl2 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        if (c_type != LEX_RPAREN){
            throw curr_lex;
        }
        gl();
        S();
        pl3 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
        if (c_type == LEX_ELSE) {
            gl();
            S();
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl3);
        } else
            throw curr_lex;
    }
        // pl0: if (!E) goto pl1; S; goto pl0; pl1:
    else if (c_type == LEX_WHILE) {
		++in_cycle;
		++run_break;
        gl();
        pl0 = prog.get_free();
        if (c_type != LEX_LPAREN){
            throw curr_lex;
        }
        gl();
        E();
		eq_bool();
        if (c_type != LEX_RPAREN){
            throw curr_lex;
        }
        gl();
        pl1 = prog.get_free();
        prog.blank();
        prog.put_lex(Lex(POLIZ_FGO));
        S();
        prog.put_lex(Lex(POLIZ_LABEL, pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
		
		for (int i = 0; i < count_break[run_break]; i++){
			prog[break_[top_break - 1]] = Lex(POLIZ_LABEL, prog.get_free());
			top_break--;
		}
		count_break[run_break] = 0;
		--run_break;
		--in_cycle;
    }//end while1

    // for({E};{E};{E}) S
    // E ; pl0 E pl1 !F pl2 ! pl3 E ; pl0 ! pl2 S pl3 ! pl1
    else if (c_type == LEX_FOR) {
		++in_cycle;
		++run_break;
        gl();
        if (c_type != LEX_LPAREN){
            throw curr_lex;
        }
        gl();
        if (c_type != LEX_SEMICOLON){
            E();
			rub = st_lex.pop();
            prog.put_lex(Lex(c_type));			
        }
        if (c_type != LEX_SEMICOLON){
            throw curr_lex;
        }
        gl();
		pl0 = prog.get_free();
        if (c_type != LEX_SEMICOLON){
            E();
			eq_bool();
        }
		pl1 = prog.get_free();
		prog.blank();
		prog.put_lex(Lex(POLIZ_FGO));
		
	    pl2 = prog.get_free();
		prog.blank();
		prog.put_lex(Lex(POLIZ_GO));
        if (c_type != LEX_SEMICOLON){
            throw curr_lex;
        }
        gl();
		pl3 = prog.get_free();
        if (c_type != LEX_RPAREN){
            E();
			prog.put_lex(Lex(LEX_SEMICOLON));
			rub = st_lex.pop();
        }
        if (c_type != LEX_RPAREN){
            throw curr_lex;
        }
		prog.put_lex(Lex(POLIZ_LABEL, pl0));
        prog.put_lex(Lex(POLIZ_GO));
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl2);
        gl();
        S();
	    prog.put_lex(Lex(POLIZ_LABEL, pl3));
        prog.put_lex(Lex(POLIZ_GO));
		prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1);
		
		for (int i = 0; i < count_break[run_break]; i++){
		prog[break_[top_break - 1]] = Lex(POLIZ_LABEL, prog.get_free());
			top_break--;
		}
		count_break[run_break] = 0;
		--run_break;
		--in_cycle;
    } // end of for
///////////////////////////////////////////////////////////////////////////////////////////

    else if (c_type == LEX_READ) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
        } else
            throw curr_lex;
        if (c_type == LEX_ID) {
            check_id_in_read();
            prog.put_lex(Lex(POLIZ_ADDRESS, c_val.get_i()));
            gl();
        } else
            throw curr_lex;
        if (c_type == LEX_RPAREN) {
            gl();
            prog.put_lex(Lex(LEX_READ));
        } else
            throw curr_lex;
        if (c_type == LEX_SEMICOLON){
            gl();
        }
        else{
            throw curr_lex;
        }
    }//end read
    else if (c_type == LEX_WRITE) {
        gl();
        if (c_type == LEX_LPAREN) {
            gl();
        } else
            throw curr_lex;
        E();
		rub = st_lex.pop();
        while (c_type == LEX_COMMA) {
            gl();
            E();
			rub = st_lex.pop();
        }
        prog.put_lex(Lex(LEX_WRITE));		
        if (c_type == LEX_RPAREN){
            gl();
        }
        else
            throw curr_lex;
        if (c_type == LEX_SEMICOLON){
            gl();
        }
        else{
            throw curr_lex;
        }
    }//end write
    else if (c_type == LEX_BREAK){
		if (in_cycle > 0){
			break_[top_break] = prog.get_free();
			count_break[run_break]++;
			top_break++;
			prog.blank();
			prog.put_lex(Lex(POLIZ_GO));
			gl();
			if (c_type == LEX_SEMICOLON){
				gl();
			}
			else throw curr_lex;
		}
		else {
			throw "break not in cycle";
		}
    }
    else if (c_type == LEX_GOTO){
        gl();
		
        if (c_type == LEX_ID){
			lab.push_back (Label(c_val.get_i(), prog.get_free()));
			prog.blank();
			prog.put_lex(Lex(POLIZ_GO));
			if (TID[c_val.get_i()].get_mark()){
				gl();
            }
			else if (!TID[c_val.get_i()].get_declare()){
				TID[c_val.get_i()].set_mark(true);
				gl();
			}
			else {
				throw "error parametr goto";
			}
        }
        else {
            throw curr_lex;
        }
        if (c_type == LEX_SEMICOLON){
            gl();
        }
        else throw curr_lex;
    }
    else if (c_type == LEX_ID && !(TID[c_val.get_i()].get_declare())){//label
		TID[c_val.get_i()].put_declare();
		TID[c_val.get_i()].set_mark(true);
		TID[c_val.get_i()].set_poliz_mark(prog.get_free());
		gl();
		if (c_type == LEX_COLON){
            gl();
            S();
        }
		else {
			throw "the ID is not yet described";
		}
	}
	else if (c_type == LEX_ID && (TID[c_val.get_i()].get_declare())){// assign
		if (TID[c_val.get_i()].get_mark()){
			throw "the label already described";
		}
		check_id();
		prog.put_lex(Lex(POLIZ_ADDRESS, c_val.get_i()));
		gl();
        if (c_type == LEX_ASSIGN){
            gl();
            E();
			eq_type();
			prog.put_lex(Lex(LEX_ASSIGN));
            if (c_type == LEX_SEMICOLON){
				prog.put_lex(Lex(LEX_SEMICOLON));
                gl();
            }
            else{
                throw curr_lex;
            }
        }
        else{
            throw curr_lex;
        }
    }
    else if (c_type == LEX_LFIG){
        gl();
        while (c_type != LEX_RFIG){
            S();
        }
        gl();
    }
    else if (c_type == LEX_RFIG){}
    else{
        throw curr_lex;
    }
}
void Parser::E(){
	E0();
	if (c_type == LEX_ASSIGN){
		if (assign){
			st_lex.push(c_type);
			gl();
			E();
			check_op();
		}
		else {
			throw curr_lex;
		}
	}
	assign = true;
}
void Parser::E0() {
    E1();
    while (c_type == LEX_OR) {
        st_lex.push(c_type);
		assign = false;
        gl();
        E1();
        check_op();
    }
}

void Parser::E1(){
    E2();
    while (c_type == LEX_AND) {
        st_lex.push(c_type);
		assign = false;
        gl();
        E2();
        check_op();
    }
}

void Parser::E2(){
    E3();
    if (c_type == LEX_LSS || c_type == LEX_GTR || c_type == LEX_LEQ ||
            c_type == LEX_GEQ || c_type == LEX_NEQ || c_type == LEX_EQ) {
        st_lex.push(c_type);
		assign = false;
        gl();
        E3();
        check_op();
    }
}

void Parser::E3(){

    E4();
    while (c_type == LEX_PLUS || c_type == LEX_MINUS) {
        st_lex.push(c_type);
		assign = false;
        gl();
        E4();
        check_op();
    }
}

void Parser::E4(){

    E5();
    while (c_type == LEX_TIMES || c_type == LEX_SLASH) {
		assign = false;
        st_lex.push(c_type);
        gl();
        E5();
        check_op();
    }
}

void Parser::E5(){

    if (c_type == LEX_LPAREN){
		assign = false;
        gl();
        E();
        if (c_type != LEX_RPAREN){
            throw curr_lex;
        }
        else{
            gl();
        }
    }
    else if (c_type == LEX_NOT){
		assign = false;
        gl();
        E5();
		check_not();
    }
    else if (c_type == LEX_MINUS){
		assign = false;
        gl();
        E5();
		check_unary_minus();
    }
	else if (c_type == LEX_ID){
		check_id();
		int hlp_tid = c_val.get_i();
		gl();
		if (c_type == LEX_ASSIGN){
			prog.put_lex(Lex(POLIZ_ADDRESS, hlp_tid));
		}
		else {
			prog.put_lex(Lex(LEX_ID, hlp_tid));
		}
	}
    else if (c_type == LEX_TRUE){
		assign = false;
		st_lex.push(LEX_BOOL);
		prog.put_lex(curr_lex);
        gl();
    }
	else if (c_type == LEX_FALSE){
		assign = false;
		st_lex.push(LEX_BOOL);
		prog.put_lex(curr_lex);
        gl();
    }
	else if (c_type == LEX_STR){
		assign = false;
		st_lex.push(c_type);
		prog.put_lex(curr_lex);
        gl();
    }
    else{
		assign = false;
		st_lex.push(LEX_INT);
        CI1();
    }
}
void Parser::CI1(){
    if (c_type == LEX_PLUS){
        gl();
		prog.put_lex(curr_lex);
		if (c_type == LEX_NUM){
			gl();
		}
		else{
			throw curr_lex;
		}
	}
	else if (c_type == LEX_MINUS){
        gl();
		prog.put_lex(Lex(LEX_NUM, -(c_val.get_i()), "", true, 0));
		if (c_type == LEX_NUM){
			gl();
		}		
		else{
			throw curr_lex;
		}
	}
	else if (c_type == LEX_NUM){
		prog.put_lex(curr_lex);
		gl();
	}		
    else{
        throw curr_lex;
    }
}

////////////////////////////////////////////////////////////////

void Parser::dec(type_of_lex type) {
    int i;
    while (!st_int.is_empty()) {
        i = st_int.pop();
        if (TID[i].get_declare())
            throw "twice";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

void Parser::check_id() {
    if (TID[c_val.get_i()].get_declare() && !TID[c_val.get_i()].get_mark())
        st_lex.push(TID[c_val.get_i()].get_type());
    else
        throw "not declared";
}

void Parser::check_op() {
    type_of_lex t1, t2, op, t = LEX_INT, r = LEX_BOOL, s = LEX_STR;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    if (t1 == LEX_STR && t2 == LEX_STR){
        if (op == LEX_PLUS || op == LEX_ASSIGN){
			st_lex.push(s);
        }
		else if ( op == LEX_LSS || op == LEX_GTR || op == LEX_EQ || op == LEX_NEQ){
			st_lex.push(r);
		}
		else {
			throw "wrong operation for string";
		}
    } 
	else if (t1 == LEX_INT && t2 == LEX_INT){
        if (op == LEX_ASSIGN || op == LEX_PLUS || op == LEX_MINUS || op == LEX_TIMES || op == LEX_SLASH || op == LEX_PERCENT){
			st_lex.push(t);
		}
		else if (op == LEX_LSS || op == LEX_GTR || op == LEX_EQ || op == LEX_NEQ || op == LEX_LEQ || op == LEX_GEQ){
			st_lex.push(r);
		}
		else {
			throw "wrong operation for int";
		}
	}
	else if (t1 == LEX_BOOL && t2 == LEX_BOOL){
        if (op == LEX_ASSIGN || op == LEX_OR || op == LEX_AND){
            st_lex.push(r);
		}
        else
            throw "wrong operation for bool";
    }
	else {
		throw "wrong types are in operation";
	}
    prog.put_lex(Lex(op));
}

void Parser::check_not() {
    if (st_lex.pop() != LEX_BOOL)
        throw "wrong type is in not";
    else {
        st_lex.push(LEX_BOOL);
        prog.put_lex(Lex(LEX_NOT));
    }
}

void Parser::check_unary_minus() {
    if (st_lex.pop() != LEX_INT)
        throw "wrong type is in unary minus";
    else {
        st_lex.push(LEX_INT);
        prog.put_lex(Lex(UNARY_MINUS));
    }
}
void Parser::eq_type() {
    if (st_lex.pop() != st_lex.pop())
        throw "wrong types are in =";
}

void Parser::eq_bool() {
    if (st_lex.pop() != LEX_BOOL)
        throw "expression is not boolean";
}

void Parser::check_id_in_read() {
    if (!TID[c_val.get_i()].get_declare() || TID[c_val.get_i()].get_mark())
        throw "not declared";
}
////////////////////////////////////////////////////////////////
class Executer {
    Lex pc_el;
public:
    void execute(Poliz &prog);
};
void Executer::execute(Poliz &prog) {
    Stack<lex_val, 100> args;
	Stack<lex_val, 100> hlp;
    int index = 0, size = prog.get_free();
    lex_val i, j;
    while (index < size) {
        pc_el = prog[index];
        switch (pc_el.get_type()) {
            case LEX_TRUE:
            case LEX_FALSE:
            case LEX_NUM:
            case POLIZ_ADDRESS:
            case POLIZ_LABEL:
                args.push(pc_el.get_value());
                break;
            case LEX_STR:
                i = pc_el.get_value();
                args.push(i);
                break;
            case LEX_ID:
                i = pc_el.get_value();
                if (TID[i.get_i()].get_assign()) {
                    args.push(TID[i.get_i()].get_value());
                    break;
                } else
                    throw "POLIZ: indefinite identifier";
            case LEX_NOT:
                args.push(lex_val(0, "", !(args.pop().get_b()), 2));
                break;
			case UNARY_MINUS:
                args.push(lex_val(-(args.pop().get_i()), "", true, 0));
				break;
            case LEX_OR:
                i = args.pop();
                args.push(lex_val(0, "",(args.pop().get_b() || i.get_b()), 2));
                break;
            case LEX_AND:
                i = args.pop();
                args.push(lex_val(0, "",(args.pop().get_b() && i.get_b()), 2));
                break;
            case POLIZ_GO:
                index = args.pop().get_i() - 1;
                break;
            case POLIZ_FGO:
                i = args.pop();
                if (!args.pop().get_b()) index = i.get_i() - 1;
                break;
            case LEX_WRITE:
				while (!args.is_empty()){
					i = args.pop();
					hlp.push(i);
				}
				while (!hlp.is_empty()){
					i = hlp.pop();
					if (i.get_c() == 0){
						cout << i.get_i() << " ";
					} 
					else if (i.get_c() == 1){
						cout << i.get_s() << " ";
					}
					else {
						cout << boolalpha;
						cout << i.get_b() << " ";
					}
				}
				cout << endl;
                break;
            case LEX_READ: {
                int temp1;
				bool temp2;
				string temp3;
                lex_val k;
                i = args.pop();
                if (TID[i.get_i()].get_type() == LEX_INT) {
                    cout << "Input int value for " << TID[i.get_i()].get_name() << endl;
                    cin >> temp1;
                    k.set_i(temp1);
					k.set_c(0);
				} 
				else if (TID[i.get_i()].get_type() == LEX_BOOL){
					cout << "Input bool value for " << TID[i.get_i()].get_name() << endl;
                    cin >> temp2;
                    k.set_b(temp2);
					k.set_c(2);
                }
				else {
					cout << "Input string value for " << TID[i.get_i()].get_name() << endl;
                    cin >> temp3;
                    k.set_s(temp3);
					k.set_c(1);
				}
                TID[i.get_i()].put_value(k);
                TID[i.get_i()].put_assign();
                break;
            }
            case LEX_PLUS:
                i = args.pop();
                j = args.pop();
                if (i.get_s().empty() && j.get_s().empty()) {
                    args.push(lex_val((j.get_i() + i.get_i()), "", true, 0));
                } else {
                    args.push(lex_val(0, j.get_s().append(i.get_s()), true, 1));
                }
                break;
            case LEX_TIMES:
                args.push(lex_val((args.pop().get_i() * args.pop().get_i()), "", true, 0));
                break;
            case LEX_MINUS:
                i = args.pop();
                args.push(lex_val((args.pop().get_i() - i.get_i()), "", true, 0));
                break;
            case LEX_SLASH:
                i = args.pop();
                if (i.get_i()) {
                    args.push(lex_val((args.pop().get_i() / i.get_i()), "", true, 0));
                    break;
                } else
                    throw "POLIZ:divide by zero";
            case LEX_PERCENT:
                i = args.pop();
                if (i.get_i()){
                    args.push(lex_val((args.pop().get_i() % i.get_i()), "", true, 0));
                    break;
                } else
                    throw "POLIZ:divide by zero";
            case LEX_EQ:
				i = args.pop();
				j = args.pop();
				if (i.get_c() == 0){
					args.push(lex_val(0, "", (j.get_i() == i.get_i()), 2));
				}
				else {
					args.push(lex_val(0,  "",(j.get_s() == i.get_s()), 2));
				}
                break;
            case LEX_LSS:
				i = args.pop();
				j = args.pop();
				if (i.get_c() == 0){
					args.push(lex_val(0, "", (j.get_i() < i.get_i()), 2));
				}
				else {
					args.push(lex_val(0,  "",(j.get_s() < i.get_s()), 2));
				}
                break;
            case LEX_GTR:
				i = args.pop();
				j = args.pop();
				if (i.get_c() == 0){
					args.push(lex_val(0, "", (j.get_i() > i.get_i()), 2));
				}
				else {
					args.push(lex_val(0,  "",(j.get_s() > i.get_s()), 2));
				}
                break;
            case LEX_LEQ:
                i = args.pop();
				j = args.pop();
                args.push(lex_val(0,  "",(j.get_i() <= i.get_i()), 2));
                break;
            case LEX_GEQ:
                i = args.pop();
				j = args.pop();
                args.push(lex_val(0,  "",(j.get_i() >= i.get_i()), 2));
                break;
            case LEX_NEQ:
				i = args.pop();
				j = args.pop();
				if (i.get_c() == 0){
					args.push(lex_val(0, "", (j.get_i() != i.get_i()), 2));
				}
				else {
					args.push(lex_val(0,  "",(j.get_s() != i.get_s()), 2));
				}
                break;
            case LEX_ASSIGN:
                i = args.pop();
                j = args.pop();
                TID[j.get_i()].put_value(i);
                TID[j.get_i()].put_assign();
				args.push(i);
                break;
			case LEX_SEMICOLON:
				i = args.pop();
				break;
            default:
                throw "POLIZ: unexpected elem";
        }//end of switch
        ++index;
    };//end of while
    cout << "Finish of executing!!!" << endl;
}

class Interpretator {
    Parser pars;
	Executer E;
public:
    Interpretator(char *program) : pars(program) {}

    void interpretation();
};

void Interpretator::interpretation() {
    pars.analyze();
	E.execute(pars.prog);
}

int main() {
    try {
        Interpretator I("break_inside_loop.txt");
        I.interpretation();
        return 0;
    }
    catch (char c) {
        cout << "unexpected symbol " << c << endl;
        return 1;
    }
    catch (Lex l) {
        cout << "unexpected lexeme";
        cout << l;
        return 1;
    }
	catch (const char* source){
		cout << source << endl;
		return 1;
	}
}
