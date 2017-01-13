#include<iostream>
#include "Leader.H"
using namespace std;

Leader::Leader(string name, string email, string password)
{
	this->email_ = email;
	this->password_ = password;
	this->name_ = name;
}

Leader::~Leader()
{
	this->Followers_of_user.~LinkedList();
}

Result Leader::AddFollower(string name,string email)
{
	FriendType newFollower(name, email);
	FriendType * temp = this->Followers_of_user.getHead();
	while (temp!=NULL)
	{
		if (temp->GetEmail() == email)
		{
			return FAILURE;
		}
		this->Followers_of_user.getNext();
		temp = this->Followers_of_user.getData();
	}
	this->Followers_of_user.addHead(newFollower);
	this->NumberFolloers_++;
	return SUCCESS;
}

Result Leader::RemoveFollower(string email)
{
	FriendType * temp = this->Followers_of_user.getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			this->Followers_of_user.removeElem();
			return SUCCESS;
		}
		this->Followers_of_user.getNext();
		temp = this->Followers_of_user.getData();
		this->NumberFolloers_--;
	}
	return FAILURE;
}

int Leader::NumberOfFolowwers() const
{
	return this->NumberFolloers_;
}

LinkedList<FriendType> Leader::SendBrodcast() const
{
	return this->Followers_of_user;
}


