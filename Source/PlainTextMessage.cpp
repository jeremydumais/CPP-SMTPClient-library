#include "../Include/PlainTextMessage.h"

using namespace std;
using namespace jed_utils;

PlaintextMessage::PlaintextMessage(const MessageAddress &pFrom,
        const MessageAddress &pTo,
        const string &pSubject,
        const string &pBody,
        const vector<MessageAddress> &pCc,
        const vector<MessageAddress> &pBcc,
        const vector<Attachment> &pAttachments) 
    : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments)
{
}

PlaintextMessage::PlaintextMessage(const MessageAddress &pFrom,
        const vector<MessageAddress> &pTo,
        const string &pSubject,
        const string &pBody,
        const vector<MessageAddress> &pCc,
        const vector<MessageAddress> &pBcc,
        const vector<Attachment> &pAttachments) 
    : Message(pFrom, pTo, pSubject, pBody, pCc, pBcc, pAttachments)
{
}

const string PlaintextMessage::getMimeType() const
{
    return "text/plain";
}

