//HW6 by Bo Li

//CIS554 HW6   Due: 11:59PM, Friday, Nov. 8.
#include <iostream>
#include <memory>
#include <math.h>

using namespace std;

class node {
public:
	int value;
	shared_ptr<node> right;
	shared_ptr<node> l_child;
	shared_ptr<node> r_child;
	node() {}
	node(int i) { value = i; }
};

class tree {
public:
	shared_ptr<node> root;
	int level;
	tree() { level = 0; }

	//Implement all member functions below
	tree(int n);//constructor for n-level tree
	//and initilize values as shown in the diagram; 0, 1, 2, ...
	//Note that root node is at level 1 and its value will be initialized to 0

	tree(const tree& T);//copy constructor
	~tree();//destructor

	tree(tree&& T); //move constructor

	tree(const initializer_list<int>& V);//The first number in V is tree level;
	//the rest are values from top to bottom and from left to right
	//For example, to create the tree with n=3 in the diagram,
	//tree T1 = {3, 0,1,2,3,4,5,6}; //where the first 3 is tree level, and the rest are values

	void operator= (const tree& R);//L-value operator=

	void operator= (tree&& R); //R-value operator=

	tree ThreeTimes(); //return a tree with all node value being three times 
	friend ostream& operator<<(ostream& str, const tree& T);

	int sum(shared_ptr<node> p);//sum of node values in sub-tree rooted at p
	void delete_level(int i); // Delete nodes at level i. Some nodes at level(s) higher
	//than i will also be deleted accordingly. As described in class.  (Also see the
	//example in the main function.)

	shared_ptr<node> find(int i); //find the first node with value i and return
	//its address; if not found, return nullptr;
};

ostream& operator<<(ostream& str, const tree& T) {
	shared_ptr<node> p = T.root;

	while (p) {
		str << p->value << " ";
		p = p->right;
		if (p == T.root)
			break;
	}
	return str;
}

tree::tree(int n) {
	if (n == 0) return;	// out of scope
	if (n == 1) {	// Root
		root = make_shared<node>(0);
		root->right = root;
	} else {
		int total_nodes = pow(2, n) - 1;
		root = make_shared<node>(0);
		auto p = root;

		for (int i = 1; i < total_nodes; i++) {
			shared_ptr<node> np = make_shared<node>(i);

			p->right = np;
			p = np;
		}
		p->right = root;	// last Node->right indicates to root
		p.reset();
		
		// generate tree
		p = root;
		auto p1 = p->right;

		while (p) {
			while (p1) {		// connect node with its child
				p->l_child = p1;
				p1 = p1->right;
				p->r_child = p1;
				p1 = p1->right;
				break;
			}
			if (p1 == root) {
				p1.reset();
				break;
			}
		
			p = p->right;
		}
		p.reset();
	}
}

tree::tree(const initializer_list<int>& V) : tree() {
	auto it = V.begin();
	level = *it;
	int total_nodes = pow(2, level) - 1;
	int count = 0;

	it++;
	while (it != V.end()) {
		count++;
		it++;
	}
	if (total_nodes != count) return;		// level has to be matched with number of nodes

	it = V.begin();	// reset it
	it++;

	if (total_nodes == 1) {
		shared_ptr<node> p = make_shared<node>(*it);
		root = p;
		root->right = root;
		p->right = p;
	} else {		
		root = make_shared<node>(*it);	// set root
		auto p = root;
		it++;
		while (it != V.end()) {		// connect all nodes by right smart ptr
			shared_ptr<node> np = make_shared<node>(*it);
			p->right = np;
			p = np;

			it++;
		}
		p->right = root;
		p.reset();

		// generate tree
		p = root;
		auto p1 = p->right;

		while (p) {
			while (p1) {		// connect node with its child
				p->l_child = p1;
				p1 = p1->right;
				p->r_child = p1;
				p1 = p1->right;
				break;
			}
			if (p1 == root) {
				p1.reset();
				break;
			}

			p = p->right;
		}
		p.reset();
	}
}

tree::~tree() {		
	auto p = root;
	while (p) {
		p = p->right;
		if (p->right == root) {
			p->right.reset();
			break;
		}
	}

	p.reset();
	root.reset();
}

tree::tree(const tree& T) : tree() {	// copy constructor
	if (!T.root) return;

	level = T.level;
	auto p1 = T.root;			// need to be reset
	root = make_shared<node>(*p1);

	if (T.root->right == T.root) 	// number of level 1
		root->right = root;
	else {				
		p1 = p1->right;
		auto p = root;

		while (p1) {
			p->right = make_shared<node>(*p1);
			p = p->right;

			p1 = p1->right;

			if (p1 == T.root) {
				p->right = root;
				p.reset();
				p1.reset();
				break;
			}
		}

		// generate tree
		p = root;
		auto p1 = p->right;

		while (p) {
			while (p1) {		// connect node with its child
				p->l_child = p1;
				p1 = p1->right;
				p->r_child = p1;
				p1 = p1->right;
				break;
			}
			if (p1 == root) {
				p1.reset();
				break;
			}

			p = p->right;
		}
		p.reset();
	}
}

tree::tree(tree&& T) : tree()  { // move constructor
	if (!T.root) return;

	level = T.level;
	root = T.root;
	T.root.reset();
}

void tree::operator= (const tree& R) { //L-value operator=
	if (!R.root) return;
	
	// Clear buffer
	auto p = root;
	while (p) {
		p = p->right;
		if (p->right == root) {
			p->right.reset();
			break;
		}
	}
	p.reset();
	root.reset();

	// Copy
	level = R.level;
	auto p1 = R.root;			// need to be reset
	root = make_shared<node>(*p1);

	if (R.root->right == R.root) 	// number of level 1
		root->right = root;
	else {
		p1 = p1->right;
		auto p = root;

		while (p1) {
			p->right = make_shared<node>(*p1);
			p = p->right;

			p1 = p1->right;

			if (p1 == R.root) {
				p->right = root;
				p.reset();
				p1.reset();
				break;
			}
		}

		// generate tree
		p = root;
		auto p1 = p->right;

		while (p) {
			while (p1) {		// connect node with its child
				p->l_child = p1;
				p1 = p1->right;
				p->r_child = p1;
				p1 = p1->right;
				break;
			}
			if (p1 == root) {
				p1.reset();
				break;
			}

			p = p->right;
		}
		p.reset();
	}
}

void tree::operator= (tree&& R) {	//R-value operator=
	// Clear buffer
	auto p = root;
	while (p) {
		p = p->right;
		if (p->right == root) {
			p->right.reset();
			break;
		}
	}
	p.reset();
	root.reset();

	level = R.level;
	root = R.root;
	R.root.reset();
}

tree tree::ThreeTimes() {
	int total_nodes = pow(2, level) - 1;
	tree temp(level);
	temp.level = level;
	auto p = root;
	auto p1 = temp.root;

	while(p1) {
		p1->value = (p->value) * 3;
		p1 = p1->right;
		p = p->right;

		if (p == root)
			break;
	}

	return temp;
}

shared_ptr<node> tree::find(int i) {			
	auto p = root;
	while (p) {
		if (p->value == i)
			break;
		
		p = p->right;
		if (p->right == root) {	
			p.reset();
			return nullptr;
		}
	}

	return p;
}

int tree::sum(shared_ptr<node> p) {	// using recursive
	if (p == nullptr)
		return 0;
	return (p->value + sum(p->l_child) + sum(p->r_child));
}

void tree::delete_level(int i) {
	if (i < 2 || i > level) abort();	// first level cannot be delete

	auto p1 = root;
	auto p = root;

	for (int j = 0; j < pow(2, i - 1) - 2; j++) {		// level i - 1
		p1 = p1->right;
	}

	for (int j = 0; j < pow(2, i) - 2 ; j++) {		// level i			
		p = p->right;
	}

	if (p->right == root) {	// delete leaf level
		auto p2 = p1->right;
		p1->right = root;
		p->right = p2;
		p2->right.reset();
	}
	else {		// delete level in the middle
		auto p_f = p1->right;
		p1 = root;

		for (int j = 0; j < pow(2, i - 2) - 1 ; j++) {	// first node of i-1 level
			p1 = p1->right;
		}
	
		for (int j = 0; j < pow(2, i - 1)/2; j++) {	// connect i-1 level to i+1 level
			p1->l_child = p1->l_child->l_child;
			p1->r_child = p1->r_child->l_child;

			if (j == pow(2, i - 1)/2 - 1) {
				p1->right = p->right;
				break;
			}

			p1 = p1->right;
		}

		// remove level i
		for (int j = 0; j < pow(2, i)/2; j++) {
			p_f->l_child = nullptr;
			p_f = p_f->right;
		}
		p->right = nullptr;
		
		// reconnect level after i
		auto fst = p_f;
		int skip = 0;
		auto last_node = p_f;
		shared_ptr<node> tracker;

		for (int j = i + 1; j <= level; j++) {
			tracker = p_f;
			int s = pow(2, skip);

			for (int k = 0; k < pow(2, j) / 2 - 1; k++)		// last node of level i+1
				last_node = last_node->right;

			while (tracker != last_node) {			
				for (int k = 0; k < s - 1; k++)		// based on current level, skip number of nodes for p_f
					p_f = p_f->right;
				
				tracker = p_f->right;

				for (int k = 0; k < s - 1; k++)
					tracker = tracker->right;

				p_f->right = tracker->right;
				tracker->right = nullptr;

				p_f = p_f->right;

				if (p_f == root)
					break;
			}

			if (tracker == last_node)
				tracker->right = nullptr;

			last_node = p_f;
			skip++;
		}
	}
}

int main() {
	tree T1(3);

	cout << T1 << endl; //will print 0 1 2 3 4 5 6

	tree T2 = { 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24 };
	cout << T2 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T3(T2);
	cout << T3 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	tree T4;
	T4 = T3;
	cout << T4 << endl; //will print 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24

	T4 = T3.ThreeTimes();
	cout << T4 << endl;//will print 30 33 36 39 42 45 48 51 54 57 60 63 66 69 72

	T4.delete_level(3);
	cout << T4 << endl;//will print 30 33 36 51 57 63 69

	cout << T3.sum(T3.find(12)) << endl; //will print 133



	getchar();
	getchar();
	return 0;
}

