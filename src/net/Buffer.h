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

    size_t ReadFromFd(int fd);

    void Append(const char* begin, size_t len);

    size_t ReadableBytes() const
    { return write_index_ - read_index_; }

    size_t WriteableBytes() const
    { return buffer_.size() - write_index_;}

    void AddReadIndex(size_t bytes);

    void AddWriteIndex(size_t bytes);

    const char* Begin() const
    { return &*buffer_.begin(); }

    char* Begin()
    { return &*buffer_.begin(); }

    char* WriteBegin()
    { return Begin() + write_index_; }

    char* ReadBegin()
    { return Begin() + read_index_; }

    void DropAllData();

    std::string ReadAllAsString();
    std::string ReadBytesAsString(size_t bytes);

    /**
     * peek int32 from buffer and transform form network to host
     * @return
     */
    int32_t PeekInt32();

private:

    const static int DEFAULT_BUFFER_SIZE = 1024;
    const static int BUFFER_BEGIN = 8;

    size_t read_index_;
    size_t write_index_;
    std::vector<char> buffer_;

    void EnsureWriteBytes(size_t len);

    void ExpanseBuffer(size_t len);
};
}
}
#endif //MONGO_SRC_NET_BUFFER_H
