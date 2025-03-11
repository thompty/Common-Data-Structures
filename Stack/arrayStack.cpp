//Fixed size stack using a fixed size array
#include <iostream>

class Stack { 
    //Top is index of top element
    //Cap is max size
    int top, cap; 
    
    //Pointer to dynamically allocate elements
    int *a; 

public: 
    //Constructor
    Stack(int cap) { 
        //Set capacity of stack
        this->cap = cap; 
        //Initialize as empty stack
        top = -1; 
        //Dynamically allocate array of size cap
        a = new int[cap]; 
    } 

    //Destructor
    ~Stack() { 
        delete[] a; 
    } 

    //Push function to insert onto stack
    bool push(int x) { 
        //Check if stack is full
        if (top >= cap - 1) { 
            std::cout << "Stack Overflow\n"; 
            return false; 
        } 
        //Increment top and insert x
        a[++top] = x; 
        return true; 
    } 

    //Pop function to remove top 
    int pop() { 
        //Check if stack is empty
        if (top < 0) { 
            std::cout << "Stack Underflow\n"; 
            return 0; 
        } 
        //Return top and decrement top
        return a[top--]; 
    } 

    //Peek function to view top without removing
    int peek() { 
        //Check if stack is empty
        if (top < 0) { 
            std::cout << "Stack is Empty\n"; 
            return 0; 
        } 
        //Return top
        return a[top]; 
    } 

    //Function to check if empty stack
    bool isEmpty() { 
        return top < 0; 
    } 
}; 