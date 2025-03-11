#include <iostream>
#include <vector>
struct Node{
    //Data of the node
    int data;

    //Pointer to next node
    Node *next;

    //Constructor
    Node(int data){
        this->data = data;
        this->next = nullptr;
    }
};

//Checks if key is in linked list
bool searchKey(Node *head, int key){
    //Intialize current node with the head
    Node *curr = head;

    //Iterate through the nodes of linked list until the NULL ptr
    while(curr != nullptr){
        //Check if current node is equal to the key
        if(curr->data == key){
            //If found return true
            return true;
            
            //Move to next node
            curr = curr->next;
        }
        //If not found return false
        return false;
    }
}

//Function to count the number of nodes within the linked list
int countNodes(Node *head){
    //Initialize count
    int count = 0;
    
    //Initialize current node with the head node
    Node* curr = head; 
    
    //Iterate through the nodes of the linked list
    while(curr != nullptr){
        //Increment count by 1 for each node that is passed
        count++;
        
        //Move to next node
        curr = curr->next;
    }

    //Return length of the linked list
    return count;
}

//Recursively count the number of nodes within the linked list
int recursiveCountNodes(Node *head){
    //Check that the head is not nullptr
    if(head == nullptr){
        //If empty return 0 length
        return 0;
    }

    //Count this node plus the rest of the list
    return 1 + recursiveCountNodes(head->next);
}

//Insert a node at the head of the Linked List
Node* insertAtFront(Node *head, int newData){
    //Create a new node with the new data
    Node *newNode = new Node(newData);

    //Make the next point to the head of the current Linked List
    newNode->next = head;

    //Return the new node as the head of the list
    return newNode;
}

//Insert a node at a specific position
Node* insertAtPos(Node *head, int pos, int newData){
    //Check if pos is valid
    if(pos < 1){
        return head;
    }

    //Change head is pos is 1
    if(pos == 1){
        Node *newNode = new Node(newData);
        newNode->next = head;
        return newNode;
    }
    
    //Set current node to head 
    Node *curr = head;

    //Search through list until you get to the node right before pos of the new node
    for(int i = 1; i < pos - 1 && curr != nullptr; i++){
        curr = curr->next;
    }

    //If pos is greater than number of nodes return the head
    if(curr == nullptr){
        return head;
    }

    Node *newNode = new Node(newData);

    //Update pointers
    newNode->next = curr->next;
    curr->next = newNode;

    return head;
}

//Delete the head of the linked list
Node* deleteHead(Node* head){
    //Check if list is empty
    if(head == nullptr){
        return nullptr;
    }
    //Set head into temp value
    Node* temp = head;

    //Move the head pointer to the node after the original head
    head = head->next;

    //Free memory of the old head
    delete temp;

    return head;
}

//Delete the last node of the linked list
Node* deleteLastNode(struct Node* head){
    //If the linked list is empty return null
    if(head == nullptr){
        return nullptr;
    }

    //If the linked list only has one node delete it and return null
    if(head->next == nullptr){
        delete head;
        return nullptr;
    }

    //Find the second to last node 
    Node* secondToLast = head;
    while (secondToLast->next->next != nullptr){
        secondToLast = secondToLast->next;
    }

    //Delete the last node
    delete(secondToLast->next);

    //Change the next of the second to last node to null
    secondToLast->next = nullptr;

    return head;
}

//Delete a node at a specific position
Node* deleteAtPos(Node* head, int pos){
    //Previous of node to be deleted
    Node* prev;
    Node* temp = head;

    //If list is empty
    if(temp == nullptr){
        return head;
    }

    //If the head is to be deleted 
    if(pos == 1){
        //Set next node as head
        head = temp->next;
        //Free memory of old head
        delete temp;
        return head;
    }

    //If node is in the middle
    for(int i = 1; i != pos; i++){
        //Traverse the list until pos
        prev = temp;
        temp = temp->next;
    }

    //If pos is found delete the node
    if(temp != nullptr){
        prev->next = temp->next;
        delete(temp);
    }

    //If pos is not found return error message
    else{
        std::cout << "No data";
    }

    return head;
}

//Modify data in linked list

//Convert the linked list to a vector
void linkedListToVector(Node* head, std::vector<int>& vec){
    Node* curr = head;

    for(int i = 0; i <vec.size(); i++){
        vec[i] = curr->data;
        curr = curr->next;
    }
}

//Convert vector to linked list
void vectorToLinkedList(const std::vector<int>& vec, Node* head){
    Node* curr = head;
    for (int i = 0; i < vec.size(); i++){
        curr->data = vec[i];
        curr = curr->next;
    }
}

//Change a value inside the vector
void modifyVector(std::vector<int>& vec){
    for(int i = 0; i < vec.size() / 2; ++i){
        int x = vec[i];
        vec[i] = vec[vec.size() - i - 1] - x;
        vec[vec.size() - i - 1] = x;
    }
}

//Full function to modify the Linked list
Node* modifyTheList(Node* head) {
    if (!head->next) return nullptr;

    // Count the number of nodes
    int n = countNodes(head);

    // Create a vector for the linked list data
    std::vector<int> vec(n);

    // Convert linked list to vector
    linkedListToVector(head, vec);

    // Modify the vector
    modifyVector(vec);

    // Convert vector back to linked list
    vectorToLinkedList(vec, head);

    return head;
}