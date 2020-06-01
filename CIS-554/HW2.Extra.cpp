//HW2-EC by Bo Li
//SU Net ID: bli158  SUID: 218717316

//CIS554 HW2 Second
//Due: 11:59PM Tuesday ( October 22 )
/*
-   Implement the functions reverse of the DoublyLinkedList class which is sorted in frequency.
The description of the reverse function is given in the class.
-   In the implementation reverse, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.
-   In implementaing reverse, you are not allowed to do sorting from scratch.

When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.  (This means all operations should directly performed on the list.)
*/
#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node* next;
    Node* previous;
    Node(int i) { value = i; next = previous = nullptr; }
    Node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
    Node* head;
    Node* tail;
    DoublyLinkedList() { head = tail = nullptr; }
    DoublyLinkedList(const std::initializer_list<int>& V);
    void printForward();
    void printBackward();


    void reverse();
    /*
    Given an already sorted DoublyLinkedList in frequency (i.e., the result of HW1), make
    the numbers with the same frequency be sorted in decending order.
    For example, 4 9 33 7 7 12 12 6 6 6 will be re-arranged into 33 9 4 12 12 7 7 6 6 6
    */

};


DoublyLinkedList::DoublyLinkedList(const std::initializer_list<int>& V) {
    head = tail = nullptr;
    for (auto& value : V) {
        Node* p1 = new Node(value);
        p1->previous = tail;
        if (tail != nullptr)
            tail->next = p1;
        tail = p1;
        if (head == nullptr)
            head = p1;
    }
}

void DoublyLinkedList::printForward() {
    cout << endl;
    Node* p1 = head;
    while (p1 != nullptr) {
        cout << p1->value << " ";
        p1 = p1->next;
    }
}

void DoublyLinkedList::printBackward() {
    cout << endl;
    Node* p1 = tail;
    while (p1 != nullptr) {
        cout << p1->value << " ";
        p1 = p1->previous;
    }
}

void DoublyLinkedList::reverse() {
    Node *p = head, *p1 = head, *p2;
    Node* p_occurred;

    if ( !head || !head->next ) return; // return if the linked list contains 0 node or 1 node

    int total = 0;
    while (p1) {
        total ++;
        p1 = p1->next;
    }

    for(int i = 1; i < total+1; i++) {      // frequency on each node
        p1 = head;
        Node *p_start = p, *p_end = nullptr;
        int count = 0;
        if (p_start)
            p_start = p;

        while (p1) {
            int freq = 1;
            p_occurred = p1->previous;

            while ( p_occurred ) {   // if p1->value is occurred in its all previous nodes, move p1 to next
                if ( p1->value == p_occurred->value && p1 != tail ) {
                    p1 = p1->next;
                    p_occurred = p1;
                } else if ( p1->value == p_occurred->value && p1 == tail ) {  // if last node is occurred previously, do not count, and exit the loop
                    freq = -1; // do not count
                    break;
                }
                p_occurred = p_occurred->previous;
            }

            p2 = p1->next;
            while ( p2 ) {    // count frequency of each distinctive node
                if ( p2->value == p1->value )
                    freq++;
                p2 = p2->next;
            }

            if (freq == i) {
                count = freq;
                for (int j = 0; j < freq; j++)
                    p = p->next;
            }
            p1 = p1->next;
        }

        if (count != 0 ) {      // sub_list based on same frequency
            if (p && p != head)
                p_end = p->previous;
            else if (p && p == head)
                p_end = head;
            else if (!p)
                p_end = tail;

            if (p_start->value == p_end->value)        // all nodes have same value in current frequency
                continue;
            else {
                Node *p_prev , *p_cur = p_start, *p_next;
                Node *end_next = p_end->next;

                while (p_cur != end_next) {
                    if (p_cur == p_start)
                        p_cur = p_cur->next;

                    p_prev = p_cur->previous;
                    p_next = p_cur->next;

                    if (p_cur->value > p_prev->value) {
                        if (p_prev == p_start)                          // put p_start back to first node of current Freq
                            p_start = p_cur;

                        if (p_prev == head && p_cur != tail) {          // Switch Head  & middle
                            p_cur->next = p_prev;
                            p_prev->previous = p_cur;
                            p_cur->previous = nullptr;
                            head = p_cur;
                            p_prev->next = p_next;
                            p_next->previous = p_prev;
                        }
                        else if (p_prev != head && p_cur != tail) {     // switch middle
                            p_cur->previous = p_prev->previous;
                            p_prev->previous->next = p_cur;
                            p_cur->next = p_prev;
                            p_prev->previous = p_cur;
                            p_prev->next = p_next;
                            p_next->previous = p_prev;
                        }
                        else if (p_prev == head && p_cur == tail) {     // switch head & tail
                            p_cur->next = p_prev;
                            p_prev->previous = p_cur;
                            p_cur->previous = nullptr;
                            p_prev->next = nullptr;
                            head = p_cur;
                            tail = p_prev;
                        }
                        else if (p_prev != head && p_cur == tail) {     // switch tail & middle
                            p_prev->next = p_cur;
                            p_cur->previous = p_prev->previous;
                            p_cur->next = p_prev;
                            p_prev->previous = p_cur;
                            p_prev->next = nullptr;
                            tail = p_prev;
                        }
                        continue;
                    }

                    p_cur = p_cur->next;
                }
            }
        }
    }
}

int main() {

    DoublyLinkedList d{ 1,9,15,2,2,8,8,0,0,0,0,3,3,3,3,3,19,19,19,19,19,11,11,11,11,11,11, 4,4,4,4,4,4,4 };
    d.reverse();

    d.printForward();
    d.printBackward();

    DoublyLinkedList d1{ 1,9,9,9 };
    d1.reverse();

    d1.printForward();
    d1.printBackward();

    DoublyLinkedList d2{ 0,0,3,3,3,4,4,4 };
    d2.reverse();

    d2.printForward();
    d2.printBackward();

    DoublyLinkedList d3{ 8,8,9,9,13,13 };
    d3.reverse();

    d3.printForward();
    d3.printBackward();

    DoublyLinkedList d4{ };
    d4.reverse();

    d4.printForward();
    d4.printBackward();

    DoublyLinkedList d5{ 13,13,13,13,13 };
    d5.reverse();

    d5.printForward();
    d5.printBackward();

    getchar();
    getchar();
    return 0;
}