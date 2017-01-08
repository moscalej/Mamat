#ifndef _LEADER_H_
#define _LEADER_H_
#include "Follower.h"

#include "defs.H"
class Leader : public Follower
{
public:
	Leader(string name, string email, string password);
	~Leader();

private:

};

Leader::Leader(string name, string email, string password)
{
	this->email_ = email;
	this->password_ = password;
	this->name_ = name;
}

Leader::~Leader()
{
}



#endif
