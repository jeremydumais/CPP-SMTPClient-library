#include "serveroptionsanalyzer.h"

using namespace jed_utils;

// Trim from start
bool ServerOptionsAnalyzer::containsAllOptions(const std::string &optionsStr) {
    std::string sanitizedOptionsStr = [&optionsStr]() {
        if (optionsStr.size() >= 2 && optionsStr.substr(optionsStr.size() - 2) == "\r\n") {
            return optionsStr.substr(0, optionsStr.size() - 2);
        } else {
            return optionsStr;
        }
    }();
    size_t lastLineStart = sanitizedOptionsStr.rfind("\r\n");
    if (lastLineStart == std::string::npos) {
        lastLineStart = 0;
    } else {
        lastLineStart += 2;  // Move past the \r\n
    }
    if (sanitizedOptionsStr.substr(lastLineStart, 4) == "250 ") {
        return true;
    }
    return false;
}
