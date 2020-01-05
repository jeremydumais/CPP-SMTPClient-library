#ifndef CREDENTIAL_H
#define CREDENTIAL_H

#ifdef _WIN32
	#ifdef SMTPCLIENT_EXPORTS  
		#define CREDENTIAL_API __declspec(dllexport)   
	#else  
		#define CREDENTIAL_API __declspec(dllimport)   
	#endif  
#else
	#define CREDENTIAL_API
#endif

namespace jed_utils
{
    class CREDENTIAL_API Credential
	{
    public:
        Credential(const char *pUsername, const char *pPassword);
        virtual ~Credential();
        Credential(const Credential& other); //Copy constructor
        Credential& operator=(const Credential& other); //Copy assignment
		Credential(Credential&& other) noexcept; //Move constructor
		Credential& operator=(Credential&& other) noexcept; //Move assignement
        const char *getUsername() const;
        const char *getPassword() const;
        void setUsername(const char *pUsername);
        void setPassword(const char *pPassword);
    private:
        char* mUsername;
        char* mPassword;
    };
} // namespace jed_utils

#endif