#include "lab.h"

//������������� ����� ��������� ������
void ignore() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//����������� ���������� ��������
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

// ���������� ������
nodePtr make(const string exp, int first, int last){
	if (exp[first] == '(' && exp[first+1] == ')'){
		system("cls");
		cout << "������! ������ ������ (). " << endl;
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
		cout << "������! �������� ���������� ������. " << endl;
		return 0;
	}
	if (temp == 100)
		if (exp[first] == '(' && exp[last] == ')') return make(exp, first + 1, last - 1);
		else { 
			k = last - first + 1;
			return new Node{ exp.substr(first, k), 0, 0 };
		}
	string op(1, exp[k]); // string �����������
	if (op == "/") {
		nodePtr left = make(exp, first, k - 1);
		nodePtr right = make(exp, k + 1, last);
		if (right->data == "0") {
			system("cls");
			cout << "������! ������� �� ����." << endl;
			return 0;
		}
		return new Node{ op, left, right };
	}
	return new Node{ op , make(exp, first, k - 1), make(exp, k + 1, last) };
}

//���������� ���������
double calculate(nodePtr root){ // double ������ ��� �������
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

//����� ������
void showData(nodePtr root) {
	if (!root) return;
	showData(root->right);
	cout << endl << root->data << " " << endl << "������� �����" << root << endl << "����� ������ ����: " << root->left << endl << "����� ������� ����: " << root->right << endl;
	showData(root->left);
}

//����������� ���������� �����
void count(nodePtr root, int& n) {
	if (root) {
		n++;
		count(root->left, n);
		count(root->right, n);
	}
}

//����������� ������ ������
int height(nodePtr root) {
	if (!root) return 0;
	return 1 + max(height(root->left), height(root->right));
}

//������������ ������, ���������� ��� ������
nodePtr freeList(nodePtr& root) {
	if (root) {
		freeList(root->left);
		freeList(root->right);
		delete root;
	}
	return 0;
}

//������� ��������� �� ��������� ����� � ����������
string infixToPrefix(nodePtr root) {
	if (!root->left && !root->right) return root->data;
	string left = infixToPrefix(root->left);
	string right = infixToPrefix(root->right);
	return root->data + " " + left + " " + right;
}

//������� ��������� �� ��������� ����� � �����������
string infixToPostfix(nodePtr root) {
	if (!root->left && !root->right) return root->data;
	string left = infixToPostfix(root->left);
	string right = infixToPostfix(root->right);
	return left + " " + right + " " + root->data;
}

//�������� ���������� ���������
bool check( const string str) {
	int countOp = 0;
	int countNum = 0;
	for (int i = 0; i < str.length(); i++) {
		if (!isdigit(str[i]) && str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != '/' && str[i] != '(' && str[i] != ')') return true; //�������� �� ����������
		if (str[i]=='-' || str[i]=='+' || str[i]=='*' || str[i]=='/' || str[i]=='(' || str[i]==')') countOp++; //���������� ����������
		if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && (str[i+1] == '+' || str[i+1] == '-' || str[i+1] == '*' || str[i+1] == '/')) return true;
	}
	if (countOp==str.length()) return true; // �������� �� ----, 2, -5
	return false;
}
