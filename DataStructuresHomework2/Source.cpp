// Homework 2 for Data Structures
//
// Fun with Linked Lists
//
// Usage: Run from console with User Input
//
// Programmer: Ryan Shoemake
//
// 06/21/2018 - Start and Finish
//
/////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

struct Node {
	int data;
	Node *next;
};

//I'll need functions here for the homework.
//One that gets the number of elements requested from the user.
//One to create Numbers.txt with random variables based on the size the user enters. -Make sure to check file was created.
//Unformated print.
//Formated print.
//One that inserts the data from Numbers.txt in the order it was recieved. Print this unformated.
//One that arranges in ascending order.
//One that arranges in descending order.
//Delete the list.

bool GetUserInput(int &Size);
void CreateFile(int Size);
//void PrintFile();					//DELETE. DEBUGGING PURPOSES
int InsertNormal(Node *&);
int InsertReverse(Node *&);
int InsertAscend(Node *&);
int InsertDescend(Node *&);
void PrintDirty(Node *);
void PrintClean(Node *);
void DeleteList(Node *&);

string InFile = "Numbers.txt";


int main() {
	int Size;

	//Do a validity check to see if the program should continue. This is another layer of checking. The function
	// will check input as well.
	if (GetUserInput(Size)) {
		struct Node *Head;
		Head = NULL;
		//This is the second function in the first part of the homework. 
		// It's a simplistic function to write "Size" number of random variables
		// to a file.
		CreateFile(Size);
		//PrintFile();		//DELETE ME OR COMMENT OUT FOR FINAL TURN IN--------------------------------
		//------------------END OF PROBLEM 1--------------------

		//This will be the second part of the homework. A function will insert the numbers directly
		// from the file created in part 1. It will then print them to console line by line.
		// Then it will print them in a formatted way. And then a delete function will be called.
		InsertNormal(Head);
		PrintDirty(Head);
		PrintClean(Head);
		DeleteList(Head);
		//------------------END OF PROBLEM 2--------------------

		//This part will be almost exactly the same except the insert function will create the linked
		// list in reverse.
		InsertReverse(Head);
		PrintDirty(Head);
		PrintClean(Head);
		DeleteList(Head);
		//------------------END OF PROBLEM 3--------------------

		//Once again, this will be almost the same except there will be two insert functions and the 
		// unformatted print will not exist. The first function will create a linked list from smallest
		// to largest number and the second function will do the opposite.
		InsertAscend(Head);
		PrintClean(Head);
		DeleteList(Head);

		InsertDescend(Head);
		PrintClean(Head);
		DeleteList(Head);
		//------------------END OF PROBLEM 4--------------------

		//cout << "Worked";	-----------Debug
		//system("pause");	-----------Debug
	}
	else {
		cout << "Invalid Input. Get out." << endl;
	}
	system("pause");
	return 0;
}

bool GetUserInput(int &Size) {
	string denied;		// This is to catch ANY input the user gives

	//Prompt the user for input. Try to be as clear as possible....
	cout << "Please enter a size for the linked list.\nThe size must be an integer between 20 and 100.\n20 and 100 ARE valid choices.\n";
	cin >> denied;
	Size = atoi(denied.c_str());
	if (Size >= 20 && Size <= 100) {
		return true;
	}
	else {
		cout << "You tried to pass " << denied << " ?\nThat's just ridiculous..\n";	
		return false;
	}

}

void CreateFile(int Size) {
	//Seeding the random to be able to create different random integers.
	srand(time(NULL));
	//Output file is called Numbers.txt as instructed.
	ofstream fout("Numbers.txt");

	//Randomly generate numbers to send to Numbers.txt. I usually randomize numbers around 1-100 for easy debugging
	for (int i = 0; i < Size; i++) {
		fout << rand() % 100 + 1 << endl;
	}
	fout.close();
}

//DELETE ME OR COMMENT ME OUT FOR FINAL TURNIN
void PrintFile() {
	ifstream fin(InFile.c_str());
	int counter = 0;

	int holdme;
	while (fin >> holdme) {
		cout << holdme << " ";
	}
	cout << endl;
	fin.close();
}

int InsertNormal(Node *&Head) {
	//Opening up the input file and declaring a holder variable.
	ifstream fin(InFile.c_str());
	int x;

	//Get the first variable here, just in case Head == NULL
	fin >> x;

	//Creates Head. We are not using a sentinel head.
	if (Head == NULL) {
		Head = new Node;
		Head->data = x;
		Head->next = NULL;
	}

	//Create a while loop to grab the values from the InFile. This will continue to move and add
	// new nodes as long as we are pulling information from the file.
	Node *curr;
	curr = Head;
	while (fin >> x) {
		curr->next = new Node;
		curr = curr->next;
		curr->data = x;
		curr->next = NULL;
	}
	fin.close();
	return 0;
}

int InsertReverse(Node *&Head) {
	//Opening up the input file and declaring a holder variable.
	ifstream fin(InFile.c_str());
	int x;

	//Get the first variable here, just in case Head == NULL
	fin >> x;

	//Creates Head. We are not using a sentinel head.
	if (Head == NULL) {
		Head = new Node;
		Head->data = x;
		Head->next = NULL;
	}

	//Create a while loop to grab the values from the InFile. This will continue to move and add
	// new nodes as long as we are pulling information from the file.
	//For reversing the linked list, I chose to create new nodes and link them to head and then 
	// keep moving head backwards. This made the most sense to me, though it did feel a little
	// off moving Head that much.
	Node *curr;
	while (fin >> x) {
		curr = new Node;
		curr->next = Head;
		curr->data = x;
		Head = curr;
	}
	fin.close();
	return 0;
}

int InsertAscend(Node *&Head) {
	//Opening up the input file and declaring a holder variable.
	ifstream fin(InFile.c_str());
	int x;

	//Get the first variable here, just in case Head == NULL
	fin >> x;

	//Creates Head. We are not using a sentinel head.
	if (Head == NULL) {
		Head = new Node;
		Head->data = x;
		Head->next = NULL;
	}

	//Create a while loop to grab the values from the InFile. This will continue to move and add
	// new nodes as long as we are pulling information from the file.
	//I'll grab most of this code from the code papers given in class. I've made a few modifications
	// due to doing things a little differently. I also found out that I'll have to check the Head
	// value against the x value in case it needs to be switched.
	Node *curr;
	curr = Head;
	Node *newnode;
	while (fin >> x) {
		if (Head->data > x) {		//THIS PART COULD BE ELIMINATED BY USING A HEAD SENTINEL-----------
			newnode = new Node;
			newnode->data = x;
			newnode->next = Head;
			Head = newnode;
		}
		else {
			while ((curr->next != NULL) && (curr->next->data < x)) {
				curr = curr->next;
			}
			if ((newnode = new Node) == NULL) {
				cout << "You are out of space!" << endl;
				return 1;
			}
			newnode->data = x;
			newnode->next = curr->next;
			curr->next = newnode;
			curr = Head;
		}
	}
	fin.close();
	return 0;
}

int InsertDescend(Node *&Head) {
	//Opening up the input file and declaring a holder variable.
	ifstream fin(InFile.c_str());
	int x;

	//Get the first variable here, just in case Head == NULL
	fin >> x;

	//Creates Head. We are not using a sentinel head.
	if (Head == NULL) {
		Head = new Node;
		Head->data = x;
		Head->next = NULL;
	}

	//Create a while loop to grab the values from the InFile. This will continue to move and add
	// new nodes as long as we are pulling information from the file.
	//This will be almost the exact same as the Ascend function. The only differences will be
	// changing the Head->data ">" to a "<" and the other "<" in the else - while loop to ">"
	Node *curr;
	curr = Head;
	Node *newnode;
	while (fin >> x) {
		if (Head->data < x) {		//THIS PART COULD BE ELIMINATED BY USING A HEAD SENTINEL-----------
			newnode = new Node;
			newnode->data = x;
			newnode->next = Head;
			Head = newnode;
		}
		else {
			while ((curr->next != NULL) && (curr->next->data > x)) {
				curr = curr->next;
			}
			if ((newnode = new Node) == NULL) {
				cout << "You are out of space!" << endl;
				return 1;
			}
			newnode->data = x;
			newnode->next = curr->next;
			curr->next = newnode;
			curr = Head;
		}
	}
	fin.close();
	return 0;
}

void PrintDirty(Node *Head) {
	//Make a check to see if the list is actually empty.
	if (Head == NULL) {
		cout << "Link is empty\n";
	}

	//Traverse through the list one at a time printing out the values in each node.
	// This will continue until tmp is NULL;
	Node *tmp;
	tmp = Head;
	while (tmp != NULL) {
		cout << tmp->data << endl;
		tmp = tmp->next;
	}
}

void PrintClean(Node *Head) {
	//Make a check to see if the list is actually empty.
	if (Head == NULL) {
		cout << "Link is empty\n";
	}

	//Traverse through the list one at a time printing out the values in each node.
	// This will continue until tmp is NULL;
	// The code for formatting (the counter and mod routine) was taken primarily from
	// handouts recieved in class
	Node *tmp;
	tmp = Head;
	int counter = 1;
	while (tmp != NULL) {
		cout << tmp->data << "\t";
		if (counter % 5 == 0) {
			cout << endl;
			counter = 0;
		}
		tmp = tmp->next;
		counter++;
	}
}

void DeleteList(Node *&Head) {
	//Make a check to see if the list is actually empty.
	if (Head == NULL) {
		cout << "Link is empty\n";
		delete Head;	//I'm not sure if this is even needed? -------------------------
	}

	//Traverse through the list one at a time deleting the nodes.
	// This will continue until Head is NULL;
	Node *tmp;
	tmp = Head;
	while (Head != NULL) {
		tmp = tmp->next;
		delete Head;
		Head = tmp;
	}
}