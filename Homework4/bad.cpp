void removeBad(list<Movie*>& li)
{
	int m_size = li.size();
	list<Movie*> li2;
	while (li.size() != 0) {
		Movie* ptr = li.front();
		li.pop_front();
		if (ptr->rating() < 55) {
			delete ptr;
		}
		else {
			li2.push_back(ptr);
		}
	}
	li.swap(li2);
}