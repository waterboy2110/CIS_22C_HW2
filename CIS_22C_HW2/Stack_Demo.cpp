/**~*~*
  This program demonstrates two basic stack operations:
  push and pop.

  James Agua: 20122405
  Stack_Demo is HW2.
  Implemented getCount, getTop, readFile, Strtok and used removeTrailingWhiteSpace.
  Extended menu to include new choices.
  Used vector and stringsteams to process file.
  readFile is messy - should refactor if time permits.
*~**/
#include <iostream>
#include <string>
#include "Stack.h"
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <sstream>

using namespace std;

// Constants for the menu choices
const int PUSH_CHOICE			= 1,
          POP_CHOICE			= 2,
		  PEEK_CHOICE			= 3,
		  TEST_FILE_CHOICE		= 4,
          QUIT_CHOICE			= 5;

// Function prototypes
int menu();
int getValidNum(int low, int high);
void pushItem(Stack<string> *);
void popItem(Stack<string> *);
void peekItem(Stack<string> *);
bool processFile(Stack<string> *);
string removeTrailingWhiteSpace(string str);
void Strtok(vector<string>*, string, char*);
void pushStack(Stack<string> *, string);
void popStack(Stack<string> *);
void flushStack(Stack<string> *);


int main()
{
    int choice;    // To hold a menu choice

    // Create the stack.
    Stack<string> *stack = new Stack<string>;

    while ((choice = menu())!= QUIT_CHOICE)
    {
        switch (choice)
        {
           case PUSH_CHOICE:
                pushItem(stack);
                break;
           case POP_CHOICE:
                popItem(stack);
				break;
		   case PEEK_CHOICE:
			   peekItem(stack);
				break;
		  case TEST_FILE_CHOICE:
			  processFile(stack);
        }
    }

    delete stack;
    cout << "\n\t*** THE END ***\n";
    return 0;
}

/**~*~*
   The menu function displays the menu and gets
   the user's choice, which is assigned to the
   reference parameter.
*~**/
int menu()
{
    int choice;
     // Display the menu and get the user's choice.
     cout << "\n\nWhat do you want to do?\n\t"
          << PUSH_CHOICE
          << " - Push an item onto the stack\n\t"
          << POP_CHOICE
          << " - Pop an item off the stack\n\t"
		  << PEEK_CHOICE
		  << " - Peek at the top of the stack\n\t"
		  << TEST_FILE_CHOICE
		  << " - Process file\n\t"
          << QUIT_CHOICE
          << " - Quit the program\n"
          << "Enter your choice: ";

     choice = getValidNum(PUSH_CHOICE, QUIT_CHOICE);
     return choice;
}

/**~*~*
   The pushItem function gets an item from the
   user and pushes it onto the stack.
*~**/
void pushItem(Stack<string> *stack)
{
     string item;

     // Get an item to push onto the stack.
     cout << "\nEnter an item: ";
     getline(cin, item);
     stack->push(item);
}

/**~*~*
//	The pushStack fuction places an item on the
//	stack from the file. Used in the readFile
//	method due to different input requirments.
//	could implement overload pushItem for cleaner
//	code.
*~**/
void pushStack(Stack<string> *stack, string item)
{
	stack->push(item);
	cout << "\n\tPush " << item << " ";
}

/**~*~*
   The popItem function pops an item from the stack
*~**/
void popItem(Stack<string> *stack)
{
     bool status;
     string item = "";

     // Pop the item.
     status = stack->pop(item);

     // Display the item.
     if (status)
        cout << "\n\t" << item << " was popped.\n\n";
     else
        cout << "\n\t*** Empty stack! ***\n\n";
}

/**~*~*
//	The popStack fuction pops an item off the
//	stack and displays the item. Used for the
//	readFile method due to formatting.
*~**/
void popStack(Stack<string> *stack)
{
	 bool status;
     string item = "";

     // Pop the item.
     status = stack->pop(item);

     // Display the item.
     if (status)
        cout << item << " ";
     else
        cout << "\n\t*** Empty stack! ***\n\n";

}

/**~*~*
//	The flushStack fuction pops an items off the
//	stack until the stack is empty. Cleans up stack
//	at the end of the file operation.
*~**/
void flushStack(Stack<string> *stack)
{
	 bool status = true;
     string item = "";

     // Pop the items until empty.
	 while(status)
	 {
		 status = stack->pop(item);
		 // Display message that stack is empty
		 if (!status)
			 cout << "\n\t***  Stack has been flushed! ***\n\n";
	 }
}

/**~*~*
   This function displays the value at the top of the stack without changing the stack
*~**/
void peekItem(Stack<string> *stack)
{
	bool status;
	string item = "";

	//peek at the top of the stack
	status = stack->getTop(item);

	// Display the top of the stack
	if (status)
		cout << "Display the elmement on top of the stack: " << item;
	else
		cout << "\t*** Empty stack! ***\n";
}

/**~*~*
   This function prompts the user to enter an integer number within a given range
   If the input is not valid (not a number or if it is outside of the range) it
   prompts the user to enter a new number, until the input is valid.
*~**/
int getValidNum(int low, int high)
{
    int num;
    bool success;

    do
    {
        cout << "Please enter a number (" << low << " to " << high << "): ";
        cin >> num;
        cin.clear();          // to clear the error flag
        cin.ignore(80, '\n'); // to discard the unwanted input from the input buffer
    }while(!success || num < low || num > high);

    return num;
}

//**************************************************
// Definition of function processFile.
// This function will read all the data from
// the file given by the user and process them using 
// Stack.This function returns true if read successfully,
// and false if it did not read successfully.
// TODO: pass vector to Strtok as a reference and delete it
// at the end of processFile - passing by pointer - pretty sure
// it's deleted.
// Each test should be a method.
//**************************************************
bool processFile(Stack<string> *stack)
{
   ifstream inFile;
   string readStr;
   string fileName;
   string data;
   bool empty = true;
   vector<string> vstring;
   int number = 0;

   // Promt user for filename to open
   cout << "Enter the name of the file you wish to process:\n";
   cin >> fileName;

// Open file to read, if couldn't open, display error
   // and exit with false
   inFile.open(fileName);
   if (!inFile)
   {
      cout << "Error opening " << fileName << "!\n";
      return false;
   }

   while (getline(inFile, readStr))  // get data from file.
   {
	   data = removeTrailingWhiteSpace(readStr);
	   //cout << "\nData Input: " << data << "\n"; //DEBUG**
	   
	   // Seperate the strings into groups of strings of numbers
	   Strtok(&vstring, data, " ");
	   
	   // Process the vector of strings
	   for(int i = 0; i < vstring.size(); i++)
	   {
		 if(! (istringstream(vstring[i]) >> number) ) number = 0; //convert the string @ vector[i] to a number, 0 if conversion fails.
		 
		 //Run the tests - would be better if these were thier own functions
		 if(number > 1)
			 pushStack(stack, vstring[i]);
		
		 else if(number < 0)
		 {
			 int absoluteNumber = abs(number);
			 if( absoluteNumber <= stack->getCount())
			 {
				 cout << "\n\t" << number << ": Pop and print " << absoluteNumber << " number(s): ";
				 for(int i = 0; i < absoluteNumber; i++)
					popStack(stack); 
			 }
			 else
				 cout << "\n\t" << number << ": The stack has less than " << absoluteNumber << " items."; 
		 }
		 
		 else if(number == 0)
			 cout << "\n\t" << number << ": The stack has " << stack->getCount() << " numbers.";
		 
		 else
		 {
			 cout << "\n\t" << number << ": ";
			 peekItem(stack);
		 }
	   }
   }

   inFile.close();
   // Flush the stack
   flushStack(stack);
   // delete the vector
   vstring.erase(vstring.begin(), vstring.begin() + vstring.size());

   if (empty)
      return false;

   return true;
}

//**************************************************
// Definition of function removeTrailingWhiteSpace.
// This function removes trailing white spaces at
// the back of the string, str, and returns the new
// string. Removes trailing tabs, line feeds,
// spaces, and carriage returns.
//**************************************************
string removeTrailingWhiteSpace(string str)
{
   int i = str.length() - 1;  // zero based
   while (str[i] == '\t' || str[i] == '\n' || str[i] == ' ' || str[i] == '\r')
   {
      str.erase(i, 1);
      i--;
   }
   return str;
}

//***************************************************
// Definition of function Strok.
// This function tokenizes the string and returns
// each element of the string as a string in a vector.
//***************************************************

void Strtok(vector<string>* vstring, string cptr, char* delimiter)
{
	string astring = cptr;
	string stemp;
	int start = 0;
	int index = astring.find(delimiter);
	// Process the string and load the vector
	while (index != string::npos)
	{
		stemp.assign(astring,start,index-start);
		vstring->push_back(stemp);
		start = index + 1;
		index = astring.find(delimiter,start);
	}
	stemp.assign(astring,start,astring.length()-start);
	vstring->push_back(stemp);
}

