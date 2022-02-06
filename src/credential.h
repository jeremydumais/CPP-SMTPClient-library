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
    /** @brief The Credential class is used to authenticate with the
     *  SMTP server.
     */
    class CREDENTIAL_API Credential
	{
    public:
    	/**
		 *  @brief  Construct a new Credential. 
		 *  @param pUsername The user name.
		 *  @param pPassword The password.
		 */
        Credential(const char *pUsername, const char *pPassword);
        
		/** The destructor og Credential */
        virtual ~Credential();
        
        /** Credential copy constructor */
        Credential(const Credential& other);
        
        /** Credential copy assignment operator */
        Credential& operator=(const Credential& other);
		
        /** Credential move constructor */
        Credential(Credential&& other) noexcept;
		
        /** Credential move assignment operator */
        Credential& operator=(Credential&& other) noexcept;
        
		/** Return the username. */
        const char *getUsername() const;
        
		/** Return the password. */
        const char *getPassword() const;

        /**
		 *  @brief  Set the user name. 
		 *  @param pUsername A char array pointer of the user name. 
		 */
        void setUsername(const char *pUsername);

        /**
		 *  @brief  Set the password. 
		 *  @param pPassword A char array pointer of the password. 
		 */
        void setPassword(const char *pPassword);
    private:
        char* mUsername;
        char* mPassword;
    };
} // namespace jed_utils

#endif