#ifndef _SOCIALNETWORK_H
#define _SOCIALNETWORK_H

#include "defs.H"
#include <string>
using namespace std;


class SocialNetwork {
public:
	SocialNetwork(string name, string password);
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

	void ShowMessageList();
	void ReadMessage(int messageNum);
	void SendMessage(string email, string subject, string content);

	void Follow(string leaderEmail);

	// General actions
	void FindUser(string partialName);
private:
    // To do
};

#endif
