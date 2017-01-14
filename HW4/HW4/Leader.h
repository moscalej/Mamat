#ifndef _LEADER_H_
#define _LEADER_H_
#include "Follower.H"


class Leader : public Follower
{
public:
	Leader() {}
	Leader(string name, string email, string password);
	~Leader();
	Result AddFollower(string name, string email);
	Result RemoveFollower(string email);
	int NumberOfFolowwers() const;
	string mail_of_followerNumber(int number);
	
	
private:
	LinkedList<FriendType> Followers_of_user;
	
	int NumberFolloers_;
};




#endif
