#ifndef _MESSAGE_H_
#define _MESSAGE_H_
// change .H &&&&&&&&&&&&&&&&&&&&&&
#include "defs.h"
#include "Lists.h"
#include <string>

using namespace std;

class Message {
public:
    Message(string source, string subject, string content);
    void Display(int num) const;
    void Read();
	bool isRead();
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

	void Add(Message newMessage);
	int Size();
	int UnreadSize();
	void Print();
	Result ReadMessage(int messageNum);
private:
	// To do
	LinkedList<Message> messageList;
	int readSize;
	int messageListSize;
};
#endif
