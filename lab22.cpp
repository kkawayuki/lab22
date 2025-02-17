// COMSC-210 | lab 22 | Kent Kawashima
// IDE used: Visual Studio Code
#include <iostream>
using namespace std;

// global variables
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
int llSize = 0; // track current number of list elements, (could alternatively exist as a static field of DoublyLinkedList class)

// class
class DoublyLinkedList
{
private:
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
        Node(int val, Node *p = nullptr, Node *n = nullptr)
        {
            data = val;
            prev = p;
            next = n;
        }
    };

    Node *head;
    Node *tail;

public:
    // constructor
    DoublyLinkedList()
    {
        head = nullptr;
        tail = nullptr;
    }

    // methods
    void push_back(int value)
    {
        Node *newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        llSize++;
    }

    void push_front(int value)
    {
        Node *newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        llSize++;
    }

    void insert_after(int value, int position)
    {
        if (position < 0)
        {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node *newNode = new Node(value);
        if (!head)
        {
            head = tail = newNode;
            return;
        }

        Node *temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp)
        {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;

        llSize++;
    }

    /************************************************
     * Function: Deletes a Node member of the
     * DoublyLinkedList class based on user-specified
     * integer input of position of desired deletion
     *
     * Parameters: value, integer corresponding to
     * desired Node deletion location
     * Return: NONE
     ************************************************/
    void delete_pos(int value)
    { // NOTE: assumes user knows that index starts at zero
        if (!head)
            return; // Empty list

        Node *temp = head;

        for (int i = 0; temp, i < value; i++) // traverses through linked list from start if valid, based on value
            temp = temp->next;                // traverse until found

        if (!temp)
            return; // Value not found

        // below code assumes that now temp points to the node to delete
        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Deleting the head
        }

        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Deleting the tail
        }

        llSize--;
        delete temp;
    }

    /************************************************
     * Function: Deletes the first Node member of the
     * DoublyLinkedList class, as long as one exists
     *
     * Parameters: NONE
     * Return: NONE
     ************************************************/
    void pop_front()
    {
        if (!head)
            return; // Empty list

        Node *temp = head;

        if (!temp)
            return; // head not found

        head = temp->next; // Deleting the head
        temp->next->prev = temp->prev;

        llSize--;
        delete temp;
    }

    /************************************************
     * Function: Deletes the last Node member of the
     * DoublyLinkedList class, as long as one exists.
     *
     * Parameters: NONE
     * Return: NONE
     ************************************************/
    void pop_back()
    { // NOTE: assumes user knows that index starts at zero
        if (!head)
            return; // Empty list

        Node *temp = head;

        for (int i = 0; temp, i < llSize - 1; i++) // traverses through linked list from start if valid, based on value
            temp = temp->next;                     // traverse until found

        if (!temp)
            return; // Value not found

        temp->prev->next = temp->next;
        tail = temp->prev; // Deleting the tail

        llSize--;
        delete temp;
    }

    void delete_val(int value)
    {
        if (!head)
            return; // Empty list

        Node *temp = head;
        while (temp && temp->data != value)
            temp = temp->next;

        if (!temp)
            return; // Value not found

        if (temp->prev)
        {
            temp->prev->next = temp->next;
        }
        else
        {
            head = temp->next; // Deleting the head
        }

        if (temp->next)
        {
            temp->next->prev = temp->prev;
        }
        else
        {
            tail = temp->prev; // Deleting the tail
        }

        llSize--;
        delete temp;
    }

    void print()
    {
        Node *current = head;
        if (!current)
            return;
        while (current)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << "\n\n";
    }

    void print_reverse()
    {
        Node *current = tail;
        if (!current)
            return;
        while (current)
        {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << "\n\n";
    }

    // destructor
    ~DoublyLinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

/************************************************
 * Function: Main
 ************************************************/
int main()
{
    DoublyLinkedList list;
    int temp;

    // populate linked list based on MAX_LS
    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    // begin operations

    cout << "List backward: \n";
    list.print_reverse();

    cout << "List forward: \n";
    list.print();

    // Demonstrate position-based node deletion
    cout << "Please input the position of list integer to delete (starting at 1): ";
    cin >> temp;
    if (temp > 0 && temp <= llSize)
    {
        list.delete_pos(temp - 1); // deletes head based on position
        cout << "After deletion: \n";
        list.print();
    }
    else
        cout << "Invalid input, must be within range of 0-" << llSize << ".\n";

    // Demonstrate pop_front() functionality
    cout << "Popping front: \n";
    list.pop_front();
    list.print();

    // Demonstrate pop_back() functionality
    cout << "Popping back: \n";
    list.pop_back();
    list.print();

    // END OF PROGRAM
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    list.print();

    return 0;
}
