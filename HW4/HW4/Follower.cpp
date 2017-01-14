#include <iostream>

#include "Follower.H"

using namespace std;

Follower::Follower(string name, string email, string password)
{
	name_ = name;
	email_ = email;
	password_ = password;
	friends_number_ = 0;
	clog << "this followr has been create" << email_ << endl;
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
	Result result;
	while (i != max + 1)
	{
		cout << SHOW_FRIEND_REQUESTS_SUCCESS << endl;
		if (FAILURE == (result = FriendRequests.getNext()))
		{
			break;
		}
		curRequest = FriendRequests.getData();
		i++;
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
	Result result;
	while (i != max + 1)
	{
		cout << SHOW_FRIEND_LIST_SUCCESS << endl;
		if (FAILURE == (result = FriendList.getNext()))
		{
			break;
		}
		curFriend = FriendList.getData();
		i++;
	}
	return true;

	
}

Result Follower::AddFriendRequest(string name, string email)
{
	FriendType temp(name, email);
	if ((true == check_friend_request(email)) && (true == check_friend(email)))
	{
		return this->FriendRequests.addHead(temp);
	}
	return FAILURE;
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
			if (false == this->check_friend(email)) 
			{
				this->FriendRequests.removeElem();
				return FAILURE;
			}
			this->FriendList.addHead(newfriend);// need to check if already friends
			this->friends_number_ = this->friends_number_++;
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
			this->friends_number_ = this->friends_number_ - 1;
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

void Follower::addNewMessage(Message newMessage)
{
	this->imbox_.Add(newMessage);
	
}

int Follower::NumberUnreadMessage()
{
	return this->imbox_.UnreadSize();
}



string Follower::ShowFriendMail(int Friend_number) 
{
	int temp = this->NumberOfFriends();
	FriendType * Momentary_firend = this->FriendList.getHead();
	if (temp == 0 || Friend_number > temp) return NULL;
	for (int i = 1; i < Friend_number; i++)
	{
		this->FriendList.getNext();
	}
	Momentary_firend = this->FriendList.getData();

	return Momentary_firend->GetEmail();
}

int Follower::NumberOfFriends() const
{
	return this->friends_number_;
}

bool Follower::AddLeader(string name, string email)
{
	FriendType newLeader(name, email);
	if (true == this->check_leader(email))
	{
		this->Leaders_to_follow.addHead(newLeader);
			return true ;
	}
	return false;
}

int Follower::number_of_leaders()
{
	return this->Leaders_to_follow.getSize();
}

string Follower::show_leaders_email(int number)
{
	if (number <1 || number > this->Leaders_to_follow.getSize()) return "";
	FriendType * temp = this->Leaders_to_follow.getHead();
	for (int i = 1; i < number; i++)
	{
		this->Leaders_to_follow.getNext();
	}
	temp = this->Leaders_to_follow.getData();
	return temp->GetEmail();

}

bool Follower::check_friend_request(string email)
{
	if (0 == this->FriendRequests.getSize()) return true;
	FriendType * temp = this->FriendRequests.getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			return false;
		}
		if (FAILURE == (this->FriendRequests.getNext() ))
		{
			break;
		}
		temp = this->FriendRequests.getData();
	}
	return true;
}

bool Follower::check_friend(string email)
{
	if (0 == this->FriendList.getSize()) return true;
	FriendType * temp = this->FriendList.getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			return false;
		}
		if (FAILURE == (this->FriendList.getNext()))
		{
			break;
		}
		temp = this->FriendList.getData();
	}
	return true;
}

bool Follower::check_leader(string email)
{
	if (0 == this->Leaders_to_follow.getSize()) return true;
	FriendType * temp = this->Leaders_to_follow.getHead();
	while (temp != NULL)
	{
		if (temp->GetEmail() == email)
		{
			return false;
		}
		if (FAILURE == (this->Leaders_to_follow.getNext()))
		{
			break;
		}
		temp = this->Leaders_to_follow.getData();
	}
	return true;
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
