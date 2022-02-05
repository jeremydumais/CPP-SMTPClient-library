#include "credential.h"
#include "stringutils.h"
#include <cstring>
#include <stdexcept>

using namespace jed_utils;

Credential::Credential(const char *pUsername, const char *pPassword)
    : mUsername(nullptr),
      mPassword(nullptr)
{   
    std::string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw std::invalid_argument("Username cannot be null or empty");
    }

    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw std::invalid_argument("Password cannot be null or empty");
    }

    size_t username_len = strlen(pUsername);
	mUsername = new char[username_len + 1];
	strcpy(mUsername, pUsername);

    size_t password_len = strlen(pPassword);
	mPassword = new char[password_len + 1];
	strcpy(mPassword, pPassword);
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
	strcpy(mUsername, other.mUsername);
    strcpy(mPassword, other.mPassword);
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
		strcpy(mUsername, other.mUsername);
        //mPassword
		mPassword = new char[strlen(other.mPassword) + 1];
		strcpy(mPassword, other.mPassword);
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
	std::string username_str { pUsername == nullptr ? "" : pUsername };
    if (pUsername == nullptr || strcmp(pUsername, "") == 0 || StringUtils::trim(username_str).empty()) {
        throw std::invalid_argument("Username cannot be null or empty");
    }

	delete []mUsername;
	size_t username_len = strlen(pUsername);
	mUsername = new char[username_len + 1];
	strcpy(mUsername, pUsername);
}

void Credential::setPassword(const char *pPassword)
{
    if (pPassword == nullptr || strcmp(pPassword, "") == 0) {
        throw std::invalid_argument("Password cannot be null or empty");
    }

	delete []mPassword;
    size_t password_len = strlen(pPassword);
	mPassword = new char[password_len + 1];
	strcpy(mPassword, pPassword);
}