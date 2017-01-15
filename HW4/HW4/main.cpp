#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#include <stdlib.h>
#include <crtdbg.h>
#include <cstdio>

#include "SocialNetwork.H"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif  // _DEBUG

using namespace std;



int stringToInt(const string s) {
	istringstream istr(s);
	int i = 0;
	istr >> i;
	return i;
}

vector<string> tokenize(string line, const char* delim) {
	unsigned int i, j;
	vector<string> tokens;
	while (!line.empty()) {
		i = line.find_first_not_of(delim);
		j = line.find_first_of(delim, i + 1);
		tokens.push_back(line.substr(i, j - i));
		if (j > line.size() - 1)
			line = "";
		else
			line = line.substr(j + 1, line.size() - j - 1);
	}
	return tokens;
}

int main(int argc, char **argv) {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//_CrtSetBreakAlloc(3142);
	SocialNetwork SocNetwork("MamatNet", "1234");
	const char* delims = " \t\n";
	vector<string> tokens;
	string line, subject, content, email;

	std::ifstream input(fopen(argv[1], "r"));




	while (getline(input, line)) {
		//getline(input, line);
		tokens = tokenize(line, delims);
		if (tokens.size() == 0) {
			continue;
		}

		if (tokens[0] == "AdminLogin") {
			SocNetwork.AdminLogin(tokens[1]);
			continue;
		}

		if (tokens[0] == "Login") {
			SocNetwork.Login(tokens[1], tokens[2]);
			continue;
		}

		if (tokens[0] == "Logout") {
			SocNetwork.Logout();
			continue;
		}

		if (tokens[0] == "CreateLeader") {
			SocNetwork.CreateLeader(tokens[1], tokens[2], tokens[3]);
			continue;
		}

		if (tokens[0] == "DeleteUser") {
			SocNetwork.DeleteUser(tokens[1]);
			continue;
		}

		if (tokens[0] == "BroadcastMessage") {
			cout << "Subject: ";
			getline(input, subject);
			cout << "Content: ";
			getline(input, content);
			SocNetwork.BroadcastMessage(subject, content);
			continue;
		}

		if (tokens[0] == "CreateFollower") {
			SocNetwork.CreateFollower(tokens[1], tokens[2], tokens[3]);
			continue;
		}

		if (tokens[0] == "ShowFriendRequests") {
			SocNetwork.ShowFriendRequests();
			continue;
		}

		if (tokens[0] == "ShowFriendList") {
			SocNetwork.ShowFriendList();
			continue;
		}

		if (tokens[0] == "SendFriendRequest") {
			SocNetwork.SendFriendRequest(tokens[1]);
			continue;
		}

		if (tokens[0] == "AcceptFriendRequest") {
			SocNetwork.AcceptFriendRequest(tokens[1]);
			continue;
		}

		if (tokens[0] == "RemoveFriend") {
			SocNetwork.RemoveFriend(tokens[1]);
			continue;
		}

		if (tokens[0] == "ShowMessageList") {
			SocNetwork.ShowMessageList();
			continue;
		}

		if (tokens[0] == "ReadMessage") {
			SocNetwork.ReadMessage(stringToInt(tokens[1]));
			continue;
		}

		if (tokens[0] == "SendMessage") {
			cout << "Email: ";
			getline(input, email);
			cout << "Subject: ";
			getline(input, subject);
			cout << "Content: ";
			getline(input, content);
			SocNetwork.SendMessage(email, subject, content);
			continue;
		}

		if (tokens[0] == "Follow") {
			SocNetwork.Follow(tokens[1]);
			continue;
		}

		if (tokens[0] == "FindUser") {
			SocNetwork.FindUser(tokens[1]);
			continue;
		}

		if (tokens[0] == "Exit") {
			break;
		}

		cerr << "Invalid input" << endl;
	}
	_CrtDumpMemoryLeaks();
	return 0;
};
