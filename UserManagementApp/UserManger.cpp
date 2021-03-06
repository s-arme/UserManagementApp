#include "UserManger.h"
#include<iostream>
#include<list>
using namespace std;

CurrentUser* CurrentUser::instance = 0;
User* CurrentUser::cu = nullptr;
std::list<User> userList({ User("cppadmin","q!Edf@42b"), });
CurrentUser* CurrentUser::getInstance() {
	if (instance == 0) {
		instance = new CurrentUser();
	};
	return instance;
}
Errors CurrentUser::login(User* user) {
	if (cu != nullptr) {
		return ALREADYLOGGEDIN;
	}
	this->cu = user;
	return SUCCESSFULLLOGIN;
}

Errors CurrentUser::logout() {
	if (cu == nullptr) {
		return ALREADYLOGGEDOUT;
	}
	this->cu = nullptr;
	return Ok;
}

Errors CurrentUser::operator()(string & username, string & password) {
	for (User a : userList) {
		if (a.getUsername() == username) {
			if (a.checkPassword(password)) {
				return login(&a);
			}
			return PASSWORDWRONG;
		}
	}
	return USERNAMENOTFOUND;
}

bool CurrentUser::isLoggedIn() {
	if (cu == nullptr) {
		return false;
	}
	return true;
}

Errors signUp(string firstname, string lastname, string username, string password) {
	if (password.length() < 8) {
		return PasswordLength;
	}
	for (User a : userList) {
		if (a.getUsername() == username) {
			return ExistingUser;
		}
	}
	User user(username, password, firstname, lastname);
	userList.push_back(user);
	return Ok;
}