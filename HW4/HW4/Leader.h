#ifndef _LEADER_H_
#define _LEADER_H_
#include "Follower.h"

#include "defs.H"
class Leader : public Follower
{
public:
	Leader() {}
	Leader(string name, string email, string password);
	~Leader();
	Result AddFollower(string name, string email);
	Result RemoveFollower(string email);
	int NumberOfFolowwers() const;
	LinkedList<FriendType> SendBrodcast();
	
private:
	LinkedList<FriendType> Followers_of_user;
	
	int NumberFolloers_;
};




#endif
