#include <iostream>
#include <string>
using namespace std;

enum CallType {
	VOICE, TEXT
};
//====================================================
//Your declarationsand implementations would go here==
//====================================================
/*
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
	~Phone() { cout << "Destroying the phone " << this->id() << "." << endl; }
	Phone(string number, CallType type) :m_type(type), Medium(number) {}
	string connect() const { return "Call"; }
	string transmit(string message) const {
		string result = "";
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
	~TwitterAccount() { cout << "Destroying the Twitter account " << this->id() << "." << endl; }
	TwitterAccount(std::string handle) : Medium(handle) {}
	std::string connect() const { return "Tweet"; }
};
class EmailAccount :public Medium {
public:
	~EmailAccount() { cout << "Destroying the email account " << this->id() << "." << endl; }
	EmailAccount(std::string email) : Medium(email) {}
	std::string connect() const { return "Email"; }
};
*/


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
void send(const Medium* m, std::string msg)
{
	cout << m->connect() << " using id " << m->id()
		<< ", sending " << m->transmit(msg) << endl;
}
int main()
{
	//Medium* x = new Medium("ethel"); // meant to produce an error
	Medium* media[4];
	media[0] = new TwitterAccount("UCLABruinAlert");
	// Phone users may prefer messages to be left as voice or text.
	media[1] = new Phone("(310) 825 3894", VOICE);
	media[2] = new Phone("(213) 389 9060", TEXT);
	media[3] = new EmailAccount("jbroon@ucla.edu");

	cout << "Send the message." << endl;
	for (int k = 0; k < 4; k++)
		send(media[k], "Major power outage in West L.A.");

	// Clean up the media before exiting
	cout << "Cleaning up." << endl;
	for (int k = 0; k < 4; k++)
		delete media[k];
}
/*
Send the message.
Tweet using id UCLABruinAlert, sending text: Major power outage in West L.A.
Call using id (310) 825 3894, sending voice: Major power outage in West L.A.
Call using id (213) 389 9060, sending text: Major power outage in West L.A.
Email using id jbroon@ucla.edu, sending text: Major power outage in West L.A.
Cleaning up.
Destroying the Twitter account UCLABruinAlert.
Destroying the phone (310) 825 3894.
Destroying the phone (213) 389 9060.
Destroying the email account jbroon@ucla.edu.
*/