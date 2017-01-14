#ifndef _SOCIALNETWORK_H
#define _SOCIALNETWORK_H

#include "Leader.H"
#include <string>
using namespace std;


class SocialNetwork {
public:
	SocialNetwork(){}

	SocialNetwork(string name, string password);
	//<su much memory to reaease
	~SocialNetwork();

	void AdminLogin(string password);
	void Login(string email, string password);
	void Logout();

	// Admin actions
	void CreateLeader(string name, string email, string password);
	void DeleteUser(string email);

	// Leader actions
	void BroadcastMessage(string subject, string content);

	// Follower actions (also leader actions)
	void CreateFollower(string name, string email, string password);

	void ShowFriendRequests();
	void ShowFriendList();
	void SendFriendRequest(string friendEmail);
	void AcceptFriendRequest(string friendEmail);
	void RemoveFriend(string friendEmail);

	void ShowMessageList(); //<-- need to check if it works as we want
	void ReadMessage(int messageNum);
	void SendMessage(string email, string subject, string content);

	void Follow(string leaderEmail);

	// General actions
	void FindUser(string partialName);
private:
	
	Follower * SearchByEmailFollower(string email);
	Leader * SearchByEmailLeader(string email);
	string name_;
	string password_;
	LinkedList<Follower> follower_user_;
	LinkedList<Leader> leader_user_;
	Current_state user_loged_on_;
	Follower * activeFollower;
	Leader * activeLeader_;
	
};

#endif
