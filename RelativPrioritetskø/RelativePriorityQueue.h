#pragma once
#include "Node.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>


class RelativePriorityQueue
{
public:
	RelativePriorityQueue();
	bool Tick();
	bool isEmpty();
	void removeFront();
	void insertAll();
	void insertNew();
	bool insertElement(int line);
	Node* convertLineToNode(int line);
	std::string stringInline(int line);
	void removeElementInTxt(Node* nodeToBeRemoved);
	int getLastlineInTxt();
	void delete_line(const char *file_name, int n);
	void sendCoffeeOrder(Node* coffeeorder);
	void printFront(); 
	~RelativePriorityQueue();
private:
	char filename[20] = "coffeeorderfile.txt"; 
	std::ifstream coffeeorderfile;
	Node* frontPtr;
};

