

#include <iostream>
#include <string>
#include "SocialNetwork.h"

using namespace std;


void SocialNetwork::AdminLogin(string password)
{
	if (this->password_ == password) {
		if (this->user_loged_on_ != OFFLINE) this->Logout();
		this->user_loged_on_ = ADMIN;
		cout << ADMIN_LOGIN_SUCCESS << endl;
		return;
	}
	cout << ADMIN_LOGIN_FAIL << endl;
}



/*we could have use a template funtion for this but only for two kind of elements is not worth it
we could build a global neutral pointer and cast diferent types wehn we search in diferent lists */
void SocialNetwork::Login(string email, string password)
{

	if ((0 == this->follower_user_.getSize()) && (0 == this->leader_user_.getSize())) {
		cout << LOGIN_FAIL << endl;
		return;
	}
	Follower * User = this->SearchByEmailFollower(email);
	if (User != NULL)
	{
		if (true == User->isPassword(password))
		{
			if (this->user_loged_on_ != OFFLINE) {
				this->activeFollower = NULL;
				this->activeLeader_ = NULL;
			}
			this->activeFollower = User;
			this->user_loged_on_ = FOLOOW;
			cout << LOGIN_SUCCESS << endl;
			return;
		}
		cout << LOGIN_FAIL << endl;
		return;
	}
	Leader * User2 = this->SearchByEmailLeader(email);
	if (NULL != User2)
	{
		if (true == User2->isPassword(password))
		{
			if (this->user_loged_on_ != OFFLINE) {
				this->activeFollower = NULL;
				this->activeLeader_ = NULL;
			}
			this->activeFollower = User2;
			this->activeLeader_ = User2;
			this->user_loged_on_ = LEAD;
			cout << LOGIN_SUCCESS << endl;
			return;
		}
		cout << LOGIN_FAIL << endl;
		return;
	}
	cout << LOGIN_FAIL << endl;
}


void SocialNetwork::Logout()
{
	switch (this->user_loged_on_)
	{
	case ADMIN:
		this->user_loged_on_ = OFFLINE;
		cout << LOGOUT_SUCCESS << endl;
		break;
	case FOLOOW:
		this->user_loged_on_ = OFFLINE;
		this->activeFollower = NULL;
		cout << LOGOUT_SUCCESS << endl;
		break;
	case LEAD:
		this->user_loged_on_ = OFFLINE;
		this->activeFollower = NULL;
		this->activeLeader_ = NULL;
		cout << LOGOUT_SUCCESS << endl;
		break;
	default: this->user_loged_on_ = OFFLINE;
		cout << LOGOUT_FAIL << endl;
	}
}

void SocialNetwork::FindUser(string partialName)
{

	cout << "Followers:" << endl;
	// Loop over all followers in network
	int number_followers = this->follower_user_.getSize();
	Follower * curFollower = this->follower_user_.getHead();
	for (int i = 0;i < number_followers; ++i)
	{

		if (curFollower->GetName().find(partialName) != string::npos)
		{
			cout << i + 1 << ") " << curFollower->GetName() << ": " << curFollower->GetEmail() << endl;
		}
		this->follower_user_.getNext();
		curFollower = follower_user_.getData();
	}
	number_followers = this->leader_user_.getSize();
	Leader * curLeader = this->leader_user_.getData();
	cout << "Leaders:" << endl;
	// Loop over all leaders in network
	for (int i = 0; i < number_followers; ++i)
	{
		if (curLeader->GetName().find(partialName) != string::npos)
		{
			cout << i + 1 << ") " << curLeader->GetName() << ": " << curLeader->GetEmail() << endl;
		}
		this->follower_user_.getNext();
		curLeader = this->leader_user_.getData();
	}
}



void SocialNetwork::CreateLeader(string name, string email, string password)
{
	
	if (this->user_loged_on_ != ADMIN)
	{
		cout << CREATE_LEADER_FAIL << endl;
		return;
	}
	Leader * temp;
	
	if (NULL != (temp = SearchByEmailLeader(email)))
	{
		cout << CREATE_LEADER_FAIL << endl;
		return;
	}
	Leader newleader(name, email, password);
	if (SUCCESS == (this->leader_user_.addHead(newleader)))
	{
		cout << CREATE_LEADER_SUCCESS << endl;
		return;
	}
	cout << CREATE_LEADER_FAIL << endl;
}


/*this funtion will search on the Social network for the user  by his email
  once it found it will go throuw the user friends and reach the emails for each 
  friend will search that friend and remove the user from his friend list after that
  will remove the user from the social network
  this search will hapen from the follower list and then from the leaders list*/
void SocialNetwork::DeleteUser(string email)
{
	int Number_of_friends;
	if (ADMIN != this->user_loged_on_)
	{
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	if ((0 == this->follower_user_.getSize()) && (0 == this->leader_user_.getSize())) {
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	
	Follower * UserFriend;
	Follower * User = this->SearchByEmailFollower(email);
	if (User != NULL)
	{
		Number_of_friends = User->NumberOfFriends();
		for (int i = 0; i < Number_of_friends; i++)
		{

			/*this will get the mails of the friends and get a pointer to the friends and delete hes existence from then */

			if (NULL == (UserFriend = this->SearchByEmailFollower(User->ShowFriendMail(i + 1))))
			{
				UserFriend = this->SearchByEmailLeader(User->ShowFriendMail(i + 1));
				if (UserFriend == NULL)
				{
					continue;
				}
				UserFriend->RemoveFriend(User->GetEmail());
				continue;
			
			}
			UserFriend->RemoveFriend(User->GetEmail());
		}
		
		User = this->SearchByEmailFollower(email);
		string email_to_see;
		Leader * TheLEader;
		int numberLEADERs = User->number_of_leaders();
		if (numberLEADERs != 0)
		{
			
			for (int i = 0; i < numberLEADERs; i++)
			{
				email_to_see = User->show_leaders_email(i+1);
				TheLEader = this->SearchByEmailLeader(email_to_see);
				if (TheLEader == NULL)
				{
					continue;
				}
				TheLEader->RemoveFollower(User->GetEmail());

			}
		}




		User = this->SearchByEmailFollower(email); // to set the iterator to the rigth place and we know is not null from the last part
		clog << "this follower will be deestroy: " << User->GetEmail() << endl;
		User->~Follower();
		this->follower_user_.removeElem();
		cout << DELETE_USER_SUCCESS << endl;
		return;

	}
	Leader * User2;
	User2 = this->SearchByEmailLeader(email);
	// there is not such an user
	if (User2 == NULL)
	{
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	/*now we know the user is a leader and we search on the lider lybery*/
	Number_of_friends = User2->NumberOfFriends();
	for (int i = 0; i < Number_of_friends; i++)
	{

		/*this will get the mails of the friends and get a pointer to the friends and delete hes existence from then */

		if (NULL == (UserFriend = this->SearchByEmailFollower(User->ShowFriendMail(i + 1))))
		{
			UserFriend = this->SearchByEmailLeader(User->ShowFriendMail(i + 1));
			if (UserFriend == NULL)
			{
				continue;
			}
			UserFriend->RemoveFriend(User->GetEmail());
			continue;
		}
		UserFriend->RemoveFriend(User->GetEmail());
	}
	
	User2 = this->SearchByEmailLeader(email);
	string email_to_see;
	Leader * TheLEader;
	int numberLEADERs = User2->number_of_leaders();
	if (numberLEADERs != 0)
	{

		for (int i = 0; i < numberLEADERs; i++)
		{
			email_to_see = User2->show_leaders_email(i + 1);
			TheLEader = this->SearchByEmailLeader(email_to_see);
			if (TheLEader == NULL)
			{
				continue;
			}
			TheLEader->RemoveFollower(User->GetEmail());

		}
	}
	User = this->SearchByEmailLeader(email);
	clog << "this LEADER will be deestroy: " << User->GetEmail() << endl;
	User->~Follower();
	this->leader_user_.removeElem();
	cout << DELETE_USER_SUCCESS << endl;
	return;
}

void SocialNetwork::BroadcastMessage(string subject, string content)
{
	if (this->user_loged_on_ != LEAD)
	{
		cout << BROADCAST_MESSAGE_FAIL << endl;
		return;
	}
	int number_followers = this->activeLeader_->NumberOfFolowwers();
	if (0== number_followers)
	{
		cout << BROADCAST_MESSAGE_FAIL << endl; // need to be check
		return;
	}
	string destiny;
	Follower * destiny_user;
	Message newMessae(this->activeLeader_->GetEmail(), subject, content);
	for (int i = 0; i < number_followers; i++)
	{
		destiny = this->activeLeader_->mail_of_followerNumber(i + 1);
		if (NULL != (destiny_user = this->SearchByEmailFollower(destiny)))
		{
			destiny_user->addNewMessage(newMessae);
			
		}
		else if (NULL != (destiny_user = this->SearchByEmailLeader(destiny)))
		{
			destiny_user->addNewMessage(newMessae);
			
		}
		else
		{

		}


	}

	cout << BROADCAST_MESSAGE_SUCCESS << endl;

}

void SocialNetwork::CreateFollower(string name, string email, string password)
{
	if (this->user_loged_on_ == OFFLINE)
	{
		cout << CREATE_FOLLOWER_FAIL << endl;
		return;
	}
	Follower newUser(name, email, password);
	if ((NULL != SearchByEmailFollower(email)) || (NULL != SearchByEmailLeader(email)))
	{
		cout << CREATE_FOLLOWER_FAIL << endl;
		return;
	}
	if (SUCCESS == (this->follower_user_.addHead(newUser)))
	{
		cout << CREATE_FOLLOWER_SUCCESS << endl;
		return;
	}
	cout << CREATE_FOLLOWER_FAIL << endl;
}

void SocialNetwork::ShowFriendRequests()
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << SHOW_FRIEND_REQUESTS_FAIL << endl;
		return;
	}
	this->activeFollower->ShowFriendRequests();
}

void SocialNetwork::ShowFriendList()
{
	
		if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
		{
			cout << SHOW_FRIEND_LIST_FAIL << endl;
			return;
		}
		this->activeFollower->ShowFriendList();
	
}

void SocialNetwork::SendFriendRequest(string friendEmail)
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	

	Follower * User = this->SearchByEmailFollower(friendEmail);
	if ((User != NULL) && (User->GetEmail() != this->activeFollower->GetEmail()))
	{
		if (SUCCESS == User->AddFriendRequest((this->activeFollower->GetName()), this->activeFollower->GetEmail()))
		{
		
			cout << SEND_FRIEND_REQUEST_SUCCESS << endl;
			return;
		}
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
	}
	User = this->SearchByEmailLeader(friendEmail);
	if ((NULL != User) && (User->GetEmail() != this->activeFollower->GetEmail()))
	{
		if (SUCCESS == User->AddFriendRequest((this->activeFollower->GetName()), this->activeFollower->GetEmail()))
		{

			cout << SEND_FRIEND_REQUEST_SUCCESS << endl;
			return;
		}
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
	}
	cout << SEND_FRIEND_REQUEST_FAIL << endl;

}

void SocialNetwork::AcceptFriendRequest(string friendEmail)
{
	Follower * newFriend;
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
		return;
	}


	if ((0 == this->follower_user_.getSize()) && (0 == this->leader_user_.getSize())) {
		cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	if (NULL == (newFriend = this->SearchByEmailFollower(friendEmail)))
	{
		if ((NULL == (newFriend = this->SearchByEmailLeader(friendEmail))))
		{
			cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
			return;
		}
	}
	newFriend->AddFriendRequest(this->activeFollower->GetName(), this->activeFollower->GetEmail());
	newFriend->AcceptFriendRequest(this->activeFollower->GetEmail());
	if (SUCCESS == (this->activeFollower->AcceptFriendRequest(friendEmail)))
	{
		cout << ACCEPT_FRIEND_REQUEST_SUCCESS << endl;
		return;
	}
	cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;

}

/*this will search for remove the friend from the user and also from the "FRIEND friends"*/
void SocialNetwork::RemoveFriend(string friendEmail)
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << REMOVE_FRIEND_FAIL << endl;
		return;
	}
	if ((0 == this->follower_user_.getSize()) && (this->leader_user_.getSize())) {
		cout << REMOVE_FRIEND_FAIL << endl;
		return;
	}
	if (SUCCESS == (this->activeFollower->RemoveFriend(friendEmail)))
	{
		Follower * oldfriend = this->SearchByEmailFollower(friendEmail);
		if (oldfriend != NULL)
		{
			oldfriend->RemoveFriend(this->activeFollower->GetEmail());
			cout << REMOVE_FRIEND_SUCCESS << endl;
			return;
		}
		if (NULL != (oldfriend = this->SearchByEmailLeader(friendEmail)))
		{
			oldfriend->RemoveFriend(this->activeFollower->GetEmail());
			cout << REMOVE_FRIEND_SUCCESS << endl;
			return;
		}


		
	}
	cout << REMOVE_FRIEND_FAIL << endl;
}
void SocialNetwork::ShowMessageList()
{
	if (this->user_loged_on_ == ADMIN || this->user_loged_on_ == OFFLINE)
	{
		cout << SHOW_MESSAGE_LIST_FAIL<<endl;
		return;
	}
	this->activeFollower->ShowMessages();
}
void SocialNetwork::ReadMessage(int messageNum)
{
	if (this->user_loged_on_ == ADMIN || this->user_loged_on_ == OFFLINE)
	{
		cout << READ_MESSAGE_FAIL<<endl;
		return;
	}
	this->activeFollower->ReadMessage(messageNum);


}
void SocialNetwork::SendMessage(string email, string subject, string content)
{
	if (this->user_loged_on_ == ADMIN || this->user_loged_on_ == OFFLINE)
	{
		cout << SEND_MESSAGE_FAIL << endl;
		return;
	}
	Message new_message(this->activeFollower->GetEmail(), subject, content);
	Follower * temp;
	temp = this->SearchByEmailFollower(email);
	if (NULL != temp)
	{
	
		temp->addNewMessage(new_message);
		cout << SEND_MESSAGE_SUCCESS << endl;
		return;
	}
	temp = this->SearchByEmailLeader(email);
	if (NULL != temp)
	{
		temp->addNewMessage(new_message);
		cout << SEND_MESSAGE_SUCCESS << endl;
		return;
	}
	else
	{
		cout << SEND_MESSAGE_FAIL << endl;

	}
}
void SocialNetwork::Follow(string leaderEmail)
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << FOLLOW_FAIL << endl;
		return;
	}
	Leader * temp = this->SearchByEmailLeader(leaderEmail);
	if (temp == NULL)
	{
		cout << FOLLOW_FAIL << endl;
		return;
	}
	if (SUCCESS == temp->AddFollower(this->activeFollower->GetName(), this->activeFollower->GetEmail()))
	{
		this->activeFollower->AddLeader(temp->GetName(), leaderEmail);
		cout << FOLLOW_SUCCESS << endl;
		return;
	}
	cout << FOLLOW_FAIL << endl;
}

SocialNetwork::SocialNetwork(string name, string password)
{
	name_ = name;
	password_ = password;

	user_loged_on_ = OFFLINE;
	activeFollower = NULL;
}

SocialNetwork::~SocialNetwork()
{
	clog << "we start the: ~SocialNetwork()"  << endl;
	Follower * temp_follower;
	temp_follower = this->follower_user_.getHead();
	while (temp_follower != NULL)
	{
		clog << "this follower will be deestroy: " << temp_follower->GetEmail() << endl;
		temp_follower->~Follower();
		if (FAILURE == this->follower_user_.getNext())
		{
			break;
		}
		temp_follower = follower_user_.getData();
	}
	Leader * temp_Leader;
	temp_Leader = this->leader_user_.getHead();
	while (temp_follower != NULL)
	{
		clog << "this leader will be destroy: " << temp_Leader->GetEmail() << endl;
		temp_Leader->~Leader();
		
		if (FAILURE == this->leader_user_.getNext())
		{
			break;
		}
		temp_Leader = leader_user_.getData();
	}
	this->follower_user_.~LinkedList();
	this->leader_user_.~LinkedList();
}


/*helper funtions*/
Follower * SocialNetwork::SearchByEmailFollower(string email)
{

	if (0 == this->follower_user_.getSize()) {
		return NULL;
	}
	Follower * User = follower_user_.getHead(); //need to check if this copy a new value or asinge the value to cur request
	Result result;
	while (true)
	{
		if (User->GetEmail() == email)
		{
			return User;
		}

		if (FAILURE == (result = follower_user_.getNext()))
		{
			return NULL;
		}
		User = follower_user_.getData();
	}
}

Leader * SocialNetwork::SearchByEmailLeader(string email)
{
	
		if (0 == this->leader_user_.getSize()) {
			return NULL;
		}
		Leader * User = leader_user_.getHead(); //need to check if this copy a new value or asinge the value to cur request
		Result result;
		while (true)
		{
			if (User->GetEmail() == email)
			{
				return User;
			}

			if (FAILURE == (result = leader_user_.getNext()))
			{
				return NULL;
			}
		}
		User = leader_user_.getData();

	
}
