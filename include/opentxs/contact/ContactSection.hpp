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

#ifndef OPENTXS_CONTACT_CONTACT_SECTION_HPP
#define OPENTXS_CONTACT_CONTACT_SECTION_HPP

#include "opentxs/Version.hpp"

#include "opentxs/Proto.hpp"
#include "opentxs/Types.hpp"

#include <map>
#include <memory>

namespace opentxs
{

class ContactGroup;
class ContactItem;

class ContactSection
{
public:
    typedef std::map<proto::ContactItemType, std::shared_ptr<ContactGroup>>
        GroupMap;

    ContactSection(
        const std::string& nym,
        const std::uint32_t version,
        const std::uint32_t parentVersion,
        const proto::ContactSectionName section,
        const GroupMap& groups);
    ContactSection(
        const std::string& nym,
        const std::uint32_t version,
        const std::uint32_t parentVersion,
        const proto::ContactSectionName section,
        const std::shared_ptr<ContactItem>& item);
    ContactSection(
        const std::string& nym,
        const std::uint32_t parentVersion,
        const proto::ContactSection& serialized);
    ContactSection(const ContactSection&) = default;
    ContactSection(ContactSection&&) = default;

    ContactSection operator+(const ContactSection& rhs) const;

    ContactSection AddItem(const std::shared_ptr<ContactItem>& item) const;
    GroupMap::const_iterator begin() const;
    std::shared_ptr<ContactItem> Claim(const Identifier& item) const;
    ContactSection Delete(const Identifier& id);
    GroupMap::const_iterator end() const;
    std::shared_ptr<ContactGroup> Group(
        const proto::ContactItemType& type) const;
    bool HaveClaim(const Identifier& item) const;
    bool SerializeTo(proto::ContactData& data, const bool withIDs = false)
        const;
    std::size_t Size() const;

    ~ContactSection() = default;

private:
    const std::uint32_t version_{0};
    const std::string nym_{};
    const proto::ContactSectionName section_{proto::CONTACTSECTION_ERROR};
    const GroupMap groups_{};

    static std::uint32_t check_version(
        const std::uint32_t in,
        const std::uint32_t targetVersion);
    static GroupMap create_group(
        const std::string& nym,
        const proto::ContactSectionName section,
        const std::shared_ptr<ContactItem>& item);
    static GroupMap extract_groups(
        const std::string& nym,
        const std::uint32_t parentVersion,
        const proto::ContactSection& serialized);

    ContactSection add_scope(const std::shared_ptr<ContactItem>& item) const;

    ContactSection() = delete;
    ContactSection& operator=(const ContactSection&) = delete;
    ContactSection& operator=(ContactSection&&) = delete;
};
}  // namespace opentxs

#endif  // OPENTXS_CONTACT_CONTACT_SECTION_HPP
