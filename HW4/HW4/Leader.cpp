#include<iostream>
#include "Leader.H"
using namespace std;

Leader::Leader(string name, string email, string password)
{
	this->email_ = email;
	this->password_ = password;
	this->name_ = name;
	clog << "this leader has been create" << email << endl;
}

Leader::~Leader()
{
	clog << "we start the: ~Leader()" << endl;
	clog << "leader wants to be DESTROY :"<<email_ << endl;
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
		if (FAILURE == this->Followers_of_user.getNext())
		{
			break;
		}
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
			this->NumberFolloers_--;
		}
		if (FAILURE == this->Followers_of_user.getNext())
		{
			break;
		}
		temp = this->Followers_of_user.getData();
		
	}
	return FAILURE;
}

int Leader::NumberOfFolowwers() const
{
	return this->NumberFolloers_;
}

string Leader::mail_of_followerNumber(int number)
{

		if (number <1 || number > this->Followers_of_user.getSize()) return "";
		FriendType * temp = this->Followers_of_user.getHead();
		for (int i = 1; i < number; i++)
		{
			this->Followers_of_user.getNext();
		}
		temp = this->Followers_of_user.getData();
		return temp->GetEmail();

	
	
}




