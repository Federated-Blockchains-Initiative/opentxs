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
 *  fellowtraveler\opentransactions.org
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

#ifndef OPENTXS_API_BLOCKCHAIN_HPP
#define OPENTXS_API_BLOCKCHAIN_HPP

#include "opentxs/Version.hpp"

#include "opentxs/core/Identifier.hpp"
#include "opentxs/Proto.hpp"
#include "opentxs/Types.hpp"

#include <cstdint>
#include <map>
#include <memory>
#include <mutex>
#include <set>

namespace opentxs
{
namespace api
{
class Activity;
class Crypto;
class Wallet;

namespace storage
{
class Storage;
}  // namespace storage

namespace implementation
{
class Native;
}

class Blockchain
{
public:
    std::shared_ptr<proto::Bip44Account> Account(
        const Identifier& nymID,
        const Identifier& accountID) const;
    std::set<Identifier> AccountList(
        const Identifier& nymID,
        const proto::ContactItemType type) const;
    std::unique_ptr<proto::Bip44Address> AllocateAddress(
        const Identifier& nymID,
        const Identifier& accountID,
        const std::string& label = "",
        const BIP44Chain chain = EXTERNAL_CHAIN) const;
    bool AssignAddress(
        const Identifier& nymID,
        const Identifier& accountID,
        const std::uint32_t index,
        const Identifier& contactID,
        const BIP44Chain chain = EXTERNAL_CHAIN) const;
    std::unique_ptr<proto::Bip44Address> LoadAddress(
        const Identifier& nymID,
        const Identifier& accountID,
        const std::uint32_t index,
        const BIP44Chain chain) const;
    Identifier NewAccount(
        const Identifier& nymID,
        const BlockchainAccountType standard,
        const proto::ContactItemType type) const;
    bool StoreIncoming(
        const Identifier& nymID,
        const Identifier& accountID,
        const std::uint32_t index,
        const BIP44Chain chain,
        const proto::BlockchainTransaction& transaction) const;
    bool StoreOutgoing(
        const Identifier& senderNymID,
        const Identifier& accountID,
        const Identifier& recipientContactID,
        const proto::BlockchainTransaction& transaction) const;
    std::shared_ptr<proto::BlockchainTransaction> Transaction(
        const Identifier& id) const;

    ~Blockchain() = default;

private:
    typedef std::map<Identifier, std::mutex> IDLock;

    friend class implementation::Native;

    Activity& activity_;
    Crypto& crypto_;
    storage::Storage& storage_;
    Wallet& wallet_;
    mutable std::mutex lock_;
    mutable IDLock nym_lock_;
    mutable IDLock account_lock_;
    proto::Bip44Address& add_address(
        const std::uint32_t index,
        proto::Bip44Account& account,
        const BIP44Chain chain) const;
    std::uint8_t address_prefix(const proto::ContactItemType type) const;

    Bip44Type bip44_type(const proto::ContactItemType type) const;
    std::string calculate_address(
        const proto::Bip44Account& account,
        const BIP44Chain chain,
        const std::uint32_t index) const;
    proto::Bip44Address& find_address(
        const std::uint32_t index,
        const BIP44Chain chain,
        proto::Bip44Account& account) const;
    void init_path(
        const std::string& root,
        const proto::ContactItemType chain,
        const std::uint32_t account,
        const BlockchainAccountType standard,
        proto::HDPath& path) const;
    std::shared_ptr<proto::Bip44Account> load_account(
        const Lock& lock,
        const std::string& nymID,
        const std::string& accountID) const;
    bool move_transactions(
        const Identifier& nymID,
        const proto::Bip44Address& address,
        const std::string& fromContact,
        const std::string& toContact) const;

    Blockchain(
        Activity& activity,
        Crypto& crypto,
        storage::Storage& storage,
        Wallet& wallet);
    Blockchain() = delete;
    Blockchain(const Blockchain&) = delete;
    Blockchain(Blockchain&&) = delete;
    Blockchain operator=(const Blockchain&) = delete;
    Blockchain operator=(Blockchain&&) = delete;
};
}  // namespace api
}  // namespace opentxs

#endif  // OPENTXS_API_BLOCKCHAIN_HPP
