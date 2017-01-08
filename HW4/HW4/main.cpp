#include "SocialNetwork.H"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

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
		j = line.find_first_of(delim, i+1);
		tokens.push_back(line.substr(i, j-i));
		if (j > line.size()-1)
			line = "";
		else
			line = line.substr(j+1,line.size()-j-1);
	}
	return tokens;
}

int main() {

	SocialNetwork SocNetwork("MamatNet", "1234");
	const char* delims = " \t\n";
	vector<string> tokens;
	string line, subject, content, email;

	while (!cin.eof()) {
		getline(cin, line);
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
			getline(cin, subject);
			cout << "Content: ";
			getline(cin, content);
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
			getline(cin, email);
			cout << "Subject: ";
			getline(cin, subject);
			cout << "Content: ";
			getline(cin, content);
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
	return 0; 
};
