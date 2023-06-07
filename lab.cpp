#include "lab.h"

//Игнорирование ранее введенной строки
void ignore() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Определение приоритета операций
int priority(const char &c) {
	switch (c) {
	case '+': 
	case '-': 
		return 1;
	case '*': 
	case '/': 
		return 2;
	}
	return 100;
}

// Построение дерева
nodePtr make(const string exp, int first, int last){
	if (exp[first] == '(' && exp[first+1] == ')'){
		system("cls");
		cout << "Ошибка! Пустые скобки (). " << endl;
		return 0;
	}
	int temp = 100, k = 0, prt = 0, nest = 0; 
	for (int i = first; i <= last; i++) {
		if (exp[i] == '('){
			nest++; 
			continue;
		}
		if (exp[i] == ')'){
			nest--; 
			continue;
		}
		if (nest > 0) continue; 
		prt = priority(exp[i]);
		if (prt <= temp) {
			temp = prt;
			k = i;
		}
	}
	if (nest) {
		system("cls");
		cout << "Ошибка! Нечетное количество скобок. " << endl;
		return 0;
	}
	if (temp == 100)
		if (exp[first] == '(' && exp[last] == ')') return make(exp, first + 1, last - 1);
		else { 
			k = last - first + 1;
			return new Node{ exp.substr(first, k), 0, 0 };
		}
	string op(1, exp[k]); // string конструктор
	if (op == "/") {
		nodePtr left = make(exp, first, k - 1);
		nodePtr right = make(exp, k + 1, last);
		if (right->data == "0") {
			system("cls");
			cout << "Ошибка! Деление на ноль." << endl;
			return 0;
		}
		return new Node{ op, left, right };
	}
	return new Node{ op , make(exp, first, k - 1), make(exp, k + 1, last) };
}

//Вычисление выражения
double calculate(nodePtr root){ // double только для деления
	if (!root->left) {
		int i;
		istringstream(root->data) >> i;
		return i;
	}
	double num1 = calculate(root->left);
	double num2 = calculate(root->right);
	if (root->data == "+") return num1 + num2;
	else if (root->data == "-") return num1 - num2;
	else if (root->data == "*") return num1 * num2;
	else if (root->data == "/") return num1 / num2;
}

//Вывод дерева
void showData(nodePtr root) {
	if (!root) return;
	showData(root->right);
	cout << endl << root->data << " " << endl << "Текущий адрес" << root << endl << "Адрес левого сына: " << root->left << endl << "Адрес правого сына: " << root->right << endl;
	showData(root->left);
}

//Определение количества узлов
void count(nodePtr root, int& n) {
	if (root) {
		n++;
		count(root->left, n);
		count(root->right, n);
	}
}

//Определение высоты дерева
int height(nodePtr root) {
	if (!root) return 0;
	return 1 + max(height(root->left), height(root->right));
}

//Освобождение памяти, выделенной для дерева
nodePtr freeList(nodePtr& root) {
	if (root) {
		freeList(root->left);
		freeList(root->right);
		delete root;
	}
	return 0;
}

//Перевод выражения из инфиксной формы в префиксную
string infixToPrefix(nodePtr root) {
	if (!root->left && !root->right) return root->data;
	string left = infixToPrefix(root->left);
	string right = infixToPrefix(root->right);
	return root->data + " " + left + " " + right;
}

//Перевод выражения из инфоксной формы в постфиксную
string infixToPostfix(nodePtr root) {
	if (!root->left && !root->right) return root->data;
	string left = infixToPostfix(root->left);
	string right = infixToPostfix(root->right);
	return left + " " + right + " " + root->data;
}

//Проверка введенного выражения
bool check( const string str) {
	int countOp = 0;
	int countNum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')') return true; //Проверка на содержание
		if (str[i]=='-' || str[i]=='+' || str[i]=='*' || str[i]=='/' || str[i]=='(' || str[i]==')') countOp++; //количество операторов
		if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/')) return true;
	}
	if (countOp==str.length()) return true; // проверка на ----, 2, -5
	return false;
}
