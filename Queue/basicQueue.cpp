#include <iostream>
#include <limits.h> // For INT_MIN

class Queue {
    int *arr;       // Pointer to the array that holds queue elements
    int capacity;   // Maximum number of elements the queue can hold
    int front;      // Index of the front element
    int rear;       // Index of the rear element
    int count;      // Current size of the queue

public:
    // Constructor to initialize the queue with a given capacity
    Queue(int size) {
        arr = new int[size]; // Dynamically allocate an array
        capacity = size;
        front = 0;           // Start front at 0
        rear = -1;           // Rear is set to -1 initially (no elements yet)
        count = 0;           // No elements in the queue yet
    }

    // Destructor to free the allocated memory
    ~Queue() {
        delete[] arr;
    }

    // Function to add an element to the queue
    void queueEnqueue(int data) {
        // Check if the queue is full
        if (isFull()) {
            std::cout << "Queue is full\n";
            return;
        }
        // Use circular increment for rear
        rear = (rear + 1) % capacity;
        arr[rear] = data;
        count++; // Increase queue size
    }

    // Function to remove an element from the queue
    void queueDequeue() {
        // Check if the queue is empty
        if (isEmpty()) {
            std::cout << "Queue is empty\n";
            return;
        }
        // Simply move front to the next index (circularly)
        front = (front + 1) % capacity;
        count--; // Decrease queue size
    }

    // Function to get the front element of the queue
    int frontElement() {
        if (isEmpty()) {
            std::cout << "Queue is empty\n";
            return INT_MIN; // Return a minimum value to indicate error
        }
        return arr[front];
    }

    // Function to get the rear element of the queue
    int rearElement() {
        if (isEmpty()) {
            std::cout << "Queue is empty\n";
            return INT_MIN;
        }
        return arr[rear];
    }

    // Check if the queue is empty
    bool isEmpty() {
        return (count == 0);
    }

    // Check if the queue is full
    bool isFull() {
        return (count == capacity);
    }

    // Function to get the current size of the queue
    int size() {
        return count;
    }
};

int main() {
    // Create a queue with capacity 5
    Queue q(5);

    // Enqueue elements into the queue
    q.queueEnqueue(1);
    q.queueEnqueue(8);
    q.queueEnqueue(3);
    q.queueEnqueue(6);
    q.queueEnqueue(2);

    // Try adding one more element (should display "Queue is full")
    q.queueEnqueue(10);

    // Display current size, front and rear elements of the queue
    std::cout << "Queue size: " << q.size() << "\n";
    std::cout << "Front element: " << q.frontElement() << "\n";
    std::cout << "Rear element: " << q.rearElement() << "\n";

    // Dequeue an element and display the new front element
    q.queueDequeue();
    std::cout << "Front element after dequeue: " << q.frontElement() << "\n";

    return 0;
}
