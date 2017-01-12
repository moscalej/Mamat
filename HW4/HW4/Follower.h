#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include <iostream>
#include <string>
#include "defs.H"
#include "Lists.h"
#include "Message.h"



using namespace std;


class FriendType
{

public:
	FriendType() {}
	FriendType(string name, string email);
	string GetName() const;
	string GetEmail() const;

private:

	string name_;
	string email_;

};

// Aid Functions ?


class Follower {
public:
	Follower() {}

	Follower(string name, string email, string password);
	~Follower() {
	}

    string GetName() const;
	string GetEmail() const;
	bool isPassword(string password) const;
	bool ShowFriendRequests();
	bool ShowFriendList();
	Result AddFriendRequest(string name, string email); // <--- important to check that cant befriend self or already friends
	Result AcceptFriendRequest(string email);
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
	int NumberOfFriends() const;
protected:

	string name_;
	string email_;
	string password_;
	int friends_number_;
	LinkedList<FriendType> FriendList;
	LinkedList<FriendType> FriendRequests;
	MessageBox imbox_;
};




#endif
