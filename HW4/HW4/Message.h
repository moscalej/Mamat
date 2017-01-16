#ifndef _MESSAGE_H_
#define _MESSAGE_H_
#include <iostream>
#include <string>

#include "Lists.H"



using namespace std;

class Message {
public:
	~Message() {
		count1_m--;
		clog << "total numberM " << count1_m << endl;
	}
	Message();
    Message(string source, string subject, string content);
    void Display(int num) const;
    void Read();
	bool isRead();
	//bool operator==(const string& b) { return true; };
	static int count1_m;
private:
    string source_;
	string subject_;
    string content_;
    bool   read_;
};


class MessageBox
{
public:
	MessageBox();
	
	~MessageBox();

	void Add(Message * newMessage);
	int Size();
	int UnreadSize();
	void Print();
	
	Result ReadMessage(int messageNum);
private:
	// To do
	LinkedList<Message> * messageList;
	int readSize;
	int messageListSize;
};


#endif
