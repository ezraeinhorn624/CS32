class Medium {
public:
	Medium(std::string id) :m_id(id) {}
	virtual ~Medium() {}
	virtual std::string connect() const = 0;
	std::string id() const { return m_id; }
	virtual std::string transmit(std::string message) const {
		std::string result = "text: ";
		result += message;
		return result;
	}
private:
	std::string m_id;
};
class Phone :public Medium {
public:
	~Phone() { std::cout << "Destroying the phone " << this->id() << "." << std::endl; }
	Phone(std::string number, CallType type) :m_type(type), Medium(number) {}
	std::string connect() const { return "Call"; }
	std::string transmit(string message) const {
		std::string result = "";
		if (m_type == VOICE)
			result += "voice: ";
		else
			result += "text: ";
		result += message;
		return result;
	}
private:
	CallType m_type;
};
class TwitterAccount :public Medium {
public:
	~TwitterAccount() { std::cout << "Destroying the Twitter account " << this->id() << "." << std::endl; }
	TwitterAccount(std::string handle) : Medium(handle) {}
	std::string connect() const { return "Tweet"; }
};
class EmailAccount :public Medium {
public:
	~EmailAccount() { std::cout << "Destroying the email account " << this->id() << "." << std::endl; }
	EmailAccount(std::string email) : Medium(email) {}
	std::string connect() const { return "Email"; }
};