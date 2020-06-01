//CIS554 HW2
//Due: 11:59PM, Monday ( September 23)
/*
-   Implement two member functions, merge and remove, of the DoublyLinkedList class of HW1.
The descriptions of the two member functions are given below.
-   In the implementation of merge and remove, you are not allowed to modify values of nodes.
You only can modify pointers of nodes.
-   Again, you are not allowed to create new nodes in your implementation.  No external structures (such as arrays,
linked list, map, etc.) are allowed.  You can use some temporary pointes or variables for your
implementation.
-   In implementaing merge and remove, you are not allowed to call sort() in HW1


When you submit your code, do not modify main function.

Do not introduce new functions
In-place implementation is required.  (This means all operations should directly performed on the list.)
*/


/**
 * Instruction:
 *
 *  -> group unsorted list
 *  -> search same node in sorted list, append the nodes.
 *  -> Merge / Remove: Move the cur node into right position of frequency in the sorted list
 * */
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
	void makeRandomList(int m, int n);
	void printForward();
	void printBackward();


	void sort();//sort all values based on frequency in ascending order.
	//In case of ties, the smaller values will appear earlier
	//Example:  for list with values  7 6 12 4 33 12 6 6 7
	//sorted results: 4 33 7 7 12 12 6 6 6



	void merge(DoublyLinkedList& L);
	/*
	Given an already sorted DoublyLinkedList (i.e., the result of HW1) , take
	another unsorted list L as function argument, and merge L into the current
	list to form a single sorted DoublyLinkedList.  The result of merge is a sorted list.
	You are not allowed to invoke sort() in HW1 in your implementation of merge.
	*/

	void remove(int m, int n);
	/*
	Given an already sorted DoublyLinkedList (i.e., the result of the HW1),
	remove n times of value m from the DoublyLinkedList.
	If n is more than the total number of m's in the DoublyLinkedList,
	then remove all m's from the list.
	If m does not exist in the list, then do nothing.
	The result of remove will be a sorted list.
	You are not allowed to invoke sort() in HW1 in your implementation of remove.
	*/
};

void DoublyLinkedList::makeRandomList(int m, int n) {

	for (int i = 0; i < m; i++) {
		Node* p1 = new Node(rand() % n);
		p1->previous = tail;
		if (tail != nullptr) tail->next = p1;
		tail = p1;
		if (head == nullptr) head = p1;
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

void DoublyLinkedList::sort() {
	Node* p1, * p2;
	Node* p_origin;
	Node* p_temp;
	Node* p_occurred;
	Node* p_traverse = head;
	int list_length = 0;
	int cur_value;
	int distinct_node_num = 0;

	while (p_traverse) {  // get length of doubly linked list
		list_length++;
		p_traverse = p_traverse->next;
	}

	if (!head || !head->next) return; // return if the linked list contains 0 node or 1 node

	for (int i = list_length; i > 0; i--) {  // find out frequency of nodes in ascending order
		p1 = head;
		int count = 0;

		while (p1) {  // p1 traverses the entire doubly linked list
			p_occurred = p1->previous;
			int freq = 1;

			while (p_occurred) {   // if p1->value is occurred in its all previous nodes, move p1 to next
				if (p1->value == p_occurred->value && p1 != tail) {
					p1 = p1->next;
					p_occurred = p1;
				}
				else if (p1->value == p_occurred->value && p1 == tail) {  // if last node is occurred previously, do not count, and exit the loop
					freq = -1; // do not count
					break;
				}
				p_occurred = p_occurred->previous;
			}

			p2 = p1->next;  // p2 always indicates the next node of p1
			while (p2) {    // count frequency of each distinctive node
				if (p2->value == p1->value) {
					freq++;
				}
				p2 = p2->next;
			}

			if (freq == i) { // find out nodes by current frequency in ascending order, move them in the front of list
				distinct_node_num++;    // find out number of distinct nodes

				if (p1 == head)
					p_origin = p1;  //  the position of the node pointed by p1 has to be recorded in order to continue to track the entire list
				else
					p_origin = p1->previous;

				cur_value = p1->value;  // record current value pointed by p1

				while (p1) {  // based on current node pointed by p1, track all remnant nodes to find out nodes with current frequency, and move them to the front of list
					if (p1->value == cur_value) {
						if (p1 == head);  // do not move
						else if (p1 == tail) {  // move tail to the front
							tail = p1->previous;
							tail->next = nullptr;

							// put p1 node into head
							p1->next = head;
							head->previous = p1;
							head = p1;
							head->previous = nullptr;

							p1 = tail;
						}
						else {  // move middle nodes to the front
							p_temp = p1->previous;
							p1->previous->next = p1->next;
							p1->next->previous = p1->previous;

							// put p1 node into head
							p1->next = head;
							head->previous = p1;
							head = p1;
							head->previous = nullptr;

							p1 = p_temp;
						}
						count++;    // calculate how many nodes totally in current frequency
					}
					p1 = p1->next;
				}
				p1 = p_origin;
			}
			p1 = p1->next;
		}

		if (count != 0 && count != 1) {     // sort nodes by current frequency
			p1 = head;
			int tracker = 0;    // track nodes based on current frequency
			int temp;
			Node* p_current;

			while (p1) {
				if (tracker < count) {    // number of nodes on current frequency
					p2 = p1->previous;
					p_current = p1;

					while (p2) {  // use p2 to track all previous nodes of current node
						if (p1->value < p2->value) {    // swap if previous node value is larger than current node value
							temp = p1->value;
							p1->value = p2->value;
							p2->value = temp;

							p1 = p2;
						}
						p2 = p2->previous;
					}
				}
				else    // break to avoid tracking useless nodes
					break;

				p1 = p_current;
				tracker++;
				p1 = p1->next;
			}
		}
	}

}

void DoublyLinkedList::merge(DoublyLinkedList& L) {
	cout << endl;
	Node* l1 = L.head, * l2;

	if (L.head == nullptr) return;
	if (head == nullptr) return;

	while (l1) {    // group unsorted list based on nodes frequency
		bool exist = false;
		Node* p1 = head, * p2;
		Node* pass_1;
		Node* start_l = l1;
		Node* start = head, * next_node, * end = head;

		l2 = l1->next;

		while (l2) {    // find frequency of each distinct node by its value
			if (l2->value == l1->value && l1->value != l1->next->value) {   // find duplicate nodes by value
				Node* l3;   // record the current position of l2->next->previous, in order that l2 keep moving to next node

				// move duplicated node after l1
				if (l2 == L.tail) {
					l3 = l2;

					L.tail = l2->previous;  // position of L.tail
					L.tail->next = nullptr;

					l2->next = l1->next;
					l1->next->previous = l2;
					l1->next = l2;
					l2->previous = l1;
				}
				else {
					l3 = l2->previous;

					l2->previous->next = l2->next;
					l2->next->previous = l2->previous;

					l2->next = l1->next;
					l1->next->previous = l2;
					l1->next = l2;
					l2->previous = l1;
				}
				l1 = l2;
				l2 = l3;
			}
			else if (l2->value == l1->value && l1->value == l1->next->value) {   // move pointers if there are two same consecutive nodes
				l1 = l1->next;
				l2 = l1;
			}

			l2 = l2->next;
		}

		pass_1 = l1->next;  // record the position of next of l1 indicated to

		while (p1) {  // find corresponding nodes in sorted list
			if (start_l->value == p1->value) { // only one single distinct node in unsorted list
				start = p1;
				exist = true;
				if (p1 == tail) {
					start_l->previous = tail;
					tail->next = start_l;
					tail = l1;
					tail->next = nullptr;
				}
				else {
					l1->next = p1->next;
					p1->next->previous = l1;
					p1->next = start_l;
					start_l->previous = p1;
				}
				break;
			}
			p1 = p1->next;
		}

		if (!exist) {    //  node of Unsorted list Does Not exist in Sorted List, put it to head of sorted list
			l1->next = head;
			head->previous = l1;
			head = start_l;

			start = head;
		}

		int freq = 0;
		next_node = start;

		while (next_node->value == start->value) {  // get each partition of each distinct group
			freq++; // frequency of each updated node in sorted list

			if (next_node != tail) {
				next_node = next_node->next;
				end = next_node->previous;
			}
			else {    // next_node reach to tail
				end = next_node;
				break;
			}
		}

		if (start == head) {   // Disconnect matched group nodes in sorted list
			head = end->next;
			head->previous = nullptr;
		}
		else if (end == tail) {
			tail = start->previous;
			tail->next = nullptr;
		}
		else {
			start->previous->next = end->next;
			end->next->previous = start->previous;
		}

		p1 = head; // init p1 to head of sorted list

		while (p1) {
			p2 = p1;
			Node* p_start = p1, * p_end;
			int sorted_freq = 0;

			while (p2) {  // each distinct nodes frequency
				if (p2->value == p1->value)
					sorted_freq++;
				else {
					p1 = p2->previous;
					break;
				}

				if (p2 == tail && p2->value == p1->value)   // p2 reaches to tail, if it's still in group, jump p1 to tail
					p1 = p2;

				p2 = p2->next;
			}

			p_end = p1; // end of node of current group

			//!! Determine where need to put in by current node group

			//!! freq:          Selected node's freq
			//!! sorted_freq    different group node's freq

			//!! startï¼?        Selected group node -> start node
			//!! end:           Selected group node -> end node

			//!! p_start:       sorted node -> start node
			//!! p_end:         sorted node -> end node

			if (freq > sorted_freq) { // move next, insert into back side
				if (p_end == tail) {    // insert group into tail position
					p_end->next = start;
					start->previous = p_end;
					tail = end;
					tail->next = nullptr;

					p1 = tail; // end p1 loop
				}
				else
					p1 = p_end; // jump to next group
			}
			else if (freq == sorted_freq) { // same freq
			 //!! Compare Values by nodes
				if (start->value > p_start->value) {  // insert group into tail position
					if (p_end == tail) {
						p_end->next = start;
						start->previous = p_end;
						tail = end;
						tail->next = nullptr;

						p1 = tail; // end p1 loop
					}
				}
				else if (start->value < p_start->value) {
					if (p_start == head) {  // insert group into head position
						p_start->previous = end;
						end->next = p_start;
						head = start;
						head->previous = nullptr;
					}
					else {
						start->previous = p_start->previous;
						p_start->previous->next = start;
						end->next = p_start;
						p_start->previous = end;
					}

					p1 = tail; // end p1 loop
				}
			}
			else {    // insert in front of node
				if (p_start == head) {  // insert group into head position
					end->next = p_start;
					p_start->previous = end;
					head = start;
					head->previous = nullptr;
				}
				else {
					end->next = p_start;
					start->previous = p_start->previous;
					start->previous->next = start;
					p_start->previous = end;
				}

				p1 = tail;  // end p1 loop
			}
			//!! end if

			p1 = p1->next;
		}

		l1 = pass_1;
	}
}

void DoublyLinkedList::remove(int m, int n) {
	Node* p1 = head, * p2;
	Node* start = nullptr, * end = nullptr;
	int count = 0;
	int freq = 1;

	if (n <= 0) return; // do nothing if n <= 0

	while (p1) {
		if (p1 == tail && p1->value != m)   // m does not exist, do nothing
			return;
		else if (m != p1->value)
			p1 = p1->next;
		else
			break;
	}

	p1 = head;  // init p1
	while (p1) {    // number of current node
		if (m == p1->value)
			count++;
		p1 = p1->next;
	}

	p1 = head;  // init p1
	while (p1) {    // start position
		if (m == p1->value) {
			start = p1;
			break;
		}
		p1 = p1->next;
	}

	p1 = head;  // init p1
	while (p1) {     // end position
		if (m == p1->value)
			end = p1;

		p1 = p1->next;
	}

	if (n >= count && count > 0) {   // remove all since n >= m.length
		//!! 3 cases -> head / tail / middle
		if (m == head->value) {   // remove head group
			head = end->next;
			head->previous = nullptr;
		}
		else if (m == tail->value) {  // remove tail group
			tail = start->previous;
			tail->next = nullptr;
		}
		else {
			start->previous->next = end->next;
			end->next->previous = start->previous;
		}
	}
	else if (n < count && count > 0) {    // remove number of nodes.
		int i = 0;
		Node* position = start;   // move position to next based on how many nodes will be remove

		while (i < n) {
			position = position->next;
			i++;
		}

		if (position != tail) { // node group which is going to be removed
			start->previous->next = position;
			position->previous = start->previous;
			start = position;
		}
		else {
			tail = start;
			tail->next = nullptr;
			end = start;
		}

		Node* p3 = start;

		while (p3 != end) {  // freq of the Remain of selected group
			freq++;
			p3 = p3->next;
		}

		if (start == head) {    // disconnect group from list
			head = end->next;
			head->previous = nullptr;
		}
		else if (end == tail) {
			tail = start->previous;
			tail->next = nullptr;
		}
		else {
			start->previous->next = end->next;
			end->next->previous = start->previous;
		}

		p1 = head;  // init p1
		while (p1) {
			Node* p_start = p1, * p_end;
			p2 = p1;

			int sorted_freq = 0;

			while (p2) {  // each distinct nodes frequency
				if (p2->value == p1->value)
					sorted_freq++;
				else {
					p1 = p2->previous;
					break;
				}

				if (p2 == tail && p2->value == p1->value)   // p2 reaches to tail, if it's still in group, jump p1 to tail
					p1 = p2;

				p2 = p2->next;
			}
			p_end = p1;

			//!! Determine where we need to put selected group in

			//!! freq:          Selected node's freq
			//!! sorted_freq    different group node's freq

			//!! startï¼?        Selected group node -> start node
			//!! end:           Selected group node -> end node

			//!! p_start:       sorted node -> start node
			//!! p_end:         sorted node -> end node

			if (freq > sorted_freq) { // move next, insert into back side

				if (p_end == tail) {    // insert group into tail position
					p_end->next = start;
					start->previous = p_end;
					tail = end;
					tail->next = nullptr;

					p1 = tail; // end p1 loop
				}
				else
					p1 = p_end; // jump to next group

			}
			else if (freq == sorted_freq) { // same frequency
			 //!! Compare Values by nodes
				if (start->value > p_start->value) {  // insert group into tail position
					if (p_end == tail) {
						p_end->next = start;
						start->previous = p_end;
						tail = end;
						tail->next = nullptr;

						p1 = tail; // end p1 loop
					}

				}
				else if (start->value < p_start->value) {
					if (p_start == head) {  // insert group into head position
						p_start->previous = end;
						end->next = p_start;
						head = start;
						head->previous = nullptr;
					}
					else {
						start->previous = p_start->previous;
						p_start->previous->next = start;
						end->next = p_start;
						p_start->previous = end;
					}

					p1 = tail; // end p1 loop
				}

			}
			else {    // insert in front of node

				if (p_start == head) {  // insert group into head position
					end->next = p_start;
					p_start->previous = end;
					head = start;
					head->previous = nullptr;

				}
				else {
					end->next = p_start;
					start->previous = p_start->previous;
					start->previous->next = start;
					p_start->previous = end;
				}

				p1 = tail;  // end p1 loop
			}
			//!! end If

			p1 = p1->next;
		}
	}
}

int main() {
	DoublyLinkedList d1, d2;
	d1.makeRandomList(2, 1);
	d1.printForward();
	d1.printBackward();

	d1.sort();
	d1.printForward();
	d1.printBackward();

	d2.makeRandomList(2, 3);
	d1.printForward();
	d1.printBackward();

	d1.merge(d2);
	d1.printForward();
	d1.printBackward();

	d1.remove(0, 3);
	d1.printForward();
	d1.printBackward();
	getchar();
	getchar();
	return 0;
}