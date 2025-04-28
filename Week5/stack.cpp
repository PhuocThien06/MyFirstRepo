#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Stack {
	NODE* top;
};
Stack* initializeStack();
void push(Stack& s, int key);
int pop(Stack& s);
bool isEmpty(Stack s);
int size(Stack s);
void printStack(Stack s, ostream& out);
void clearStack(Stack& s);


Stack* initializeStack() {
	Stack* s = new Stack;
	s->top = nullptr;
	return s;
}
void push(Stack& s, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = s.top;
	s.top = newNode;
}
int pop(Stack& s) {
	if (s.top == nullptr) {
		return -1;
	}
	int key = s.top->key;
	NODE* temp = s.top;
	s.top = s.top->p_next;
	delete temp;
	return key;
}
int size(Stack s) {
	int count = 0;
	NODE* cur = s.top;
	while (cur != nullptr) {
		count++;
		cur = cur->p_next;
	}
	return count;
}
bool isEmpty(Stack s) {
	return s.top == nullptr;
}

void printStack(Stack s, ostream& out) {
	if (s.top == nullptr) {
		out << "EMPTY\n";
		return;
	}
	Stack temp;
	temp.top = nullptr;
	while (s.top != nullptr) {
		NODE* newNode = new NODE;
		newNode->key = s.top->key;
		newNode->p_next = temp.top;
		temp.top = newNode;
		s.top = s.top->p_next;
	}
	NODE* cur = temp.top;
	while (cur != nullptr) {
		out << cur->key;
		if (cur->p_next != nullptr)
			out << " ";
		cur = cur->p_next;
	}
	out << "\n";
	while (temp.top != nullptr) {
		NODE* tempNode = temp.top;
		temp.top = temp.top->p_next;
		delete tempNode;
	}
}

void clearStack(Stack& s) {
	while (s.top != nullptr) {
		NODE* temp = s.top;
		s.top = s.top->p_next;
		delete temp;
	}
}
int main() {
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	char line[200];
	Stack* s = initializeStack();
	while (inFile.getline(line, sizeof(line))) {
		if (strlen(line) == 0) continue;
		int index = 0;
		char* context = nullptr;
		while (line[index] == ' ') index++;
		char temp[200];
		strcpy_s(temp,sizeof(temp), line + index);
		char* kitu = strtok_s(temp, " ",&context);
		if (kitu == nullptr) continue;
		if (strcmp(kitu, "init") == 0) {
			printStack(*s, outFile);
		}
		else if (strcmp(kitu, "push") == 0) {
			kitu = strtok_s(nullptr, " ",&context);
			if (kitu != nullptr) {
				int key = atoi(kitu);
				push(*s, key);
			}
			printStack(*s, outFile);
		}
		else if (strcmp(kitu, "pop") == 0) {
			if (!isEmpty(*s)) {
				pop(*s);
			}
			printStack(*s, outFile);
		}
	}
	inFile.close();
	outFile.close();
	clearStack(*s);
	delete s;
	return 0;
}
