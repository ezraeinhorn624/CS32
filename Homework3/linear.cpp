bool allTrue(const std::string a[], int n);
int countFalse(const std::string a[], int n);
int firstFalse(const std::string a[], int n);
int indexOfLeast(const std::string a[], int n);
bool includes(const std::string a1[], int n1, const std::string a2[], int n2);

bool allTrue(const std::string a[], int n)
{
	if (n<=0);
	else if (!somePredicate(a[n-1]))
		return false;
	else if (!allTrue(a, n - 1))
		return false;
	return true;
}

int countFalse(const std::string a[], int n)
{
	int c = 0;
	if (n <= 0)
		return c;
	else if (!somePredicate(a[n - 1]))
		c++;
	c += countFalse(a, n - 1);
	return c;
}

int firstFalse(const std::string a[], int n)
{
	int c = -1;
	if (n <= 0)
		return c;
	if (!somePredicate(a[n - 1]))
		c = n - 1;
	if (firstFalse(a, n - 1) != -1)
		c = firstFalse(a, n - 1);
	return c;
}

int indexOfLeast(const std::string a[], int n)
{
	if (n <= 0) {
		return -1;
	}
	if (n == 1) {
		return 0;
	}
	int min = 0;
	if (n == 2) {
		if (a[0] > a[1])
			return 1;
		else
			return 0;
	}
	if (a[indexOfLeast(a, n - 1)] <= a[n - 1])
		min = indexOfLeast(a, n - 1);
	else
		min = n - 1;
	return min;
}

bool includes(const std::string a1[], int n1, const std::string a2[], int n2)
{
	if (n2 <= 0) return true;
	if (n2 > n1) return false;
	if (a1[n1 - 1] == a2[n2 - 1])
		return includes(a1, n1 - 1, a2, n2 - 1);
	return includes(a1, n1 - 1, a2, n2);
}