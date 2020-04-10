//
// Created by lsmg on 4/10/20.
//

#ifndef MONGO_SRC_NET_ENDIAN_H
#define MONGO_SRC_NET_ENDIAN_H
#include <cstdint>
#include <endian.h>
namespace mongo
{
namespace net
{
namespace sockets
{
inline int32_t NetworkToHost32(int32_t num)
{
    return be32toh(num);
}
inline int32_t HostToNetwork32(int32_t num)
{
    return htobe32(num);
}

}
}
}


#endif //MONGO_SRC_NET_ENDIAN_H
