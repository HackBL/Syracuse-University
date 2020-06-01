//HW3 by Bo Li
//SU Net ID: bli158  SUID: 218717316

#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	course() {}
	course(string n, int s, int c) { name = n; section = s; credits = c; }
	//Add additional needed member functions and implement them.
	//You also need to implement some needed functions for overloading operator<< .

	bool operator==(const course& c) const {
		return name == c.name && section == c.section && credits == c.credits;
	}

	bool operator>(const course& c) const {
		return name > c.name;
	}
};
//Implement the following functions

void add_student(map<int, map<int, list<course*>* > >& DB, int id);
void remove_student(map<int, map<int, list<course*>* > >& DB, int id);
void add_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
void drop_course(map<int, map<int, list<course*>* > >& DB, int semester, int id, course c);
void print_student_semester_courses(map<int, map<int, list<course*>* > >& DB, int semester, int id);
void print_student_all_courses(map<int, map<int, list<course*>* > >& DB, int id);
void print_DB(map<int, map<int, list<course*>* > >& DB);

//For the print functions, you need to add more functions to overload operator<<.
//for example print_DB is simply cout << DB;
//Courses in a semester are sorted alphabetically.

ostream& operator<<(ostream& str, const map<int, map< int, list<course*>*> >& V) {
	for (auto i : V) {  // print id
		str << "student id = " << i.first << endl;

		map<int, list<course*>*> sms = i.second;

		for (auto j : sms) { // print semester
			str << "semester = " << j.first << endl;

			list<course*> ::iterator crs;
			list<course*>* lst = j.second;
			crs = lst->begin();

			while (crs != lst->end()) { // print course
				str << (*crs)->name << " " << (*crs)->section << " " << (*crs)->credits << " ";
				crs++;
			}
			str << endl;
		}
	}

	return str;
}

ostream& operator<<(ostream& str, const map<int, list<course*>*>& V) {  // print semesters & courses
	for (auto i : V) {
		str << "semester = " << i.first << endl;

		list<course*> ::iterator crs;
		list<course*>* lst = i.second;
		crs = lst->begin();

		while (crs != lst->end()) {
			str << (*crs)->name << " " << (*crs)->section << " " << (*crs)->credits << " ";
			crs++;
		}
		str << endl;
	}
	return str;
}

ostream& operator<<(ostream& str, const list<course*>& V) { // print courses
	for (auto i : V)
		str << i->name << " " << i->section << " " << i->credits << " ";
	str << endl;
	return str;
}

int main() {
	//Do not change code for main function
	map<int, map<int, list <course*>*> > DB;
	add_student(DB, 11111);
	course C1("CIS554", 1, 3), C2("CSE674", 1, 3), C3("MAT296", 8, 4), C4("WRT205", 5, 3);

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111);

	add_course(DB, 20172, 11111, C2);
	add_course(DB, 20172, 11111, C4);
	add_course(DB, 20172, 11111, C3);
	add_course(DB, 20172, 11111, C1);
	print_student_all_courses(DB, 11111);

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C4);
	add_course(DB, 20171, 11112, C3);
	add_course(DB, 20171, 11112, C1);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C2);
	add_course(DB, 20172, 11112, C4);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);
	print_student_all_courses(DB, 11112);
	print_DB(DB);
	remove_student(DB, 11111);
	print_DB(DB);
	getchar();
	getchar();
	return 0;
}

void add_student(map<int, map<int, list<course*>* > >& DB, int id) {
	if (DB.find(id) != DB.end())    return; // if student exists, do not need to add

	map<int, list<course*>*> L;
	DB[id] = L;
}

void remove_student(map<int, map<int, list<course*>* >>& DB, int id) {
	if (DB.find(id) == DB.end()) return;    // do nothing if student does not exixt

	map<int, list<course*>*> sms = DB[id];
	map<int, list<course*>*> ::iterator smsItr;
	smsItr = sms.begin();

	while (smsItr != sms.end()) {   // access map<int, list<course*>*>
		int semester = smsItr->first;

		list<course*>* lst = smsItr->second;
		list<course*> ::iterator crs;
		crs = lst->begin();

		while (crs != lst->end()) { // access list<course*>*
			auto temp = next(crs);		// iterate to next course*
			delete* crs;    // delete course* to release memory
			DB[id][semester]->erase(crs);   // remove courses

			crs = temp;	// instead of using c++, will cause increment err
		}
		delete DB[id][semester];    // delete list* to release memory
		DB[id].erase(semester);     // erase map<int, list<course*>*>

		smsItr++;
	}

	DB.erase(id);
}

void add_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {
	if (DB.find(id) == DB.end()) return;    // do nothing if student does not exist

	auto crs = new course(c);   // Dynamically create mem alloc for course
	if (DB.find(id)->second.find(semester) == DB.find(id)->second.end()) {    // add semester & course if cur semester does not exist
		auto L = new list<course*>;
		L->insert(L->begin(), crs);

		DB[id][semester] = L;
	}
	else {    // add course into cur semester & sort by course.name
		list<course*>* lst = DB[id][semester];
		list<course*>::iterator itr;

		itr = lst->begin();
		while (itr != lst->end()) {     // do nothing if course exist
			if (*(*itr) == c) {
				delete crs;     // delete course* to release memory
				return;
			}
			itr++;
		}

		itr = lst->begin();
		while (itr != lst->end()) { // sort course by name
			if (c > (*(*itr))) {
				if (next(itr) != lst->end()) {   // itr next is not end()
					itr++;
					continue;
				}
				else {   // insert c into back of list
					DB[id][semester]->insert(next(itr), crs);
					break;
				}
			}
			else {    // insert c into right position
				DB[id][semester]->insert(itr, crs);
				break;
			}
		}
	}
}

void drop_course(map<int, map<int, list<course*>* >>& DB, int semester, int id, course c) {
	bool exist = false;

	list<course*> ::iterator crs;
	auto lst = DB[id][semester];

	crs = lst->begin();
	while (crs != lst->end()) { // drop selected course
		auto temp = next(crs);	// iterate to next course*

		if (*(*crs) == c) { // delete course memory & remove course from list
			exist = true;
			delete* crs;    // delete course* to release memory
			DB[id][semester]->erase(crs);
		}
		crs = temp;	// instead of using c++, will cause increment err 
	}

	if (!exist) // do nothing if course does not exist
		return;
}

void print_student_semester_courses(map<int, map<int, list<course*>* >>& DB, int semester, int id) {
	if ((DB.find(id) == DB.end())   // do nothing if semester or student does not exist
		|| (DB.find(id)->second.find(semester) == DB.find(id)->second.end()))
		return;

	cout << "student id = " << DB.find(id)->first << endl;
	cout << "semester = " << DB[id].find(semester)->first << endl;
	cout << *(DB[id][semester]) << endl;
}

void print_student_all_courses(map<int, map<int, list<course*>* >>& DB, int id) {
	if (DB.find(id) == DB.end()) return;    // do nothing if student does not exist

	cout << "student id = " << DB.find(id)->first << endl;
	cout << DB[id] << endl;
}

void print_DB(map<int, map<int, list<course*>* >>& DB) {
	if (DB.empty()) return;
	cout << DB << endl;
}

//Some additional functions for overloading operator<<


/*
//Your output needs to keep the identical format
//Sample Screenshot
student id = 11111
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3   MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11111
semester = 20171
CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3

student id = 11112
semester = 20171
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
semester = 20172
CIS554 1 3  CSE674 1 3  MAT296 8 4  WRT205 5 3
*/