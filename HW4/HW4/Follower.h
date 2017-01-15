#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include <iostream>
#include <string>

#include "Message.H"



using namespace std;


class FriendType
{

public:
	FriendType() {}
	FriendType(string name, string email);
	string GetName() const;
	string GetEmail() const;
	void giveName(string name, string email) {
		this->name_=name;
		this->email_ = email;

	}

private:

	string name_;
	string email_;

};

// Aid Functions ?


class Follower {
public:
	Follower()
	{
		this->email_ = "";
		this->name_ = "";
		

		clog << "DEFOULT FOLLOWER HAS BEEN CREATE" << endl;
	}

	 Follower(string name, string email, string password);
	virtual ~Follower() {
		//this->FriendRequests.~LinkedList();
		//->FriendList.~LinkedList();
	}

    string GetName() const;
	string GetEmail() const;
	bool isPassword(string password) const;


	bool ShowFriendRequests();
	bool ShowFriendList();
	Result AddFriendRequest(string name, string email); // <--- important to check that cant befriend self or already friends
	Result AddFriend(string name, string email);
	Result AcceptFriendRequest(string email);
	Result removeFriendRequest(string email);
	Result RemoveFriend(string email);
	int NumFriendRequest();

	/*message handling funtions*/
	void ShowMessages();
	void ReadMessage(int number);///
	Message SendMessage(string email, string subject, string content); ////need to check
	void addNewMessage(Message newMessage);
	int NumberUnreadMessage();
	

	/*this funtion will return the emails from their friend from 1 to the number of friends
		 if there is an error will return null (sitrng is a pointer)*/
	string ShowFriendMail(int Friend_number);
	int NumberOfFriends();
	bool AddLeader(string name, string email);

	int number_of_leaders();
	string show_leaders_email(int number);
	bool check_friend_request(string email);
	Result removeLeader(string email);

	void set_basics(string name, string email, string password);
protected:
	
	bool check_friend(string email);
	bool check_leader(string email); // true means there is not such a person
	string name_;
	string email_;
	string password_;
	
	LinkedList<FriendType> FriendList;
	LinkedList<FriendType> FriendRequests;
	LinkedList<FriendType> Leaders_to_follow;
	MessageBox imbox_;
};




#endif
