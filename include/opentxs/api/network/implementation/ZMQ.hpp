/************************************************************
 *
 *                 OPEN TRANSACTIONS
 *
 *       Financial Cryptography and Digital Cash
 *       Library, Protocol, API, Server, CLI, GUI
 *
 *       -- Anonymous Numbered Accounts.
 *       -- Untraceable Digital Cash.
 *       -- Triple-Signed Receipts.
 *       -- Cheques, Vouchers, Transfers, Inboxes.
 *       -- Basket Currencies, Markets, Payment Plans.
 *       -- Signed, XML, Ricardian-style Contracts.
 *       -- Scripted smart contracts.
 *
 *  EMAIL:
 *  fellowtraveler@opentransactions.org
 *
 *  WEBSITE:
 *  http://www.opentransactions.org/
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This Source Code Form is subject to the terms of the
 *   Mozilla Public License, v. 2.0. If a copy of the MPL
 *   was not distributed with this file, You can obtain one
 *   at http://mozilla.org/MPL/2.0/.
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will
 *   be useful, but WITHOUT ANY WARRANTY; without even the
 *   implied warranty of MERCHANTABILITY or FITNESS FOR A
 *   PARTICULAR PURPOSE.  See the Mozilla Public License
 *   for more details.
 *
 ************************************************************/

#ifndef OPENTXS_API_NETWORK_IMPLEMENTATION_ZMQ_HPP
#define OPENTXS_API_NETWORK_IMPLEMENTATION_ZMQ_HPP

#include "opentxs/Version.hpp"

#include "opentxs/api/network/ZMQ.hpp"

#include <atomic>
#include <map>
#include <memory>
#include <mutex>

namespace opentxs
{
class ServerConnection;

namespace network
{
namespace zeromq
{
class Context;
}  // namespace zeromq
}  // namespace network

namespace api
{
class Settings;

namespace implementation
{
class Native;
}  // namespace implementation

namespace network
{
namespace implementation
{

class ZMQ : virtual public opentxs::api::network::ZMQ
{
public:
    const opentxs::network::zeromq::Context& Context() const override;
    std::chrono::seconds KeepAlive() const override;
    void KeepAlive(const std::chrono::seconds duration) const override;
    std::chrono::seconds Linger() override;
    std::shared_ptr<opentxs::network::zeromq::Context> NewContext()
        const override;
    std::chrono::seconds ReceiveTimeout() override;
    void RefreshConfig() override;
    std::chrono::seconds SendTimeout() override;

    ServerConnection& Server(const std::string& id) override;
    bool SetSocksProxy(const std::string& proxy) override;
    std::string SocksProxy() override;
    bool SocksProxy(std::string& proxy) override;
    ConnectionState Status(const std::string& server) const override;

    ~ZMQ();

private:
    friend class opentxs::api::implementation::Native;

    const opentxs::network::zeromq::Context& context_;
    api::Settings& config_;
    std::atomic<std::chrono::seconds> linger_;
    std::atomic<std::chrono::seconds> receive_timeout_;
    std::atomic<std::chrono::seconds> send_timeout_;
    mutable std::atomic<std::chrono::seconds> keep_alive_;
    mutable std::atomic<bool> shutdown_;
    mutable std::mutex lock_;
    std::string socks_proxy_;
    std::map<std::string, std::unique_ptr<ServerConnection>>
        server_connections_;

    bool verify_lock(const Lock& lock) const;

    void init(const Lock& lock);

    ZMQ(const opentxs::network::zeromq::Context& context,
        api::Settings& config);
    ZMQ() = delete;
    ZMQ(const ZMQ&) = delete;
    ZMQ(ZMQ&&) = delete;
    ZMQ& operator=(const ZMQ&) = delete;
    ZMQ& operator=(const ZMQ&&) = delete;
};
}  // namespace implementation
}  // namespace network
}  // namespace api
}  // namespace opentxs
#endif  // OPENTXS_API_NETWORK_IMPLEMENTATION_ZMQ_HPP
