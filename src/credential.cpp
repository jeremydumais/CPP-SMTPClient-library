#include "credential.h"
#include <cstring>
#include <stdexcept>
#include "stringutils.h"

using namespace jed_utils;
using namespace std;

Credential::Credential(const char *pUsername, const char *pPassword)
    : mUsername(nullptr),
      mPassword(nullptr)
{   
    string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw invalid_argument("Username cannot be null or empty");
    }

    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw invalid_argument("Password cannot be null or empty");
    }

    size_t username_len = strlen(pUsername);
	mUsername = new char[username_len + 1];
	strncpy(mUsername, pUsername, username_len);
    mUsername[username_len] = '\0';

    size_t password_len = strlen(pPassword);
	mPassword = new char[password_len + 1];
	strncpy(mPassword, pPassword, password_len);
    mPassword[password_len] = '\0';
}

Credential::~Credential()
{   
    delete []mUsername;
    delete []mPassword;
}

//Copy constructor
Credential::Credential(const Credential& other)
	: mUsername(new char[strlen(other.mUsername) + 1]),
      mPassword(new char[strlen(other.mPassword) + 1])
{
	strncpy(mUsername, other.mUsername, strlen(other.mUsername) + 1);
	mUsername[strlen(other.mUsername)] = '\0';

    strncpy(mPassword, other.mPassword, strlen(other.mPassword) + 1);
	mPassword[strlen(other.mPassword)] = '\0';
}

//Assignment operator
Credential& Credential::operator=(const Credential& other)
{
	if (this != &other)
	{
		delete[] mUsername;
		delete[] mPassword;
		//mUsername
		mUsername = new char[strlen(other.mUsername) + 1];
		strncpy(mUsername, other.mUsername, strlen(other.mUsername) + 1);
		mUsername[strlen(other.mUsername)] = '\0';
        //mPassword
		mPassword = new char[strlen(other.mPassword) + 1];
		strncpy(mPassword, other.mPassword, strlen(other.mPassword) + 1);
		mPassword[strlen(other.mPassword)] = '\0';
	}
	return *this;
}

//Move constructor
Credential::Credential(Credential&& other) noexcept
	: mUsername(other.mUsername),
      mPassword(other.mPassword)
{
	// Release the data pointer from the source object so that the destructor 
	// does not free the memory multiple times.
	other.mUsername = nullptr;
	other.mPassword = nullptr;
}

//Move assignement operator
Credential& Credential::operator=(Credential&& other) noexcept
{
	if (this != &other)
	{
		delete[] mUsername;
		delete[] mPassword;
		// Copy the data pointer and its length from the source object.
		mUsername = other.mUsername;
		mPassword = other.mPassword;
		// Release the data pointer from the source object so that
		// the destructor does not free the memory multiple times.
		other.mUsername = nullptr;
		other.mPassword = nullptr;
	}
	return *this;
}


const char *Credential::getUsername() const
{
    return mUsername;
}

const char *Credential::getPassword() const
{
    return mPassword;
}

void Credential::setUsername(const char *pUsername)
{
	string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw invalid_argument("Username cannot be null or empty");
    }

	delete []mUsername;
	size_t username_len = strlen(pUsername);
	mUsername = new char[username_len + 1];
	strncpy(mUsername, pUsername, username_len);
    mUsername[username_len] = '\0';
}

void Credential::setPassword(const char *pPassword)
{
    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw invalid_argument("Password cannot be null or empty");
    }

	delete []mPassword;
    size_t password_len = strlen(pPassword);
	mPassword = new char[password_len + 1];
	strncpy(mPassword, pPassword, password_len);
    mPassword[password_len] = '\0';
}