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

#ifndef OPENTXS_API_API_HPP
#define OPENTXS_API_API_HPP

#include "opentxs/Version.hpp"

#include <mutex>
#include <string>

namespace opentxs
{
class MadeEasy;
class OT_API;
class OT_ME;
class OTAPI_Exec;
class OTME_too;

namespace api
{

class Api
{
public:
    EXPORT virtual std::recursive_mutex& Lock() const = 0;

    EXPORT virtual OTAPI_Exec& Exec(const std::string& wallet = "") = 0;
    EXPORT virtual MadeEasy& ME(const std::string& wallet = "") = 0;
    EXPORT virtual OT_API& OTAPI(const std::string& wallet = "") = 0;
    EXPORT virtual OT_ME& OTME(const std::string& wallet = "") = 0;
    EXPORT virtual OTME_too& OTME_TOO(const std::string& wallet = "") = 0;

    EXPORT virtual ~Api() = default;

protected:
    Api() = default;

private:
    Api(const Api&) = delete;
    Api(Api&&) = delete;
    Api& operator=(const Api&) = delete;
    Api& operator=(Api&&) = delete;
};
}  // namespace api
}  // namespace opentxs
#endif  // OPENTXS_API_API_HPP
