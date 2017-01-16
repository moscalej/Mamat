#include "Message.H"

using namespace std;


int Message::count1_m = 0;
// Default Constructor
Message::Message() { count1_m++; };
// Constructor
Message::Message(string source, string subject, string content) : source_(source), subject_(subject), content_(content), read_(false) {
	count1_m++;
}

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
	this->messageList = new LinkedList<Message>;
	messageListSize = 0;
	readSize = 0;
}

MessageBox::~MessageBox()
{
	
	delete this->messageList;
	this->messageList = NULL;
	//clog << "we start the : :~MessageBox()" << endl;
	//this->messageList->listClean();
}
// Adding a new message to our message box
// Here we are adding a COPY of the message.
void MessageBox::Add(Message * newMessage)
{

	messageList->addHead(newMessage);
	messageListSize++;
}

// Getting the number of messages in our message box.
int MessageBox::Size()
{
	return this->messageList->getSize();
}

// The number of unread messages in out message box.
int MessageBox::UnreadSize()
{
	return messageListSize - readSize;
}

void MessageBox::Print()
{
	Message * temp = messageList->getHead();
	if (this->messageList->getSize() == 0)
	{
		return;
	}

	for (int i = 1; i < messageListSize+1; i++)
	{
		SHOW_MESSAGE_LIST_SUCCESS
		if (FAILURE == messageList->getNext()) return;
		
		temp = this->messageList->getData();

	}
	temp = NULL;
	// We have read the entire list.

}

Result MessageBox::ReadMessage(int messageNum)
{
	if (messageNum > messageListSize || messageNum < 0) return FAILURE;
	Message * temp = messageList->getHead();
	for (int i = 1; i < messageNum; i++)
	{
		messageList->getNext();
	}
	temp = messageList->getData();
	if (temp->isRead() == false)// Message has not been read before
	{
		readSize++;// Increase number of read messages.
	}
	READ_MESSAGE_SUCCESS

	return SUCCESS;
}
