#include "common.h"
#include <Poco/Net/SocketConnector.h>
#include "venus_net/service_application.h"
#include "venus_net/basic_stream.h"
#include "venus_net/stream_writer.h"
#include "venus_net/stream_reader.h"

struct CSTestPacketReq : public NetworkMessage
{
    uint32 uint_value;
    std::string string_value;

    int byteSize()
    {
        return sizeof(uint_value) + (string_value.length() + 2);
    }

    void encode(byte* buffer, size_t size)
    {
        StreamWriter w((char*)buffer, size);
        w << uint_value;
        w << string_value;
    }

    void decode(const byte* buffer, size_t size)
    {
        StreamReader r((const char*)buffer, size);
        r >> uint_value;
        r >> string_value;
    }
};

enum TestCaseType
{
    TC_CONCURRENCY_TESTING,         //短连接并发测试（建立连接随后断开）
    TC_CONNECTION_STRESS_TESTING,   //短连接压力测试（建立连接后发送若干长度数据随后断开）
};

class TestCaseRunner
{
public:
    virtual void run() = 0;
};

int main(int argc, char** argv)
{
    Poco::Net::SocketAddress serverAddress("127.0.0.1:36911");
    Poco::Net::StreamSocket clientConnector;

    try
    {
        std::cout << "starting.." << std::endl;
        for (int i = 0; i < 100; i++)
        {
            clientConnector.connect(serverAddress);
            char buffer[1024] = {0};
            int bytes_receive = clientConnector.receiveBytes(buffer, 1024, 0);
            std::cout << " bytes_receive = " << bytes_receive << std::endl;

            //构造数据包
            CSTestPacketReq requestMessage;
            BasicStreamPtr streamPtr(new BasicStream());
            streamPtr->write((int32)0);
            streamPtr->write(10001);
            streamPtr->resize(NetworkMessage::kHeaderLength + 9);
            requestMessage.encode((byte*)streamPtr->b.begin() + NetworkMessage::kHeaderLength, requestMessage.byteSize());
            streamPtr->rewriteSize(streamPtr->b.size(), streamPtr->b.begin());

            clientConnector.sendBytes(streamPtr->b.begin(), streamPtr->b.size(), 0);
            clientConnector.close();
        }
        std::cout << "finished." << std::endl;
    }
    catch (const Poco::Exception& e)
    {
        std::cout << e.displayText() << std::endl;
    }

    getchar();
    return 0;
}