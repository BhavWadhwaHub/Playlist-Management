# Playlist Management System

A C++ project that implements a custom dynamic string list data structure with support for insertion, deletion, searching, resizing, copying, comparison, and undo operations.

The project focuses on practicing core data structures and object-oriented programming concepts by building a custom list implementation from scratch without using STL containers like `vector`.

---

# Project Overview

The Playlist Management System is built around a custom `StringList` class.

Despite the project name, the implementation is not a full music streaming or audio playback application. Instead, it is a low-level string list management system that could be used as the foundation for playlist handling.

The project demonstrates:

* Dynamic memory allocation
* Deep copying
* Operator overloading
* Stack-based undo functionality
* Dynamic array resizing
* Custom list operations
* Exception handling

---

# Features

## String List Operations

The system supports:

* Insert at front
* Insert at back
* Insert before an index
* Remove elements
* Replace elements
* Clear the list
* Search for strings
* Check containment
* Access by index

---

## Undo Functionality

The project includes an internal stack-based undo system.

Undoable operations include:

* set()
* insertBefore()
* insertFront()
* insertBack()
* remove()
* removeAll()

The undo system restores the list to its previous state.

---

## Dynamic Resizing

The list automatically increases capacity when full.

This is handled through:

```cpp
checkCapacity()
```

The internal array size doubles when necessary.

---

## Deep Copy Support

The project correctly implements:

* Copy constructor
* Assignment operator
* Destructor

This prevents shallow copy memory issues.

---

## Comparison Operations

Lists can be compared using:

```cpp
operator==
operator!=
```

Two lists are considered equal if:

* They contain the same strings
* In the same order

Undo history is not considered during comparison.

---

# Technologies Used

* C++
* Dynamic Arrays
* Object-Oriented Programming
* Stack Data Structure
* Operator Overloading
* Exception Handling
* Manual Memory Management

---

# Project Structure

```text
Playlist-Management-main/
│
├── StringList.h          # StringList class declaration
├── StringList.cpp        # StringList implementation
└── StringListTest.cpp    # Test program for validating functionality
```

---

# Core Class: StringList

The entire project is centered around the `StringList` class.

The list internally stores:

```cpp
string* arr;
```

along with:

```cpp
int n;
int capacity;
```

Where:

* `n` = current number of elements
* `capacity` = allocated array size

---

# Constructor and Memory Management

## Default Constructor

Creates an empty list with capacity 10.

```cpp
StringList();
```

---

## Copy Constructor

Creates a deep copy of another list.

```cpp
StringList(const StringList& other);
```

---

## Assignment Operator

Copies one list into another.

```cpp
StringList& operator=(const StringList& other);
```

---

## Destructor

Frees dynamically allocated memory.

```cpp
~StringList();
```

---

# Accessor Functions

## size()

Returns the number of elements.

```cpp
int size() const;
```

---

## empty()

Checks if the list is empty.

```cpp
bool empty() const;
```

---

## get()

Returns the string at a given index.

```cpp
string get(int i) const;
```

---

## index()

Returns the first occurrence of a string.

```cpp
int index(string str) const;
```

Returns:

* index if found
* `-1` if not found

---

## contains()

Checks whether a string exists in the list.

```cpp
bool contains(string str) const;
```

---

# Mutator Functions

## set()

Replaces an element at a specific index.

```cpp
void set(int i, string str);
```

---

## insertFront()

Inserts a string at the beginning.

```cpp
void insertFront(string str);
```

---

## insertBack()

Inserts a string at the end.

```cpp
void insertBack(string str);
```

---

## insertBefore()

Inserts before a given position.

```cpp
void insertBefore(int pos, string str);
```

---

## remove()

Deletes an element at a specific index.

```cpp
void remove(int pos);
```

---

## removeAll()

Clears the list.

```cpp
void removeAll();
```

---

## undo()

Restores the previous list state.

```cpp
void undo();
```

The undo feature uses an internal stack.

---

# Internal Stack Class

The project includes a nested `Stack` class.

```cpp
class Stack
```

The stack is used to store undo history.

The stack supports:

* push()
* pop()
* isEmpty()

The stack dynamically resizes when full.

---

# Dynamic Capacity Handling

The list automatically grows when capacity is reached.

```cpp
void checkCapacity();
```

The array size doubles:

```text
10 → 20 → 40 → 80
```

This improves insertion efficiency.

---

# Bounds Checking

The project validates index access using:

```cpp
checkBounds(int i, string s)
```

If an invalid index is used:

* An exception is thrown
* Invalid memory access is prevented

---

# Example Workflow

## Step 1

Create a list.

```cpp
StringList list;
```

---

## Step 2

Insert elements.

```cpp
list.insertBack("Song A");
list.insertBack("Song B");
```

---

## Step 3

Display contents.

```cpp
list.print();
```

---

## Step 4

Remove an item.

```cpp
list.remove(0);
```

---

## Step 5

Undo the operation.

```cpp
list.undo();
```

The removed item is restored.

---

# String Representation

The project supports conversion to a formatted string.

```cpp
string toString() const;
```

Useful for:

* Debugging
* Printing
* Testing

---

# Testing File

## StringListTest.cpp

This file tests:

* Insertions
* Deletions
* Equality operators
* Copying
* Undo operations
* Capacity resizing
* Bounds checking

It validates whether the list behaves correctly under different operations.

---

# Object-Oriented Programming Concepts Used

## Encapsulation

Data members are private and accessed through public methods.

---

## Deep Copying

The project demonstrates proper management of dynamically allocated memory.

Avoids:

* Memory leaks
* Shared pointers between objects
* Double deletion

---

## Operator Overloading

The project overloads:

```cpp
operator=
operator==
operator!=
```

This improves usability and readability.

---

## Dynamic Memory Allocation

The project manually manages memory using:

```cpp
new
```

and

```cpp
delete[]
```

---

## Nested Classes

The internal `Stack` class is nested inside `StringList`.

This keeps undo-related functionality encapsulated.

---

# How to Compile and Run

## Compile

Using g++:

```bash
g++ StringList.cpp StringListTest.cpp -o playlist_system
```

---

## Run

On Windows:

```bash
playlist_system.exe
```

On macOS/Linux:

```bash
./playlist_system
```

---

# Example Output

```text
[Song A, Song B, Song C]

Removing index 1...

[Song A, Song C]

Undoing operation...

[Song A, Song B, Song C]
```

---

# Limitations

Current limitations include:

* No actual audio playback
* No graphical interface
* No file saving/loading
* No STL containers used
* Undo history stored only during runtime
* No playlist metadata

---

# Possible Future Improvements

Potential enhancements include:

* File persistence
* Playlist metadata support
* Real music playlist integration
* GUI implementation
* Redo functionality
* Sorting and filtering
* Template-based generic list support
* Iterator support
* Linked-list implementation alternative
* Unit testing framework integration

---

# Educational Value

This project is valuable for learning:

* Dynamic arrays
* Manual memory management
* Copy constructors
* Assignment operators
* Stack data structures
* Undo systems
* Exception handling
* Object-oriented programming in C++

It is suitable for:

* Data structures coursework
* OOP assignments
* Intermediate C++ practice
* Dynamic memory management exercises

---

# Author

Developed as a custom C++ string list and undoable data structure project.

---

# License

This project is intended for educational and demonstration purposes.
