

#include <iostream>
#include <string>
#include "SocialNetwork.H"

using namespace std;

//*******************************************************************
//* AdminLogin()
//* Method for an administrator to log into the network
//* Parameters: string (password)
//* Void
//*******************************************************************
void SocialNetwork::AdminLogin(string password)
{
	if (this->password_ == password) {
		if (this->user_loged_on_ != OFFLINE)
		{
			this->activeFollower = NULL;
			this->activeLeader_ = NULL;
		}
		this->user_loged_on_ = ADMIN;
		cout << ADMIN_LOGIN_SUCCESS << endl;
		return;
	}
	cout << ADMIN_LOGIN_FAIL << endl;
}


//*******************************************************************
//* SocialNetwork()
//* Method for a follower or leader to log into the network
//* Parameters: string (email), string (password)
//* Void
//*******************************************************************

void SocialNetwork::Login(string email, string password)
{

	if ((0 == this->follower_user_->getSize()) && (0 == this->leader_user_->getSize())) {
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
		cout << LOGIN_FAIL  << endl;
		return;
	}
	Leader * User2 = this->SearchByEmailLeader(email);
	if (NULL != User2)
	{
		if (true == User2->isPassword(password))
		{
			if (this->user_loged_on_ != OFFLINE)
			{
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
	cout << LOGIN_FAIL  << endl;
}

//*******************************************************************
//* Logout()
//* Method for logging out of the network
//* Parameters: None.
//* Void
//*******************************************************************
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
//*******************************************************************
//* FindUser()
//* Method for finding a user on the network.
//* Parameters: string (partialName)
//* Void
//*******************************************************************
void SocialNetwork::FindUser(string partialName)
{


	cout << "Followers:" << endl;
	// Loop over all followers in network
	int number_followers = this->follower_user_->getSize();
	Follower * curFollower = this->follower_user_->getHead();
	for (int i = 0;i < number_followers; ++i)
	{

		if (curFollower->GetName().find(partialName) != string::npos)
		{
			cout << i + 1 << ") " << curFollower->GetName() << ": " << curFollower->GetEmail() << endl;
		}
		this->follower_user_->getNext();
		curFollower = follower_user_->getData();
	}
	number_followers = this->leader_user_->getSize();
	Leader * curLeader = this->leader_user_->getData();
	cout << "Leaders:" << endl;
	// Loop over all leaders in network
	for (int i = 0; i < number_followers; ++i)
	{
		if (curLeader->GetName().find(partialName) != string::npos)
		{
			cout << i + 1 << ") " << curLeader->GetName() << ": " << curLeader->GetEmail() << endl;
		}
		this->follower_user_->getNext();
		curLeader = this->leader_user_->getData();
	}
}


//*******************************************************************
//* CreateLeader()
//* Method for creating a leader inside the network
//* Parameters: string (name), string (email), string (password)
//* Void
//*******************************************************************
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
	Leader * newleader = new Leader(name, email, password);

	if (SUCCESS == (this->leader_user_->addHead(newleader)))
	{
		cout << CREATE_LEADER_SUCCESS << endl;
		return;
	}
	delete newleader;
	cout << CREATE_LEADER_FAIL << endl;
}


/*this funtion will search on the Social network for the user  by his email
  once it found it will go throuw the user friends and reach the emails for each
  friend will search that friend and remove the user from his friend list after that
  will remove the user from the social network
  this search will hapen from the follower list and then from the leaders list*/
void SocialNetwork::DeleteUser(string email)
{

	if (ADMIN != this->user_loged_on_)
	{
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	if ((0 == this->follower_user_->getSize()) && (0 == this->leader_user_->getSize())) {
		cout << DELETE_USER_FAIL << endl;
		return;
	}

	Follower * UserFriend;
	//Follower * User = this->SearchByEmailFollower(email);
	UserFriend = this->follower_user_->getHead();
	while (UserFriend != NULL)
	{
		UserFriend->RemoveFriend(email);
		UserFriend->removeFriendRequest(email);
		UserFriend->removeLeader(email);
		if (FAILURE == follower_user_->getNext())
		{
			break;
		}
		UserFriend = follower_user_->getData();

	}
	Leader * LeaderFriend;
	LeaderFriend = this->leader_user_->getHead();
	while (LeaderFriend != NULL)
	{
		LeaderFriend->RemoveFriend(email);
		LeaderFriend->removeFriendRequest(email);
		LeaderFriend->removeLeader(email);
		LeaderFriend->RemoveFollower(email);
		if (FAILURE == leader_user_->getNext())
		{
			break;
		}
		LeaderFriend = leader_user_->getData();
	}
	Follower * User;
	Leader * User2;
	if (NULL != (User = this->SearchByEmailFollower(email)))
	{
		//clog << "this LEADER will be deestroy: " << User->GetEmail() << endl;
		//User->~Follower();
		this->follower_user_->removeElem();
		cout << DELETE_USER_SUCCESS << endl;
		return;

	}

	User2 = this->SearchByEmailLeader(email);
	if (User2 == NULL)  // in case it sosent exist
	{
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	//clog << "this LEADER will be deestroy: " << User2->GetEmail() << endl;
	//User2->~Leader();
	this->leader_user_->removeElem();
	cout << DELETE_USER_SUCCESS << endl;
	return;



}
//*******************************************************************
//* BroadcastMessage()  (FOR LEADERS ONLY)
//* Method for broadcasting a message to all of the followers
//* in the linked list.
//* Parameters: string (subject), string (content)
//* Void
//*******************************************************************

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

	for (int i = 0; i < number_followers; i++)
	{
		destiny = this->activeLeader_->mail_of_followerNumber(i + 1);
		if (NULL != (destiny_user = this->SearchByEmailFollower(destiny)))
		{

			destiny_user->addNewMessage(this->activeFollower->SendMessage(this->activeLeader_->GetEmail(), subject, content));

		}
		else if (NULL != (destiny_user = this->SearchByEmailLeader(destiny)))
		{
			destiny_user->addNewMessage(this->activeFollower->SendMessage(this->activeLeader_->GetEmail(), subject, content));

		}



	}

	cout << BROADCAST_MESSAGE_SUCCESS << endl;

}
//*******************************************************************
//* CreateFollower()
//* Method for creating a follower inside the network
//* Parameters: string (name), string (email), string (password)
//* Void
//*******************************************************************
void SocialNetwork::CreateFollower(string name, string email, string password)
{


	if ((NULL != SearchByEmailFollower(email)) || (NULL != SearchByEmailLeader(email)))
	{
		cout << CREATE_FOLLOWER_FAIL << endl;
		return;
	}

	Follower * newUser = new Follower(name, email, password);

	//newUser->set_basics(name, email, password);
	//clog << "and the first one" << (&email) << endl;
	if (SUCCESS == (this->follower_user_->addHead(newUser)))
	{

		cout << CREATE_FOLLOWER_SUCCESS << endl;

		return;
	}
	delete newUser;
	cout << CREATE_FOLLOWER_FAIL << endl;

}

//*******************************************************************
//* ShowFriendRequests()
//* Method for showing all of a users pending friend requests
//* Parameters: None
//* Void
//*******************************************************************
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
//*******************************************************************
//* ShowFriendList()
//* Method for showing all of a users current friends
//* Parameters: None
//* Void
//*******************************************************************
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
		return;
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
		return;
	}
	cout << SEND_FRIEND_REQUEST_FAIL << endl;

}
//*******************************************************************
//* SendFriendRequest()
//* Method for sending a friend request
//* Parameters: string (friendEmail)
//* Void
//*******************************************************************

void SocialNetwork::AcceptFriendRequest(string friendEmail)
{

	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	Follower * newFriend;

	if ((0 == this->follower_user_->getSize()) && (0 == this->leader_user_->getSize())) {
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

	//newFriend->AddFriendRequest(this->activeFollower->GetName(), this->activeFollower->GetEmail());
	//newFriend->AcceptFriendRequest(this->activeFollower->GetEmail());
	if (SUCCESS == (newFriend->AddFriend(this->activeFollower->GetName(), this->activeFollower->GetEmail())))
	{
		this->activeFollower->AddFriend(newFriend->GetName(), newFriend->GetEmail());
		this->activeFollower->removeFriendRequest(friendEmail);
		newFriend->removeFriendRequest(this->activeFollower->GetEmail());
		cout << ACCEPT_FRIEND_REQUEST_SUCCESS << endl;
		return;
	}
	cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;

}

//*******************************************************************
//* AcceptFriendRequest()
//* Method for accepting a friend request
//* Parameters: string (friendEmail)
//* Void
//*******************************************************************

/*this will search for remove the friend from the user and also from the "FRIEND friends"*/
void SocialNetwork::RemoveFriend(string friendEmail)
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << REMOVE_FRIEND_FAIL << endl;
		return;
	}
	if ((0 == this->follower_user_->getSize()) && (this->leader_user_->getSize())) {
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
//*******************************************************************
//* ShowMessageList()
//* Method for showing a users message list
//* Parameters: None
//* Void
//*******************************************************************
void SocialNetwork::SendMessage(string email, string subject, string content)
{
	if (this->user_loged_on_ == ADMIN || this->user_loged_on_ == OFFLINE)
	{
		cout << SEND_MESSAGE_FAIL << endl;
		return;
	}

	Follower * temp;
	if (this->activeFollower->GetEmail() == email)
	{
		cout << SEND_MESSAGE_FAIL << endl;
		return;
	}

	temp = this->SearchByEmailFollower(email);

	if (NULL != temp)
	{

		temp->addNewMessage(this->activeFollower->SendMessage(this->activeFollower->GetEmail(), subject, content));
		cout << SEND_MESSAGE_SUCCESS << endl;
		return;
	}
	temp = this->SearchByEmailLeader(email);
	if (NULL != temp)
	{
		temp->addNewMessage(this->activeFollower->SendMessage(this->activeFollower->GetEmail(), subject, content));
		cout << SEND_MESSAGE_SUCCESS << endl;
		return;
	}
	else
	{
		cout << SEND_MESSAGE_FAIL << endl;

	}
}
//*******************************************************************
//* Follow()
//* Method for a user to 'Follow' a Leader
//* Parameters: string (leaderEmail)
//* Void
//*******************************************************************
void SocialNetwork::Follow(string leaderEmail)
{
	if ((this->user_loged_on_ == OFFLINE) || (ADMIN == this->user_loged_on_))
	{
		cout << FOLLOW_FAIL << endl;
		return;
	}
	Leader * temp = this->SearchByEmailLeader(leaderEmail);
	if (temp == NULL )
	{
		cout << FOLLOW_FAIL << endl;
		return;
	}
	/*
	if (temp->GetEmail() == this->activeFollower->GetEmail())
	{
		cout << FOLLOW_FAIL << endl;
		return;
	}
	*/

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
	LinkedList<Follower> * follower_user_1 = new LinkedList<Follower>;
	LinkedList<Leader> * leader_user_1 = new LinkedList<Leader>;

	this->leader_user_ = leader_user_1;
	this->follower_user_ = follower_user_1;

}

SocialNetwork::~SocialNetwork()
{

		delete this->follower_user_;
		delete this->leader_user_;
		this->follower_user_ = NULL;
		this->leader_user_ = NULL;

	}

/*helper funtions*/
Follower * SocialNetwork::SearchByEmailFollower(string email)
{

	if (0 == this->follower_user_->getSize()) {
		return NULL;
	}
	Follower * User = follower_user_->getHead(); //need to check if this copy a new value or asinge the value to cur request
	Result result;
	while (true)
	{
		if (User->GetEmail() == email)
		{
			return User;
		}

		if (FAILURE == (result = follower_user_->getNext()))
		{
			return NULL;
		}
		User = follower_user_->getData();
	}
}

Leader * SocialNetwork::SearchByEmailLeader(string email)
{

		if (0 == this->leader_user_->getSize()) {
			return NULL;
		}
		Leader * User = leader_user_->getHead(); //need to check if this copy a new value or asinge the value to cur request
		Result result;
		while (true)
		{
			if (User->GetEmail() == email)
			{
				return User;
			}

			if (FAILURE == (result = leader_user_->getNext()))
			{
				return NULL;
			}
			User = leader_user_->getData();
		}



}
