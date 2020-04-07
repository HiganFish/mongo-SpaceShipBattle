//
// Created by lsmg on 4/7/20.
//

#ifndef MONGO_SRC_NET_BUFFER_H
#define MONGO_SRC_NET_BUFFER_H

#include <vector>
#include <cstddef>
#include <string>

namespace mongo
{
namespace net
{
class Buffer
{
public:
    Buffer();
    ~Buffer();

    int ReadFromFd(int sockfd);

    void SaveData(const char* begin, size_t len);

    size_t ReadableBytes() const
    { return write_index_ - read_index_; }

    size_t WriteableBytes() const
    { return buffer_.size() - write_index_;}

    void MoveReadIndex(size_t bytes);

    void MoveWriteIndex(size_t bytes);

    const char* Begin() const
    { return &buffer_[read_index_]; }

    std::string ReadAllAsString();
    std::string ReadBytesAsString(size_t bytes);
private:

    const static int DEFAULT_BUFFER_SIZE = 1024;
    const static int BUFFER_BEGIN = 8;

    size_t read_index_;
    size_t write_index_;
    std::vector<char> buffer_;

    void MoveReadIndexToEnd();
};
}
}
#endif //MONGO_SRC_NET_BUFFER_H
