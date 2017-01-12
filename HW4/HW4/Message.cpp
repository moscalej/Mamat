#include "Message.h"

using namespace std;
// Operator Overload for "=="
bool operator==(const Message& lhs, const Message& rhs)
{
	if (lhs == rhs)	return true;
	else return false;
}
// Default Constructor
Message::Message() {};
// Constructor
Message::Message(string source, string subject, string content) : source_(source), subject_(subject), content_(content), read_(false) {}

void Message::Display(int num) const
{
	cout << num << ") " << (read_ ? "" : "(Unread) ") << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
}

void Message::Read()
{
	read_ = true;
	cout << "From: " << source_ << endl;
	cout << "Subject: " << subject_ << endl;
	cout << "Content: " << content_ << endl;
}

bool Message::isRead()
{
	return read_;
}


MessageBox::MessageBox()
{
	messageListSize = 0;
	readSize = 0;
}

MessageBox::~MessageBox()
{
	this->messageList.~LinkedList();
}
// Adding a new message to our message box
// Here we are adding a COPY of the message.
void MessageBox::Add(Message newMessage)
{
	messageList.addHead(newMessage);
	messageListSize++;
}

// Getting the number of messages in our message box.
int MessageBox::Size()
{
	return this->messageListSize;
}

// The number of unread messages in out message box.
int MessageBox::UnreadSize()
{
	return messageListSize - readSize;
}

void MessageBox::Print()
{
	Message * temp = messageList.getHead();
	if (this->messageListSize == 0)
	{
		return;
	}
	temp->Read();
	for (int i = 1; i < messageListSize; i++)
	{
		messageList.getNext();
		temp = this->messageList.getData();

		READ_MESSAGE_SUCCESS

	}
	this->readSize = this->messageListSize;// We have read the entire list.

}

Result MessageBox::ReadMessage(int messageNum)
{
	if (messageNum > messageListSize || messageNum < 0) return FAILURE;
	Message * temp = messageList.getHead();
	for (int i = 1; i < messageNum; i++)
	{
		messageList.getNext();
	}
	temp = messageList.getData();
	if (temp->isRead() == false)// Message has not been read before
	{
		readSize++;// Increase number of read messages.
	}
	READ_MESSAGE_SUCCESS

	return SUCCESS;
}

