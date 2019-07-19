#include "InetSocketAddress.h"

namespace Network {
InetSocketAddress::InetSocketAddress(const InetAddress& address, int port)
    :mAddress(address), mPort(port) {}

InetSocketAddress::~InetSocketAddress() {}

} //Network 
