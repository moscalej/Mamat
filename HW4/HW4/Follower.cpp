#include <iostream>

#include "Follower.H"



Follower::Follower(string name, string email, string password)
{
	name_ = name;
	email_ = email;
	password_ = password;
}

string Follower::GetName() const
{
	return name_;
}

string Follower::GetEmail() const
{
	return email_;
}

bool Follower::isPassword(string password) const
{
	return (password_ == password ? true : false);
}
/*this funtion will check the list with friend request and print then
	if there is no friend request will do nothing
	if there is friend request will print then in order from newest to the last
	*/
bool Follower::ShowFriendRequests()
{
	if (0 == this->FriendRequests.getSize()) {
		return false;
	}
	FriendType * curRequest = FriendRequests.getHead(); //need to check if this copy a new value or asinge the value to cur request

	int i = 0;
	int max = FriendRequests.getSize();
	bool result;
	while (i != max + 1)
	{
		cout << SHOW_FRIEND_REQUESTS_SUCCESS << endl;
		if (false == (result = FriendRequests.getNext()))
		{
			break;
		}
		curRequest = FriendRequests.getData();
	}
	return true;
}

bool Follower::ShowFriendList()
{
	if (0 == this->FriendList.getSize()) {
		return false;
	}
	FriendType * curFriend = FriendList.getHead(); //need to check if this copy a new value or asinge the value to cur request


	int i = 0;
	int max = FriendList.getSize();
	bool result;
	while (i != max + 1)
	{
		cout << SHOW_FRIEND_LIST_SUCCESS << endl;
		if (false == (result = FriendList.getNext()))
		{
			break;
		}
		curFriend = FriendList.getData();
	}
	return true;

	
}

Result Follower::AddFriendRequest(string name, string email)
{
	FriendType temp(name, email);
	return this->FriendRequests.addHead(temp);
}

Result Follower::AcceptFriendRequest(string email)
{
	if (0 == FriendRequests.getSize()) return FAILURE;
	FriendType * temp = FriendRequests.getHead();
	while(true)
	{
		if (temp->GetEmail() == email)
		{
			FriendType newfriend(temp->GetName(), temp->GetEmail());
			this->FriendList.addHead(newfriend);
			this->FriendRequests.removeElem();
			return SUCCESS;
		}
		if (FAILURE == (this->FriendRequests.getNext()))
		{
			return FAILURE;
		}
		temp = FriendRequests.getData();
	}

}

Result Follower::RemoveFriend(string email)
{
	if (0 == FriendList.getSize()) return FAILURE;
	FriendType * temp = FriendList.getHead();
	while (true)
	{
		if (temp->GetEmail() == email)
		{
			this->FriendList.removeElem();
			return SUCCESS;
		}
		if (FAILURE == (this->FriendList.getNext()))
		{
			return FAILURE;
		}
		temp = FriendList.getData();
	}
	

}

int Follower::NumFriendRequest()
{
	return this->FriendRequests.getSize();
}

void Follower::ShowMessages()
{
	imbox_.Print();
}

void Follower::ReadMessage(int number)
{
	this->imbox_.ReadMessage(number);
}

Message Follower::SendMessage(string email, string subject, string content)
{
	Message newmessage(email, subject, content);
	return newmessage;
}

int Follower::NumberUnreadMessage()
{
	return this->imbox_.UnreadSize();
}

FriendType::FriendType(string name, string email)
{
	this->name_ = name;
	this->email_ = email;
		
}

string FriendType::GetName() const
{
	return name_;
}

string FriendType::GetEmail() const
{
	return this->email_;
}
