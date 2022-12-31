#include "message.h"
#include <cstddef>
#include <iterator>
#include <utility>

using namespace jed_utils;

Message::Message(const MessageAddress &pFrom,
        const MessageAddress &pTo,
        const char *pSubject,
        const char *pBody,
        const MessageAddress *pCc,
        const MessageAddress *pBcc,
        const Attachment pAttachments[],
        size_t pAttachmentsSize)
    : Message(pFrom, &pTo, 1, pSubject, pBody,
            pCc, pCc != nullptr ? 1 : 0,
            pBcc, pBcc != nullptr ? 1 : 0,
            pAttachments, pAttachmentsSize) {
}

Message::Message(const MessageAddress &pFrom,
        const MessageAddress pTo[],
        size_t pToCount,
        const char *pSubject,
        const char *pBody,
        const MessageAddress pCc[],
        size_t pCcCount,
        const MessageAddress pBcc[],
        size_t pBccCount,
        const Attachment pAttachments[],
        size_t pAttachmentsSize)
    : mFrom(pFrom),
      mTo(nullptr),
      mToCount(pToCount),
      mCc(nullptr),
      mCCCount(pCcCount),
      mBcc(nullptr),
      mBCCCount(pBccCount),
      mSubject(nullptr),
      mBody(nullptr),
      mAttachments(nullptr),
      mAttachmentCount(pAttachmentsSize) {
    if (pSubject == nullptr) {
        mSubject = new char('\0');
    } else {
        size_t subject_len = strlen(pSubject);
        mSubject = new char[subject_len + 1];
        strncpy(mSubject, pSubject, subject_len);
        mSubject[subject_len] = '\0';
    }

    if (pBody == nullptr) {
        mBody = new char('\0');
    } else {
        size_t body_len = strlen(pBody);
        mBody = new char[body_len + 1];
        strncpy(mBody, pBody, body_len);
        mBody[body_len] = '\0';
    }

    if (pTo != nullptr) {
        mTo = new MessageAddress*[mToCount];
        for (unsigned int index = 0; index < mToCount; index++) {
            mTo[index] = new MessageAddress(pTo[index]);
        }
    }

    if (pCc != nullptr) {
        mCc = new MessageAddress*[mCCCount];
        for (unsigned int index = 0; index < mCCCount; index++) {
            mCc[index] = new MessageAddress(pCc[index]);
        }
    }

    if (pBcc != nullptr) {
        mBcc = new MessageAddress*[mBCCCount];
        for (unsigned int index = 0; index < mBCCCount; index++) {
            mBcc[index] = new MessageAddress(pBcc[index]);
        }
    }

    if (pAttachments != nullptr) {
        mAttachments = new Attachment*[mAttachmentCount];
        for (unsigned int index = 0; index < mAttachmentCount; index++) {
            mAttachments[index] = new Attachment(pAttachments[index]);
        }
    }
}

Message::~Message() {
    delete[] mSubject;
    mSubject = nullptr;
    delete[] mBody;
    mBody = nullptr;
    // To
    if (mTo != nullptr) {
        for (unsigned int i = 0; i < mToCount; i++) {
            delete mTo[i];
        }
        delete[] mTo;
    }
    mTo = nullptr;
    // Cc
    if (mCc != nullptr) {
        for (unsigned int i = 0; i < mCCCount; i++) {
            delete mCc[i];
        }
        delete[] mCc;
    }
    mCc = nullptr;
    // Bcc
    if (mBcc != nullptr) {
        for (unsigned int i = 0; i < mBCCCount; i++) {
            delete mBcc[i];
        }
        delete[] mBcc;
    }
    mBcc = nullptr;
    // Attachment
    if (mAttachments != nullptr) {
        for (unsigned int i = 0; i < mAttachmentCount; i++) {
            delete mAttachments[i];
        }
        delete[] mAttachments;
    }
    mAttachments = nullptr;
}

// Copy constructor
Message::Message(const Message &other)
    : mFrom(other.mFrom),
      mTo(nullptr),
      mToCount(other.mToCount),
      mCc(nullptr),
      mCCCount(other.mCCCount),
      mBcc(nullptr),
      mBCCCount(other.mBCCCount),
      mSubject(new char[strlen(other.mSubject) + 1]),
      mBody(new char[strlen(other.mBody) + 1]),
      mAttachments(nullptr),
      mAttachmentCount(other.mAttachmentCount) {
    size_t body_len = strlen(other.mBody);
    strncpy(mBody, other.mBody, body_len);
    mBody[body_len] = '\0';

    size_t subject_len = strlen(other.mSubject);
    strncpy(mSubject, other.mSubject, subject_len);
    mSubject[subject_len] = '\0';

    // mTo
    if (other.mToCount > 0) {
        mTo = new MessageAddress*[other.mToCount];
        for (unsigned int i = 0; i < other.mToCount; i++) {
            mTo[i] = new MessageAddress(*other.mTo[i]);
        }
    }

    // mCc
    if (other.mCCCount > 0) {
        mCc = new MessageAddress*[other.mCCCount];
        for (unsigned int i = 0; i < other.mCCCount; i++) {
            mCc[i] = new MessageAddress(*other.mCc[i]);
        }
    }

    // mBcc
    if (other.mBCCCount > 0) {
        mBcc = new MessageAddress*[other.mBCCCount];
        for (unsigned int i = 0; i < other.mBCCCount; i++) {
            mBcc[i] = new MessageAddress(*other.mBcc[i]);
        }
    }

    // mAttachment
    if (other.mAttachmentCount > 0) {
        mAttachments = new Attachment*[other.mAttachmentCount];
        for (unsigned int i = 0; i < other.mAttachmentCount; i++) {
            mAttachments[i] = new Attachment(*other.mAttachments[i]);
        }
    }
}

// Copy assignment
Message& Message::operator=(const Message &other) {
    if (this != &other) {
        // mSubject
        delete[] mSubject;
        size_t subject_len = strlen(other.mSubject);
        mSubject = new char[subject_len + 1];
        strncpy(mSubject, other.mSubject, subject_len);
        mSubject[subject_len] = '\0';
        // mBody
        delete[] mBody;
        size_t body_len = strlen(other.mBody);
        mBody = new char[body_len + 1];
        strncpy(mBody, other.mBody, body_len);
        mBody[body_len] = '\0';
        // mTo and mToCount
        if (mToCount > 0) {
            for (unsigned int i = 0; i < mToCount; i++) {
                delete mTo[i];
            }
            delete[] mTo;
        }
        if (other.mToCount > 0) {
            mTo = new MessageAddress*[other.mToCount];
            for (unsigned int i = 0; i < other.mToCount; i++) {
                mTo[i] = new MessageAddress(*other.mTo[i]);
            }
        }
        mToCount = other.mToCount;
        // mCc and mCCCount
        if (mCCCount > 0) {
            for (unsigned int i = 0; i < mCCCount; i++) {
                delete mCc[i];
            }
            delete[] mCc;
        }
        if (other.mCCCount > 0) {
            mCc = new MessageAddress*[other.mCCCount];
            for (unsigned int i = 0; i < other.mCCCount; i++) {
                mCc[i] = new MessageAddress(*other.mCc[i]);
            }
        }
        mCCCount = other.mCCCount;
        // mBcc and mBCCCount
        if (mBCCCount > 0) {
            for (unsigned int i = 0; i < mBCCCount; i++) {
                delete mBcc[i];
            }
            delete[] mBcc;
        }
        if (other.mBCCCount > 0) {
            mBcc = new MessageAddress*[other.mBCCCount];
            for (unsigned int i = 0; i < other.mBCCCount; i++) {
                mBcc[i] = new MessageAddress(*other.mBcc[i]);
            }
        }
        mBCCCount = other.mBCCCount;
        // Attachments and mAttachmentCount
        if (mAttachmentCount > 0) {
            for (unsigned int i = 0; i < mAttachmentCount; i++) {
                delete mAttachments[i];
            }
            delete[] mAttachments;
        }
        if (other.mAttachmentCount > 0) {
            mAttachments = new Attachment*[other.mAttachmentCount];
            for (unsigned int i = 0; i < other.mAttachmentCount; i++) {
                mAttachments[i] = new Attachment(*other.mAttachments[i]);
            }
        }
        mAttachmentCount = other.mAttachmentCount;
    }
    return *this;
}

// Move constructor
Message::Message(Message &&other) noexcept
    : mFrom(std::move(other.mFrom)),
      mTo(other.mTo),
      mToCount(other.mToCount),
      mCc(other.mCc),
      mCCCount(other.mCCCount),
      mBcc(other.mBcc),
      mBCCCount(other.mBCCCount),
      mSubject(other.mSubject),
      mBody(other.mBody),
      mAttachments(other.mAttachments),
      mAttachmentCount(other.mAttachmentCount) {
    // Release the data pointer from the source object so that the destructor
    // does not free the memory multiple times.
    other.mTo = nullptr;
    other.mToCount = 0;
    other.mCc = nullptr;
    other.mCCCount = 0;
    other.mBcc = nullptr;
    other.mBCCCount = 0;
    other.mSubject = nullptr;
    other.mBody = nullptr;
    other.mAttachments = nullptr;
    other.mAttachmentCount = 0;
}

// Move assignement
Message& Message::operator=(Message &&other) noexcept {
    if (this != &other) {
        delete[] mSubject;
        delete[] mBody;
        // mTo
        if (mTo != nullptr) {
            for (unsigned int i = 0; i < mToCount; i++) {
                delete mTo[i];
            }
            delete[] mTo;
        }
        // mCc
        if (mCc != nullptr) {
            for (unsigned int i = 0; i < mCCCount; i++) {
                delete mCc[i];
            }
            delete[] mCc;
        }
        // mBcc
        if (mBcc != nullptr) {
            for (unsigned int i = 0; i < mBCCCount; i++) {
                delete mBcc[i];
            }
            delete[] mBcc;
        }
        // mAttachments
        if (mAttachments != nullptr) {
            for (unsigned int i = 0; i < mAttachmentCount; i++) {
                delete mAttachments[i];
            }
            delete[] mAttachments;
        }
        // Copy the data pointer and its length from the
        // source object.
        mFrom = other.mFrom;
        mSubject = other.mSubject;
        mBody = other.mBody;
        mTo = other.mTo;
        mToCount = other.mToCount;
        mCc = other.mCc;
        mCCCount = other.mCCCount;
        mBcc = other.mBcc;
        mBCCCount = other.mBCCCount;
        mAttachments = other.mAttachments;
        mAttachmentCount = other.mAttachmentCount;
        // Release the data pointer from the source object so that
        // the destructor does not free the memory multiple times.
        other.mSubject = nullptr;
        other.mBody = nullptr;
        other.mTo = nullptr;
        other.mToCount = 0;
        other.mCc = nullptr;
        other.mCCCount = 0;
        other.mBcc = nullptr;
        other.mBCCCount = 0;
        other.mAttachments = nullptr;
        other.mAttachmentCount = 0;
    }
    return *this;
}

MessageAddress **Message::getTo() const {
    return mTo;
}

size_t Message::getToCount() const {
    return mToCount;
}

const char *Message::getSubject() const {
    return mSubject;
}

const char *Message::getBody() const {
    return mBody;
}

MessageAddress **Message::getCc() const {
    return mCc;
}

size_t Message::getCcCount() const {
    return mCCCount;
}

MessageAddress **Message::getBcc() const {
    return mBcc;
}

size_t Message::getBccCount() const {
    return mBCCCount;
}

const MessageAddress &Message::getFrom() const {
    return mFrom;
}

Attachment **Message::getAttachments() const {
    return mAttachments;
}

size_t Message::getAttachmentsCount() const {
    return mAttachmentCount;
}

