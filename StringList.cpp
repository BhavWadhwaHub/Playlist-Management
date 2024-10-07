//301609355
//Bhav Wadhwa
#include "StringList.h"
#include <stdexcept>
#include <iostream>
using std::out_of_range;
using std::cout;
using std::endl;
using std::stoi;
using std::to_string;

// Default constructor - makes an empty list of capacity 10
StringList::StringList()
{
	capacity = 10;
	n = 0;
	arr = new string[capacity];
}

// Copy constructor
StringList::StringList(const StringList& other)
{
	copyList(other);
}

// ***UNDOABLE
// Overloaded assignment operator
StringList& StringList::operator=(const StringList& other) 
{
    if (&other != this) 
    {
        // Save the current state before assignment for undo purposes
        string old = "{";
        for (int i = 0; i < n; i++) 
        {
            if (i > 0) 
            {
                old += ", ";
            }
            old += "\"" + arr[i] + "\"";
        }
        old += "}";

        // Push the previous state to the undo stack (for undoing the assignment)
        Undostack.push("ASSIGN "+old);

        // Perform the actual assignment
        delete[] arr;
        copyList(other);
    }
    return *this;
}

// Destructor
StringList::~StringList()
{
	delete[] arr;
}

// ACCESSORS
// Returns the number of elements in the list
int StringList::size() const
{
	return n;
}

// Returns true if the list is empty, false otherwise
bool StringList::empty() const
{
	return n == 0;
}

// Returns the string at the given index
string StringList::get(int i) const
{
	checkBounds(i, "get");
	return arr[i];
}

// Returns the index of the first occurrence of the given string
int StringList::index(string s) const
{
	int i = 0;
	while (i < n && s != arr[i]) {
		i++;
	}
	if (i == n) {
		return -1;
	}
	else {
		return i;
	}
}

// Returns true iff the given string is in the list
bool StringList::contains(string str) const
{
	return !(index(str) == -1);
}

// Returns true if the two lists are equal, false otherwise.
// Does *not* consider any undo information when comparing two Stringlists. All
// that matters is that they have the same strings in the same order.
bool StringList::operator==(const StringList& sl) const
{
	if (size() != sl.size())
	{
		return false;
	}
	for (int i = 0; i < size(); i++)
	{
		if (get(i) != sl.get(i))
		{
			return false;
		}
	}
	return true;
}

// Returns true if the two lists are not equal, false otherwise
bool StringList::operator!=(const StringList& sl) const
{
	return !(*this == sl);
}

// Returns a string representation of the list.
string StringList::toString() const
{
	string result = "{";
	for (int i = 0; i < size(); i++)
	{
		if (i > 0) {
			result += ", ";
		}
		result += "\"" + get(i) + "\"";
	}
	return result + "}";
}


// MUTATORS

// ***UNDOABLE
// Sets the value at the given index
void StringList::set(int i, string str)
{
	checkBounds(i, "set");
	 // This allows the undo operation to know exactly which element was changed and what its previous value was, so that it can be restored if needed.
	Undostack.push("SET " + to_string(i) + " " + arr[i]);
	arr[i] = str;
}

// ***UNDOABLE
// Inserts the given string *before* the given index
void StringList::insertBefore(int pos, string str)
{
	// Doesn't use checkBounds because it's okay to insert at the end
	if (pos < 0 || pos > size()) {
		throw out_of_range("StringList::insertBefore index out of bounds");
	}
	checkCapacity();
	for (int i = n; i > pos; i--) {
		arr[i] = arr[i-1];
	}
	arr[pos] = str;
	n++;
	Undostack.push("REMOVE " + to_string(pos));
}

// ***UNDOABLE
// Inserts the given string at the front of the list
void StringList::insertFront(string str)
{
	checkCapacity();
	insertBefore(0, str);
}

// ***UNDOABLE
// Inserts the given string at the back of the list
void StringList::insertBack(string str)
{
	checkCapacity();
	insertBefore(n, str);
}

// ***UNDOABLE
// Removes the element at the given index and moves elements after it down
void StringList::remove(int pos)
{
	checkBounds(pos, "remove");
	string removed = arr[pos];
	for (int i = pos; i < n; i++) {
		arr[i] = arr[i + 1];
	}
	n--;
	Undostack.push("INSERT " + to_string(pos) + " " + removed);
}

// ***UNDOABLE
// Empties the list
void StringList::removeAll() {
    // Save the current state of the entire list for undo purposes
    string currentState = "{";
    for (int i = 0; i < n; i++) 
    {
        if (i > 0) 
        {
            currentState += ", ";
        }
        currentState += "\"" + arr[i] + "\"";
    }
    currentState += "}";

    // Push the entire list's state onto the undo stack
    Undostack.push("ASSIGN " + currentState);

    // Remove all elements from the list
    n = 0;
}

// Undoes the last operation that modified the list
void StringList::undo()
{
	// TO DO
	if (Undostack.isEmpty()) // Check if there's anything to undo
    {
        cout << "Nothing to undo." << endl;
        return;
    }

    string popped = Undostack.pop(); // Pop the last operation from the undo stack

    if (popped.substr(0, 6) == "REMOVE") // Check if the last operation was a REMOVE
    {
        int index = stoi(popped.substr(7)); // Extract the index from the operation string
        this->remove(index);    // Remove the element at the given index
    } 
    else if (popped.substr(0, 6) == "INSERT") // Check if the last operation was an INSERT
    {
        int i = 7;
        while (i < static_cast<int>(popped.length()) && popped[i] != ' ') 
        {
            i++;
        }
        int index = stoi(popped.substr(7, i - 7));  // Extract the index from the operation string
        string value = popped.substr(i + 1);    // Extract the value from the operation string
        insertBefore(index, value); // Re-insert the string at the given index
    } 
    // Check if the last operation was a SET
    else if (popped.substr(0, 3) == "SET") 
    {
        int i = 4; // Skip "SET "
        while (i < static_cast<int>(popped.length()) && popped[i] != ' ') 
        {
            i++;
        }
        int index = stoi(popped.substr(4, i - 4));  // Extract the index
        string previousValue = popped.substr(i + 1);  // Extract the previous value

        // Restore the previous value at the specified index using set()
        set(index, previousValue);
    }
    else if (popped.substr(0, 6) == "ASSIGN") // Check if the last operation was an ASSIGN
    {
        string oldState = popped.substr(7); // Extract the old state of the list
        removeAll();

        // Reconstruct the list from the saved state
        int i = 1; // Skipping the opening '{'
        while (i < static_cast<int>(oldState.length()) && oldState[i] != '}') 
        {
            string value = "";
            while (oldState[i] != '"' && i < static_cast<int>(oldState.length())) 
            {
                i++;
            }
            i++;  // Skip the opening quote
            while (oldState[i] != '"' && i < static_cast<int>(oldState.length())) 
            {
                value += oldState[i];
                i++;
            }
            i++;  // Skip the closing quote
            insertBack(value);
        }
    }
}

// Prints the list
void StringList::print() const
{
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
}

// Helper function for checking index bounds.
void StringList::checkBounds(int i, string s) const
{
	if (i < 0 || i >= size()) {
		throw out_of_range("StringList::" + s + " index out of bounds");
	}
}

// POST: Doubles the capacity of the list if n == capacity
void StringList::checkCapacity()
{
	if (n == capacity) {
		capacity *= 2;
		string* temp = new string[capacity];
		
		for (int i = 0; i < n; i++) {
			temp[i] = arr[i];
		}
		delete[] arr;
		arr = temp;
	}
}

// Helper function to copy the contents of another list
void StringList::copyList(const StringList& lst)
{
	capacity = lst.capacity;
	n = lst.n;
	arr = new string[capacity];

	for (int i = 0; i < n; i++) {
		arr[i] = lst.arr[i];
	}
}
//stack class implementation
StringList::Stack::Stack()
{
    capacity = 4;   //Set initial capacity to 4
    currentSize = 0;    //No elements in starting
    arr = new string[capacity];
}
StringList::Stack::~Stack()
{
    delete[] arr;
}
void StringList::Stack::increaseCapacity()
{
    capacity *= 2;
    string* newArr = new string[capacity];
    for (int i = 0; i < currentSize; i++) 
    {
        newArr[i] = arr[i];
    }
    delete[] arr;
    arr = newArr;
}
void StringList::Stack::push(const string& top)
{
    if (currentSize == capacity) // Check if there's enough space to add a new element
    {
        increaseCapacity(); // If not, double the capacity
    }
    arr[currentSize] = top;
    currentSize++;
}

string StringList::Stack::pop()
{
    if (isEmpty()) 
    {
        throw out_of_range("Stack is empty.");
    }

    // Return the top string and decrease the size of the stack
    string top = arr[currentSize - 1]; 
    currentSize--;
    return top;
}

bool StringList::Stack::isEmpty()
{
    return currentSize == 0; // True if the stack contains no elements
}


