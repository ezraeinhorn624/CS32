void removeOdds(vector<int>& v)
{
	vector<int>::iterator ptr = v.begin();
	while (ptr != v.end()) {
		if (*ptr % 2 = 1)
			ptr = v.erase(ptr);
		else ptr++;
	}
}