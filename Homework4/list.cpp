void listAll(const Domain* d, string path) // two-parameter overload
{
	if (d->subdomains().empty()) {
		cout << path << endl;
		return;
	}
	
	vector<Domain*> v = d->subdomains();
	int size = v.size();
	string label = path;
	for (int i = 0; i < size; i++) {
		if (path != "")listAll(v[i], v[i]->label() + '.' + path);
		else listAll(v[i], v[i]->label());
	}
}