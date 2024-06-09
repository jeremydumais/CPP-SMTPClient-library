#ifndef SERVEROPTIONSANALYZER_H
#define SERVEROPTIONSANALYZER_H

#include <string>

#ifdef _WIN32
    #ifdef SMTPCLIENT_EXPORTS
        #define SERVEROPTIONSANALYZER_API __declspec(dllexport)
    #else
        #define SERVEROPTIONSANALYZER_API __declspec(dllimport)
    #endif
#else
    #define SERVEROPTIONSANALYZER_API
#endif

namespace jed_utils {
/** @brief The ServerOptionsAnalyzer class provides utility fonctions to
 * analyzer the SMTP options that are available by the server.
*/
class SERVEROPTIONSANALYZER_API ServerOptionsAnalyzer {
 public:
    /**
     *  @brief Indicate if the server has returned all it's available options
     *  or of there still a reply with other options to come.
     *  @param optionsStr The string that contains the option list returned by
     *  the SMTP server.
     */
    static bool containsAllOptions(const std::string &optionsStr);
};
}  // namespace jed_utils


#endif  // SERVEROPTIONSANALYZER_H
