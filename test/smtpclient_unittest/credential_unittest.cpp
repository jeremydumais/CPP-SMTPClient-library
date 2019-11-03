#include "../../src/credential.h"
#include <gtest/gtest.h>

using namespace jed_utils;
using namespace std;

TEST(Credential_Constructor, NullUsername)
{
	try
	{
		Credential cred(nullptr, "123");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_Constructor, EmptyUsername)
{
	try
	{
		Credential cred("", "123");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_Constructor, OnlySpacesUsername)
{
	try
	{
		Credential cred("    ", "123");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_Constructor, NullPassword)
{
	try
	{
		Credential cred("test", nullptr);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Password cannot be null or empty", err.what());
	}
}

TEST(Credential_Constructor, EmptyPassword)
{
	try
	{
		Credential cred("test", "");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Password cannot be null or empty", err.what());
	}
}

TEST(Credential_Constructor, OnlySpacesPassword)
{
	try
	{
		Credential cred("test", "    ");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Password cannot be null or empty", err.what());
	}
}

TEST(Credential_CopyConstructor, CredentialCopyConstructorValid)
{
	Credential* cred1 = new Credential("test", "123");
	Credential cred2(*cred1);
	delete cred1;
	ASSERT_STREQ("test", cred2.getUsername());
	ASSERT_STREQ("123", cred2.getPassword());
}

TEST(Credential_CopyAssignment, CredentialCopyAssignmentValid)
{
	Credential* cred1 = new Credential("test", "123");
	Credential cred2("aaa", "bbb");
	cred2 = *cred1;
	delete cred1;
	ASSERT_STREQ("test", cred2.getUsername());
	ASSERT_STREQ("123", cred2.getPassword());
}

TEST(Credential_MoveConstructor, CredentialMoveConstructorValid)
{
	Credential cred1("test", "123");
	Credential cred2(move(cred1));
	ASSERT_STREQ("test", cred2.getUsername());
	ASSERT_STREQ("123", cred2.getPassword());
	ASSERT_EQ(nullptr, cred1.getUsername());
	ASSERT_EQ(nullptr, cred1.getPassword());
}

//Move Assignment
TEST(Credential_MoveAssignment, CredentialMoveAssignmentValid)
{
	Credential cred1("test", "123");
	Credential cred2("aaa", "bbb");
	cred2 = move(cred1);
	ASSERT_STREQ("test", cred2.getUsername());
	ASSERT_STREQ("123", cred2.getPassword());
	ASSERT_EQ(nullptr, cred1.getUsername());
	ASSERT_EQ(nullptr, cred1.getPassword());
}