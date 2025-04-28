#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct Queue {
	NODE* head;
	NODE* tail;
};
Queue* initializeQueue();
void enqueue(Queue& q, int key);
int dequeue(Queue& q);
int size(Queue q);
bool isEmpty(Queue q);
void printQueue(Queue q, ostream& out);
void clearQueue(Queue& q);


Queue* initializeQueue() {
	Queue* q = new Queue;
	q->head = nullptr;
	q->tail = nullptr;
	return q;
}
void enqueue(Queue& q, int key) {
	NODE* newNode = new NODE;
	newNode->key = key;
	newNode->p_next = nullptr;
	if (q.tail == nullptr) {
		q.head = q.tail = newNode;
	}
	else {
		q.tail->p_next = newNode;
		q.tail = newNode;
	}
}
int dequeue(Queue& q) {
	if (q.head == nullptr) {
		return -1;
	}
	int key = q.head->key;
	NODE* temp = q.head;
	q.head = q.head->p_next;
	if (q.head == nullptr) { 
		q.tail = nullptr;
	}
	delete temp;
	return key;
}
int size(Queue q){
	int count = 0;
	NODE* cur = q.head;
	while (cur != nullptr) {
		count++;
		cur = cur->p_next;
	}
	return count;
}
bool isEmpty(Queue q) {
	return q.head == nullptr;
}
void printQueue(Queue q, ostream& out) {
	if (q.head == nullptr) {
		out << "EMPTY\n";
		return;
	}
	NODE* cur = q.head;
	while (cur != nullptr) {
		out << cur->key;
		if (cur->p_next != nullptr)
			out << " ";
		cur = cur->p_next;
	}
	out << "\n";
}
void clearQueue(Queue& q) {
	while (q.head != nullptr) {
		NODE* temp = q.head;
		q.head = q.head->p_next;
		delete temp;
	}
	q.tail = nullptr;
}
int main() {
	ifstream inFile("input.txt");
	ofstream outFile("output.txt");
	char line[200];
	Queue* q = initializeQueue();
	while (inFile.getline(line, sizeof(line))) {
		if (strlen(line) == 0) continue;
		int index = 0;
		char* context = nullptr;
		while (line[index] == ' ') index++;
		char temp[200];
		strcpy_s(temp, sizeof(temp), line + index);
		char* kitu = strtok_s(temp, " ", &context);
		if (kitu == nullptr) continue;
		if (strcmp(kitu, "init") == 0) {
			printQueue(*q, outFile);
		}
		else if (strcmp(kitu, "enqueue") == 0) {
			kitu = strtok_s(nullptr, " ", &context);
			if (kitu != nullptr) {
				int key = atoi(kitu);
				enqueue(*q, key);
			}
			printQueue(*q, outFile);
		}
		else if (strcmp(kitu, "dequeue") == 0) {
			if (!isEmpty(*q)) {
				dequeue(*q);
			}
			printQueue(*q, outFile);
		}

	}
	inFile.close();
	outFile.close();
	clearQueue(*q);
	delete q;
	return 0;
}