#include <iostream>

#include <cpp/opportunisticsecuresmtpclient.hpp>
#include <cpp/plaintextmessage.hpp>
#include <cpp/htmlmessage.hpp>

namespace email = jed_utils::cpp;

static const std::string kSenderAddress = "changeme@gmail.com";
static const std::string kPassword = "changeme"; // This will be your access token

template<typename T>
class ClientWrapper {
 public:
    ClientWrapper(T client,
            email::Credential&& credentials) : mClient{std::move(client)} {
        mClient.setCredentials(credentials);
    }

    auto client() -> T& { return mClient; }

 private:
    email::OpportunisticSecureSMTPClient mClient;
};

auto buildClient() -> email::OpportunisticSecureSMTPClient& {
    static ClientWrapper clientWrapper {
        email::OpportunisticSecureSMTPClient{"smtp.gmail.com", 587},
            email::Credential(kSenderAddress, kPassword,
                    jed_utils::RecommendedAuthenticationMethod::kXOauth2)
    };

    return clientWrapper.client();
}

void sendTextEmail() {
    using email::PlaintextMessage;
    using email::MessageAddress;

    auto& client = buildClient();

    PlaintextMessage msg(MessageAddress(kSenderAddress, "Test Address Display"),
            { MessageAddress("radu.cosnita@gmail.com", "Another Address display") },
            "This is a test (Subject)",
            "Hello\nHow are you?");

    int err_no = client.sendMail(msg);
    if (err_no != 0) {
        std::cerr << client.getCommunicationLog() << '\n';
        std::string errorMessage = client.getErrorMessage(err_no);
        std::stringstream err{};
        err << "An error occurred: " << errorMessage << " (error no: " << err_no << ")";
        throw std::invalid_argument{err.str()};
    }

    std::cout << client.getCommunicationLog() << '\n';
    std::cout << "Operation completed!" << std::endl;
}

void generateTestFile() {
    std::ofstream out{"/tmp/test.txt"};
    out << "Generated content" << std::endl;
    out.flush();
    out.close();
}

void sendAttachmentEmail() {
    using email::MessageAddress;
    using email::Attachment;
    using email::PlaintextMessage;

    generateTestFile();

    const auto to = MessageAddress(kSenderAddress);
    const auto& from = to;
    const auto subject = "This is an email with an attachment";
    const auto body = "See attachment";
    const auto attachments = {
        Attachment{"/tmp/test.txt", "test.txt", "test.txt"},
    };

    PlaintextMessage msg{
        from, { to }, subject, body, {}, {}, attachments,
    };

    auto& client = buildClient();

    int err_no = client.sendMail(msg);
    if (err_no != 0) {
        std::cerr << client.getCommunicationLog() << '\n';
        std::string errorMessage = client.getErrorMessage(err_no);
        std::stringstream err{};
        err << "An error occurred: " << errorMessage << " (error no: " << err_no << ")";
        throw std::invalid_argument{err.str()};
    }

    std::cout << client.getCommunicationLog() << '\n';
    std::cout << "Operation completed!" << std::endl;
}

void sendHTMLEmail() {
    using email::MessageAddress;
    using email::Attachment;
    using email::HTMLMessage;

    const auto to = MessageAddress(kSenderAddress);
    const auto& from = to;
    const auto subject = "This is an email with an attachment";
    const auto body = "<html><body><h1>This is a html formatted email</h1></body></html>";
    const auto attachments = {
        Attachment{"/tmp/test.txt", "test.txt", "test.txt"},
    };

    HTMLMessage msg(from, { to }, subject, body, {}, {}, attachments);

    auto& client = buildClient();

    int err_no = client.sendMail(msg);
    if (err_no != 0) {
        std::cerr << client.getCommunicationLog() << '\n';
        std::string errorMessage = client.getErrorMessage(err_no);
        std::stringstream err{};
        err << "An error occurred: " << errorMessage << " (error no: " << err_no << ")";
        throw std::invalid_argument{err.str()};
    }

    std::cout << client.getCommunicationLog() << '\n';
    std::cout << "Operation completed!" << std::endl;
}

auto main() -> int {
    sendTextEmail();
    sendAttachmentEmail();
    sendHTMLEmail();
    return 0;
}
