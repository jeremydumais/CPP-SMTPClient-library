#include "htmlmessage.h"

using namespace std;
using namespace jed_utils;

HTMLMessage::HTMLMessage(const MessageAddress &pFrom,
        const MessageAddress &pTo,
        const string &pSubject,
        const string &pBody,
        const vector<MessageAddress> &pCc,
        const vector<MessageAddress> &pBcc,
        const vector<Attachment> &pAttachments) 
    : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments)
{
}

HTMLMessage::HTMLMessage(const MessageAddress &pFrom,
        const vector<MessageAddress> &pTo,
        const string &pSubject,
        const string &pBody,
        const vector<MessageAddress> &pCc,
        const vector<MessageAddress> &pBcc,
        const vector<Attachment> &pAttachments) 
    : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments)
{
}

const string HTMLMessage::getMimeType() const
{
    return "text/html";
}

