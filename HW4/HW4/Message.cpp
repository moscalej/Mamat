#include "Message.H"

using namespace std;

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
	//clog << "we start the : :~MessageBox()" << endl;
	//this->messageList.listClean();
}
// Adding a new message to our message box
// Here we are adding a COPY of the message.
void MessageBox::Add(Message newMessage)
{
	
	Message * message = new Message;
	*message = newMessage;
	messageList.addHead(message);
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
	
	for (int i = 1; i < messageListSize+1; i++)
	{
		messageList.getNext();
		SHOW_MESSAGE_LIST_SUCCESS
		temp = this->messageList.getData();

	}
	// We have read the entire list.

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

