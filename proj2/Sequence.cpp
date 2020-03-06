#include "Sequence.h"

Sequence::Sequence() {
	head = nullptr; //the only thing that needs to be declared...
}

Sequence::~Sequence() {
	//while (head->next != nullptr) { //loop through every node and erase it
	//	head->next = head->next->next;
	//	if (head->next->next!=nullptr)
	//		head->next->next->prior = head->next;
	//}
	//if (head->next == nullptr)
	//	head = nullptr;
	node* a = head;
	while (a != nullptr) {
		node* b = a->next;
		delete a;
		a = b;
	}
}

Sequence::Sequence(const Sequence &other) {
	*this = other;
}

Sequence& Sequence::operator = (const Sequence& other) {
	while (this->head != nullptr) erase(0);
	if (other.head == nullptr) {
		this->head = nullptr;
		return *this;
	}
	node* n = new node;
	n = other.head;
	this->head = n;
	node* p = this->head;
	if (p->next == nullptr) return *this;
	node*ptr2 = other.head->next;
	int place = 1;
	for (int i = 0; i < other.size(); i++) {//head = other.head; // FOR JONOTHAN wouldn't this just *point* to the sequece, not copy it? 
		/*if (ptr2 == nullptr) break;
		p->next = new node;
		p->next = ptr2;
		p = p->next;
		ptr2 = ptr2->next;*/
		insert(place, ptr2->data);
		ptr2 = ptr2->next;
		place++;
	}
	return *this;
}

bool Sequence::empty() const {
	if (size() == 0) return true;
	return false;
}

int Sequence::size() const {
	int s = 0;
	node* npr = head;
	while (npr != nullptr) {
		s++;
		npr = npr->next;
	}
	return s;
}

int Sequence::insert(int pos, const ItemType& value) {
	if (pos < 0 || pos > size()) return -1;
	node* n = new node;
	n->data = value;
	n->next = nullptr;
	n->prior = nullptr;
	if (size() == 0||pos==0) {
		n->next = head;
		head = n;
		return 0;
	}
	node* ptr1 = head;
	for (int i = 1; i < pos; i++) {
		ptr1 = ptr1->next;
	}
	n->next = ptr1->next;
	n->prior = ptr1;
	ptr1->next = n;
	return pos;
}

int Sequence::insert(const ItemType& value) {
	int p = 0;
	node* ptr = head;
	for (int i = 0; i < size(); i++) {
		if (ptr->data >= value) {
			break;
		}
		ptr = ptr->next;
		p++;
	}
	insert(p, value);
	return p;
	
	//node* n = new node; //create the node that will later be inserted
	//n->data = value;
	//n->prior = nullptr;
	//n->next = nullptr;
	//if (head == nullptr) {
	//	head = n;
	//	return 0;
	//}
	//node* ptr = head;
	//for (int i = 1; i < size(); i++) { //loop through the remaining items in sequence
	//	if (value <= ptr->data) { //actually do the insertion
	//		n->next = ptr;
	//		n->prior = ptr->prior;
	//		ptr->prior->next = n;
	//		ptr->prior = n;
	//		return (i - 1); //return where it was inserted, not where it found a match
	//	}
	//	ptr = ptr->next;
	//}
	//ptr->next = n; //if loop didn't find a match, insert at the end
	//n->prior = ptr;
	//return (size()-1);
}

bool Sequence::erase(int pos) {
	if (pos < 0 || pos >= size()) return false;
	node* p = head;
	if (size() == 1) {
		delete p;
		head = nullptr;
		return true;
	}
	if (pos == 0) {
		node* ptr1 = head->next;
		delete p;
		head = ptr1;
		return true;
	}
	if (size() == 2) {
		//if this is the case and the prior if didn't run, then pos==1...
		node* ptr2 = head->next;
		delete ptr2;
		head->next = nullptr;
		return true;
	}
	for (int i = 0; i < pos; i++) {
		p = p->next;
	}
	node* before = p->prior;
	node* after = p->next;
	//node* ptr1 = nullptr;
	delete p;
	before->next = after;
	if (after != nullptr) after->prior = before;
	return true;
}

int Sequence::remove(const ItemType& value) {
	int r = 0;
	node* p = head;
	for (int i = 0; i < size() && p!=nullptr;) {
		if (p->data == value) {
			if (p->prior == nullptr) {
				if (p->next == nullptr) head = nullptr;
				head = p->next;
				r++;
			}
			else if (p->next == nullptr) {
				p->prior->next = nullptr;
				r++;
				break;
			}
			else {
				p->prior->next = p->next;
				p->next->prior = p->prior;
				r++;
			}
		}
		else i++;
		p = p->next;
	}
	return r;
}

bool Sequence::get(int pos, ItemType& value) const {
	if (pos < 0 || pos >= size()) return false;
	node* p = head;
	for (int i = 0; i < pos && p->next!=nullptr; i++) {
		p = p->next;
	}
	value = p->data;
	return true;
}

bool Sequence::set(int pos, const ItemType& value) {
	if (pos < 0 || pos >= size()) return false;
	node* p = head;
	for (int i = 0; i < pos && p != nullptr; i++) {
		p = p->next;
	}
	p->data = value;
	return true;
}

int Sequence::find(const ItemType& value) const {
	int p = -1;
	node* ptr = head;
	for (int i = 0; i < size() && ptr != nullptr; i++) {
		if (ptr->data == value) {
			p = i;
			break;
		}
		ptr = ptr->next;
	}
	return p;
}

void Sequence::swap(Sequence& other) {
	node* ptr = other.head;
	other.head = this->head;
	this->head = ptr;

}
// Exchange the contents of this sequence with the other one.