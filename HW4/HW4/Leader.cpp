#include<iostream>
#include "Leader.H"
using namespace std;

int Leader::count1_2 = 0;

Leader::Leader(string name, string email, string password)
{
	this->Followers_of_user = new LinkedList<FriendType>;
	this->email_ = email;
	this->password_ = password;
	this->name_ = name;
	count1_2++;
	//clog << "this leader has been create" << email << endl;
}

Leader::~Leader()
{
	//this -> Followers_of_user->~LinkedList();
	
	delete this->Followers_of_user;
	this->Followers_of_user = NULL;
	count1_2--;
	clog << "total numberL " << count1_2 << endl;

}

Result Leader::AddFollower(string name, string email)
{
	
	FriendType * temp;
	temp = this->Followers_of_user->getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			return FAILURE;
		}
		if (FAILURE == this->Followers_of_user->getNext())
		{
			break;
		}
		temp = this->Followers_of_user->getData();
	}
	temp = NULL;
	FriendType * Newle = new FriendType(name , email);
	
	if (FAILURE == this->Followers_of_user->addHead(Newle))
	{
	
	delete Newle;
	return FAILURE;
	}
	this->NumberFolloers_++;
	return SUCCESS;
}

Result Leader::RemoveFollower(string email)
{
	if (this->Followers_of_user->getSize() == 0) return SUCCESS;
	FriendType * temp;
	temp = this->Followers_of_user->getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			this->Followers_of_user->removeElem();
			return SUCCESS;
			this->NumberFolloers_--;
		}
		if (FAILURE == this->Followers_of_user->getNext())
		{
			break;
		}
		temp = this->Followers_of_user->getData();

	}
	return FAILURE;
}

int Leader::NumberOfFolowwers() const
{
	return this->NumberFolloers_;
}

string Leader::mail_of_followerNumber(int number)
{

		if (number <1 || number > this->Followers_of_user->getSize()) return "";
		FriendType * temp = this->Followers_of_user->getHead();
		for (int i = 1; i < number; i++)
		{
			this->Followers_of_user->getNext();
		}
		temp = this->Followers_of_user->getData();
		return temp->GetEmail();



}
