/**
 * Author:    Andrea Casalino
 * Created:   01.28.2020
 *
 * report any bug to andrecasa91@gmail.com.
 **/

#include <MinimalSocket/Error.h>
#include <MinimalSocket/core/Address.h>

#include "../Commons.h"

#include <sstream>

namespace MinimalSocket {
std::unique_ptr<Address> Address::makeAddress(const std::string &hostIp,
                                              const Port &port) {
  std::unique_ptr<Address> result;
  result.reset(new Address{});
  result->host = hostIp;
  result->port = port;

  if (std::nullopt != makeSocketIp4(hostIp, port)) {
    result->family = AddressFamily::IP_V4;
    return result;
  }

  if (std::nullopt != makeSocketIp6(hostIp, port)) {
    result->family = AddressFamily::IP_V6;
    return result;
  }

  return nullptr;
}

namespace {
static const std::string LOCALHOST_IPv4 = "127.0.0.1";
static const std::string LOCALHOST_IPv6 = "::1";
} // namespace

Address Address::makeLocalHost(const std::uint16_t &port,
                               const AddressFamily &family) {
  Address result;
  result.port = port;
  result.family = family;
  address_case(
      family, [&result]() { result.host = LOCALHOST_IPv4; },
      [&result]() { result.host = LOCALHOST_IPv6; });
  return result;
}

bool Address::operator==(const Address &o) const {
  return (this->host == o.host) && (this->port == o.port) &&
         (this->family == o.family);
}

std::string to_string(const Address &subject) {
  std::stringstream stream;
  stream << subject.getHost() << ':' << subject.getPort();
  return stream.str();
}

std::optional<AddressFamily>
deduceAddressFamily(const std::string &host_address) {
  auto temp = Address::makeAddress(host_address, 0);
  if (nullptr == temp) {
    return std::nullopt;
  }
  return temp->getFamily();
}

bool isValidAddress(const std::string &host_address) {
  return deduceAddressFamily(host_address) != std::nullopt;
}
} // namespace MinimalSocket
