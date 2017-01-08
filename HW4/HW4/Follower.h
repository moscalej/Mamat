#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include "defs.H"
#include <iostream>
#include "Lists.h"
#include "Message.h"
#include <string>

using namespace std;


class FriendType
{
private:
	string name_;
	string email_;

public:

	FriendType(string name, string email);
	string GetName() const;
	string GetEmail() const;

};

// Aid Functions ?


class Follower {
public:
	Follower(string name, string email, string password);
	~Follower() {
	}

    string GetName() const;
	string GetEmail() const;
	bool isPassword(string password) const;
	bool ShowFriendRequests();
	bool ShowFriendList();
	Result AddFriendRequest(string name, string email);
	Result AcceptFriendRequest(string email);
	Result RemoveFriend(string email);
	int NumFriendRequest();

	/*message handling funtions*/
	void ShowMessages();
	void ReadMessage(int number);///
	Message SendMessage(string email, string subject, string content); ////need to check
	int NumberUnreadMessage();

	

	// To do
private:
    // To do
	string name_;
	string email_;
	string password_;
	LinkedList<FriendType> FriendList;
	LinkedList<FriendType> FriendRequests;
	MessageBox imbox_;
	

};




#endif
