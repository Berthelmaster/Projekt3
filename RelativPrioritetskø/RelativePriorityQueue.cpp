#include "RelativePriorityQueue.h"
#include <iostream>


RelativePriorityQueue::RelativePriorityQueue()
{
	frontPtr = nullptr; 
}

// Precondition: The queue isn’t empty
// Postcondition: Front elements minute value has been counted 1 down, and if minutevalue is less or equal to 0, true is returned, and removeFront() has been called
bool RelativePriorityQueue::Tick()
{
	if (frontPtr != nullptr && (--(frontPtr->minuteValue)) <= 0)
	{
		removeFront();
		return true;
	}
	else
		return false;
}

// Precondition: A RelativePriorityQueue has been created
// Postcondition: A bool has been returned, true if it is empty and false if not
bool RelativePriorityQueue::isEmpty()
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

// Precondition: The queue isn’t empty, and the front elements minute value is 0
// Postcondition: The coffeeOrder has been sent, and the front element has been removed
void RelativePriorityQueue::removeFront()
{
	//std::cout << "Element has been removed" << std::endl; 
	Node* tmp = frontPtr;
	sendCoffeeOrder(tmp);
	frontPtr = frontPtr->next;
	removeElementInTxt(tmp);
	delete tmp;
	if (frontPtr != nullptr && frontPtr->minuteValue == 0)
		removeFront(); 
}

// Precondition: The queue is empty
// Postcondition: All elements are inserted, in the correct order
void RelativePriorityQueue::insertAll()
{
	if (isEmpty())
	{
		int i = 0;
		while (insertElement(++i));
	}

}

// Precondition: There is one new coffeeorder to be inserted in queue last in the text dokument
// Postcondition: The new (last i txt-file) coffeeorder is inserted in queue
void RelativePriorityQueue::insertNew()
{
	int lastLine = getLastlineInTxt(); 
	insertElement(lastLine);
}

// Precondition: There is an element to be inserted on the line number
// Postcondition: The element has been inserted in the right place, and the node is correct
bool RelativePriorityQueue::insertElement(int line)
{
	if (stringInline(line).length() != 25)
	{
		return false;
	}
	else
	{
		if (!isEmpty()) 
		{
			Node* p = convertLineToNode(line);
			Node* tmpPtr = frontPtr;
			int minutesTotal = frontPtr->minuteValue;
			while (p->minuteValue >= minutesTotal && tmpPtr->next != nullptr)
			{
				minutesTotal = minutesTotal + tmpPtr->next->minuteValue;
				if (p->minuteValue >= minutesTotal)
					tmpPtr = tmpPtr->next;
			}

			if (tmpPtr->minuteValue > p->minuteValue)
			{
				frontPtr = p;
				tmpPtr->minuteValue = tmpPtr->minuteValue - p->minuteValue; 
				p->next = tmpPtr; 
			}
			else
			{
				p->next = tmpPtr->next;
				tmpPtr->next = p;
				if (p->next == nullptr)
					p->minuteValue = p->minuteValue - minutesTotal;
				else
				{
					p->minuteValue = p->minuteValue - (minutesTotal - p->next->minuteValue);
					p->next->minuteValue = p->next->minuteValue - p->minuteValue; 
				}
			}

			return true;
		}
		else
		{
			Node* p = convertLineToNode(line);
			frontPtr = p;
			p->next = nullptr; 
			return true; 
		}
	}
}

// Precondition: There is a correct formatted coffeeorder in a txt-file on the given line
// Postcondition: The line has been converted into a new Node, and a pointer has been returned
Node* RelativePriorityQueue::convertLineToNode(int line)
{
	// Make coffee order
	std::string orderline = stringInline(line); 
	CoffeeOrder order(orderline[6], orderline[0], orderline[3]);

	// Make minutevalue
	time_t rawtime;
	struct tm ordertime;

	time(&rawtime);

	char minutesorder[3] = { orderline[12], orderline[13], '\0' }; 
	char hoursorder[3] = { orderline[9], orderline[10], '\0' };
	char dayorder[3] = { orderline[23], orderline[24], '\0' };
	char monthorder[3] = { orderline[20], orderline[21], '\0' };
	char yearorder[5] = { orderline[15], orderline[16], orderline[17], orderline[18], '\0' };

	int minutesorderint = atoi(minutesorder);
	int hoursorderint = atoi(hoursorder);
	int dayorderint = atoi(dayorder);
	int monthorderint = atoi(monthorder);
	int yearorderint = atoi(yearorder);

	ordertime = *localtime(&rawtime);
	ordertime.tm_min = minutesorderint; //https://stackoverflow.com/questions/11213326/how-to-convert-a-string-variable-containing-time-to-time-t-type-in-c
	ordertime.tm_hour = hoursorderint;
	ordertime.tm_mday = dayorderint;
	ordertime.tm_mon = monthorderint - 1;
	ordertime.tm_year = yearorderint - 1900;

	double minutevalue = (difftime(mktime(&ordertime), rawtime)) / 60; //http://www.cplusplus.com/reference/ctime/difftime/

	Node* tmpPtr = new Node((int)minutevalue, order, orderline);

	return tmpPtr;
}

// Precondition: A line number is availeble to be controlled
// Postcondition: A string has been returned with text in line number
std::string RelativePriorityQueue::stringInline(int line)
{	
	coffeeorderfile.open(filename);
	std::string my_line;
	int i = 1;
	coffeeorderfile.seekg(0, std::ios::beg);
	if (coffeeorderfile.is_open())
	{
		while (!coffeeorderfile.eof())
		{
			std::getline(coffeeorderfile, my_line);
			if (i++ == line)
			{
				coffeeorderfile.close();
				return my_line;
			}
				
		}
	}
	coffeeorderfile.close();
	return "";
}

// Precondition: The txt-file isn't empty, and the element which is being send to be brewed is in the txt-file
// Postcondition: The coffeeorder equal to the one in the Node is deleted from the txt-file
void RelativePriorityQueue::removeElementInTxt(Node* nodeToBeRemoved)
{	
	coffeeorderfile.open(filename);
	int deleteline;
	nodeToBeRemoved->orderline; 
	std::string my_line;
	int i = 1;
	coffeeorderfile.seekg(0, std::ios::beg);
	if (coffeeorderfile.is_open())
	{
		while (!coffeeorderfile.eof())
		{
			std::getline(coffeeorderfile, my_line); 

			if (nodeToBeRemoved->orderline == my_line)
			{
				deleteline = i; 
				break; 
			}
			i++;
		}
	}
	coffeeorderfile.close();

	delete_line(filename, deleteline);
}

// Precondition: The txt - file isn't empty\\
// Postcondition: The line number of the last line i txt - file has been returned
int RelativePriorityQueue::getLastlineInTxt()
{
	coffeeorderfile.open(filename);
	std::string my_line;
	int i = 1;
	coffeeorderfile.seekg(0, std::ios::beg);
	if (coffeeorderfile.is_open())
	{
		while (1)
		{
			std::getline(coffeeorderfile, my_line);
			if (coffeeorderfile.eof())
			{
				break; 
			}
			++i;
		}
	}
	coffeeorderfile.close();
	return i; 
}

/* Delete_line is copied from: https://www.geeksforgeeks.org/program-delete-line-given-line-number-file/ */
void RelativePriorityQueue::delete_line(const char *file_name, int n)
{
	coffeeorderfile.open(file_name);

	// open file in write mode or out mode 
	std::ofstream ofs;
	ofs.open("temp.txt", std::ofstream::out);

	// loop getting single characters 
	char c;
	int line_no = 1;
	while (coffeeorderfile.get(c))
	{
		// if a newline character 
		if (c == '\n')
			line_no++;

		// file content not to be deleted 
		if (line_no != n)
			ofs << c;
	}

	// closing output file 
	ofs.close();

	// closing input file 
	coffeeorderfile.close();

	// remove the original file 
	std::remove(file_name);

	// rename the file 
	std::rename("temp.txt", file_name);
}

// This function has not been implemented, it will need the other threads and a messagequeue
void RelativePriorityQueue::sendCoffeeOrder(Node * coffeeorder)
{
	std::cout << "Coffeeorder sent: " << coffeeorder->orderline << std::endl; 
}

void RelativePriorityQueue::printFront()
{
	if (!isEmpty())
	{
		std::cout << "Minute: " << frontPtr->minuteValue << " Pointer: " << frontPtr << std::endl;
	}
	else
		std::cout << "No element in front" << std::endl; 
}

RelativePriorityQueue::~RelativePriorityQueue()
{
	coffeeorderfile.close();
}
