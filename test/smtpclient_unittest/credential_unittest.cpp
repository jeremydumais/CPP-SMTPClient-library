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

TEST(Credential_Constructor, ValidOnlySpacesPassword)
{
	Credential cred("Test3", "   ");
	ASSERT_STREQ("   ", cred.getPassword());
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

TEST(Credential_getUsername, ValidUsername)
{
	Credential cred("Test3", "123");
	ASSERT_STREQ("Test3", cred.getUsername());
}

TEST(Credential_getPassword, ValidPassword)
{
	Credential cred("Test3", "123");
	ASSERT_STREQ("123", cred.getPassword());
}

TEST(Credential_setUsername, ValidUsername)
{
	Credential cred("Test3", "123");
	cred.setUsername("Test4");
	ASSERT_STREQ("Test4", cred.getUsername());
}

TEST(Credential_setUsername, NullUsername)
{
	Credential cred("Test", "123");	
	try
	{
		cred.setUsername(nullptr);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_setUsername, EmptyUsername)
{
	Credential cred("Test", "123");	
	try
	{
		cred.setUsername("");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_setUsername, OnlySpacesUsername)
{
	Credential cred("Test", "123");	
	try
	{
		cred.setUsername("    ");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Username cannot be null or empty", err.what());
	}
}

TEST(Credential_setPassword, ValidPassword)
{
	Credential cred("Test3", "123");
	cred.setPassword("432");
	ASSERT_STREQ("432", cred.getPassword());
}

TEST(Credential_setPassword, NullPassword)
{
	Credential cred("Test", "123");	
	try
	{
		cred.setPassword(nullptr);
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Password cannot be null or empty", err.what());
	}
}

TEST(Credential_setPassword, EmptyPassword)
{
	Credential cred("Test", "123");	
	try
	{
		cred.setPassword("");
		FAIL();
	}
	catch(invalid_argument &err) 
	{
        ASSERT_STREQ("Password cannot be null or empty", err.what());
	}
}

TEST(Credential_setPassword, ValidOnlySpacesPassword)
{
	Credential cred("Test3", "123");
	cred.setPassword("   ");
	ASSERT_STREQ("   ", cred.getPassword());
}
