#ifndef _FOLLOWER_H_
#define _FOLLOWER_H_

#include <iostream>
#include <string>

#include "Message.H"



using namespace std;


class FriendType
{

public:
	~FriendType() {
		count1_fr--;
		//clog << "total numberFr " << count1_fr << endl;
	}
	FriendType() {
		count1_fr++;
	}
	FriendType(string name, string email);
	string GetName() const;
	string GetEmail() const;
	void giveName(string name, string email) {
		this->name_ = name;
		this->email_ = email;

	}
	static int count1_fr;
	
private:

	string name_;
	string email_;

};




class Follower {
public:
	Follower()
	{

		this->imbox_ = new MessageBox;
		this->FriendList = new LinkedList<FriendType>;
		this->FriendRequests = new LinkedList<FriendType>;
		this->Leaders_to_follow = new LinkedList<FriendType>;
		count_4++;
		

		//clog << "DEFOULT FOLLOWER HAS BEEN CREATE" << endl;
	}

	 Follower(string name, string email, string password);
	virtual ~Follower() {
		//clog << this->GetEmail() << "destroy" << endl;
		delete this->FriendList;
		delete this->FriendRequests;
		delete this->Leaders_to_follow;
		delete this->imbox_;
		this->FriendList=NULL;
		this->FriendRequests = NULL;
		this->Leaders_to_follow = NULL;
		this->imbox_ = NULL;
		count_4--;
		// clog << "total numberF " << count_4 << endl;
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
	Message * SendMessage(string email, string subject, string content); ////need to check
	void addNewMessage(Message  * newMessage);
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

	static int count_4;
protected:

	bool check_friend(string email);
	bool check_leader(string email); // true means there is not such a person
	string name_;
	string email_;
	string password_;

	LinkedList<FriendType> * FriendList;
	LinkedList<FriendType> * FriendRequests;
	LinkedList<FriendType> * Leaders_to_follow;
	MessageBox * imbox_;
};




#endif
