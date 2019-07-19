#include "InetAddress.h"
#include <WinSock2.h>

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma warning (disable: 4996)

namespace Network {

const unsigned long InetAddress::NONE = INADDR_NONE;

InetAddress::InetAddress(unsigned long address)
    :mIPAddress(address) {}

InetAddress::InetAddress(const std::string& address) {
    unsigned long uaddr = ::inet_addr(address.c_str());
    if (uaddr == NONE) {
        hostent* ent = ::gethostbyname(address.c_str());
        if (ent != 0 && ent->h_addr_list[0] != 0) {
            uaddr = *(unsigned long*)ent->h_addr_list[0];
        }
    }
    mIPAddress = uaddr;
}

InetAddress::~InetAddress() {}

std::string InetAddress::getHostAddress() const {
    in_addr addr;
    addr.S_un.S_addr = mIPAddress;
    return std::string(inet_ntoa(addr));
}

InetAddress& InetAddress::operator=(const InetAddress& other) {
    mIPAddress = other.mIPAddress;
    return *this;
}

InetAddress& InetAddress::operator=(const std::string& host) {
    *this = InetAddress(host);
    return *this;
}

} //Network 
