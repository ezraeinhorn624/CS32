int countIncludes(const std::string a1[], int n1, const std::string a2[], int n2);
void separate(std::string a[], int n, std::string separator, int& firstNotLess, int& firstGreater);
void exchange(std::string& x, std::string& y);
void order(std::string a[], int n);

int countIncludes(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (a2->empty()) return 1;
	int count = 0;
	if (n2 > n1) return 0;
	if (n2 <= 0 || n1 <= 0)
		return 1;
	if (a1[n1 - 1] == a2[n2 - 1]) {
		count += countIncludes(a1, n1 - 1, a2, n2 - 1);
		if (n1!=1) 
			count += countIncludes(a1, n1 - 1, a2, n2);
	}
	else {
		count += countIncludes(a1, n1 - 1, a2, n2);
	}
	return count;
}

void exchange(std::string& x, std::string& y)
{
	std::string t = x;
	x = y;
	y = t;
}

void separate(std::string a[], int n, std::string separator, int& firstNotLess, int& firstGreater)
{
	if (n < 0)
		n = 0;
	firstNotLess = 0;
	firstGreater = n;
	int firstUnknown = 0;
	while (firstUnknown < firstGreater)
	{
		if (a[firstUnknown] > separator)
		{
			firstGreater--;
			exchange(a[firstUnknown], a[firstGreater]);
		}
		else
		{
			if (a[firstUnknown] < separator)
			{
				exchange(a[firstNotLess], a[firstUnknown]);
				firstNotLess++;
			}
			firstUnknown++;
		}
	}
}

void order(std::string a[], int n)
{	
	if (n <= 1) return;
	int firstNotLess = 0, firstGreater = 0;
	separate(a, n, a[n - 1], firstNotLess, firstGreater);
	if (a[n - 1] != a[firstNotLess])
		order(a, n); // separate(a, n, a[n - 1], firstNotLess, firstGreater);
	//if (a[firstNotLess] > a[firstGreater])
		//exchange(a[firstNotLess], a[firstGreater]);
	order(a, n-1);
}