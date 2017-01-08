#include "SocialNetwork.h"

#include <iostream>







/*// General actions
void SocialNetwork::FindUser(string partialName)
{
	cout << "Followers:" << endl;
	// Loop over all followers in network
	for (int i = 0; ???????????????; ++i)
	{
		???????????????
		if (curFollower->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << curFollower->GetName() << ": " << curFollower->GetEmail() << endl;
		???????????????
	}

	cout << "Leaders:" << endl;
	// Loop over all leaders in network
	for (int i = 0; ???????????????; ++i)
	{
		???????????????
		if (curLeader->GetName().find(partialName) != string::npos)
			cout << i + 1 << ") " << curLeader->GetName() << ": " << curLeader->GetEmail() << endl;
		???????????????
	}
*/

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
		cout << LOGOUT_SUCCESS << endl;
		break;
	default: this->user_loged_on_ = OFFLINE;
		cout << LOGOUT_FAIL << endl;
	}
}

void SocialNetwork::CreateLeader(string name, string email, string password)
{
	bool awser;
	if (this->user_loged_on_ != ADMIN)
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

void SocialNetwork::DeleteUser(string email)
{
	if (ADMIN != this->user_loged_on_)
	{
		cout << DELETE_USER_FAIL << endl;
		return;
	}


	if (0 == this->follower_user_.getSize()) {
		cout << DELETE_USER_FAIL << endl;
		return;
	}
	Follower * User = follower_user_.getHead(); //need to check if this copy a new value or asinge the value to cur request

	bool result;

	while (true)
	{
		if (User->GetEmail() == email)
		{				
			if (SUCCESS == (this->follower_user_.removeElem()))
			{
				cout << DELETE_USER_SUCCESS << endl;
				return;
			}
		}
		if (false == (result = follower_user_.getNext()))
		{
			break;
		}
		User = follower_user_.getData();
	}

	User = this->leader_user_.getHead();
	while (true)
	{
		if (User->GetEmail() == email)
		{
			/*need to write a funtion that will go true all the firends and remove it from then*/
			if (SUCCESS == (this->leader_user_.removeElem()))
			{
				cout << DELETE_USER_SUCCESS << endl;
				return;
			}
		}
		if (false == (result = leader_user_.getNext()))
		{
			break;
		}
		User = leader_user_.getData();
	}
	cout << DELETE_USER_FAIL << endl;
	return;
}

void SocialNetwork::CreateFollower(string name, string email, string password)
{
	if ((this->user_loged_on_ != LEAD) || (FOLOOW != this->user_loged_on_))
	{
		return;
	}
	Follower newUser(name, email, password);
	if (SUCCESS == (this->follower_user_.addHead(newUser)))
	{
		cout << CREATE_FOLLOWER_SUCCESS << endl;
		return;
	}
	cout << CREATE_FOLLOWER_FAIL << endl;
}

void SocialNetwork::ShowFriendRequests()
{
	if ((this->user_loged_on_ != LEAD) || (FOLOOW != this->user_loged_on_))
	{
		cout << SHOW_FRIEND_REQUESTS_FAIL << endl;
		return;
	}
	this->activeFollower->ShowFriendRequests();
}

void SocialNetwork::ShowFriendList()
{
	
		if ((this->user_loged_on_ != LEAD) || (FOLOOW != this->user_loged_on_))
		{
			cout << SHOW_FRIEND_LIST_FAIL << endl;
			return;
		}
		this->activeFollower->ShowFriendList();
	
}

void SocialNetwork::SendFriendRequest(string friendEmail)
{
	if ((this->user_loged_on_ != LEAD) || (FOLOOW != this->user_loged_on_))
	{
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	

	Follower * User = this->SearchByEmailFollower(friendEmail);
	if (User != NULL)
	{
		if (SUCCESS == User->AddFriendRequest((this->activeFollower->GetName()), friendEmail))
		{
		
			cout << SEND_FRIEND_REQUEST_SUCCESS << endl;
			return;
		}
		cout << SEND_FRIEND_REQUEST_FAIL << endl;
	}
	User = this->SearchByEmailLeader(friendEmail);
	if (NULL != User)
	{
		if (SUCCESS == User->AddFriendRequest((this->activeFollower->GetName()), friendEmail))
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
	if (0 == this->follower_user_.getSize()) {
		cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;
		return;
	}
	if (SUCCESS == (this->activeFollower->AcceptFriendRequest(friendEmail)))
	{
		cout << ACCEPT_FRIEND_REQUEST_SUCCESS << endl;
	}
	cout << ACCEPT_FRIEND_REQUEST_FAIL << endl;

}

void SocialNetwork::RemoveFriend(string friendEmail)
{
	if (0 == this->follower_user_.getSize()) {
		cout << REMOVE_FRIEND_FAIL << endl;
		return;
	}
	if (SUCCESS == (this->activeFollower->RemoveFriend(friendEmail)))
	{
		cout << REMOVE_FRIEND_SUCCESS << endl;
	}
	cout << REMOVE_FRIEND_FAIL << endl;
}
//////////////////////////////////////////////////////////////////////////
/*/
void SocialNetwork::ShowMessageList()
{
	if (0 == this->follower_user_.getSize()) {
		cout << READ_MESSAGE_FAIL << endl;
		return;
	}
	this->activeFollower->ShowMessages();

}

void SocialNetwork::ReadMessage(int messageNum)
{
	if (0 == this->follower_user_.getSize()) {
		cout << READ_MESSAGE_FAIL << endl;
		return;
	}
	this->activeFollower->ReadMessage(messageNum))
	
	}
	
}
*/


SocialNetwork::SocialNetwork(string name, string password)
{
	name_ = name;
	password_ = password;

	user_loged_on_ = OFFLINE;
	activeFollower = NULL;
}

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

	if (0 == this->follower_user_.getSize()) {
		cout << LOGIN_FAIL << endl;
		return;
	}
	Follower * User = this->SearchByEmailFollower(email);
	if (User != NULL)
	{
		if (true == User->isPassword(password))
		{
			if (this->user_loged_on_ != OFFLINE) this->Logout();
			this->activeFollower = User;
			this->user_loged_on_ = FOLOOW;
			cout << LOGIN_SUCCESS << endl;
			return;
		}
	}
	User = this->SearchByEmailLeader(email);
	if (NULL != User)
		{
			if (true == User->isPassword(password))
			{
				if (this->user_loged_on_ != OFFLINE) this->Logout();
				this->activeFollower = User;
				this->user_loged_on_ = LEAD;
				cout << LOGIN_SUCCESS << endl;
				return;
			}
		}
	cout << LOGIN_FAIL << endl;
}


/*helper funtions*/
Follower * SocialNetwork::SearchByEmailFollower(string email)
{

	if (0 == this->follower_user_.getSize()) {
		return NULL;
	}
	Follower * User = follower_user_.getHead(); //need to check if this copy a new value or asinge the value to cur request
	bool result;
	while (true)
	{
		if (User->GetEmail() == email)
		{
			return User;
		}
		}
		if (false == (result = follower_user_.getNext()))
		{
			return NULL;
		}
		User = follower_user_.getData();
	
}

Leader * SocialNetwork::SearchByEmailLeader(string email)
{
	
		if (0 == this->leader_user_.getSize()) {
			return NULL;
		}
		Leader * User = leader_user_.getHead(); //need to check if this copy a new value or asinge the value to cur request
		bool result;
		while (true)
		{
			if (User->GetEmail() == email)
			{
				return User;
			}
		}
		if (false == (result = leader_user_.getNext()))
		{
			return NULL;
		}
		User = leader_user_.getData();

	
}
