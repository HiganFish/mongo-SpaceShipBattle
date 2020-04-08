//
// Created by lsmg on 4/8/20.
//

#include <Buffer.h>
#include <fcntl.h>
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>
int main()
{
    mongo::net::Buffer buffer;

    struct stat read_stat;
    struct stat write_stat;
    int read_fd = open("/home/lsmg/web/atom.xml", O_RDONLY);
    int write_fd = open("/home/lsmg/web/atom.xml.back", O_WRONLY | O_CREAT);
    assert(read_fd != -1);
    fstat(read_fd, &read_stat);

    size_t sum_bytes = 0;
    size_t read_bytes = 1;
    while (read_bytes != 0)
    {
        read_bytes = buffer.ReadFromFd(read_fd);
        assert(read_bytes >= 0);
        sum_bytes += read_bytes;

        std::string out = buffer.ReadBytesAsString(read_bytes);
        write(write_fd, out.c_str(), out.size());
    }

    printf("sum read %ld bytes\n", read_stat.st_size);

    fstat(write_fd, &write_stat);
    printf("sum write %ld bytes\n", write_stat.st_size);
}