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

#ifndef OPENTXS_API_CRYPTO_CRYPTO_HPP
#define OPENTXS_API_CRYPTO_CRYPTO_HPP

#include "opentxs/Version.hpp"

#include "opentxs/api/Editor.hpp"
#include "opentxs/Proto.hpp"

#include <chrono>
#include <map>
#include <memory>
#include <mutex>

namespace opentxs
{
class Bip32;
class Bip39;
class CryptoAsymmetric;
class CryptoSymmetric;
class Identifier;
class OTASCIIArmor;
class OTCachedKey;
class SymmetricKey;

namespace api
{
namespace crypto
{
class Encode;
class Hash;
class Symmetric;
class Util;
}  // namespace crypto

class Crypto
{
public:
    EXPORT virtual const OTCachedKey& DefaultKey() const = 0;
    EXPORT virtual Editor<OTCachedKey> mutable_DefaultKey() const = 0;
    EXPORT virtual const OTCachedKey& CachedKey(const Identifier& id) const = 0;
    EXPORT virtual const OTCachedKey& CachedKey(
        const OTCachedKey& source) const = 0;
    EXPORT virtual const OTCachedKey& LoadDefaultKey(
        const OTASCIIArmor& serialized) const = 0;
    EXPORT virtual void SetTimeout(
        const std::chrono::seconds& timeout) const = 0;
    EXPORT virtual void SetSystemKeyring(const bool useKeyring) const = 0;

    // Encoding function interface
    EXPORT virtual crypto::Encode& Encode() const = 0;

    // Hash function interface
    EXPORT virtual crypto::Hash& Hash() const = 0;

    // Utility class for misc OpenSSL-provided functions
    EXPORT virtual crypto::Util& Util() const = 0;

    // Asymmetric encryption engines
    EXPORT virtual CryptoAsymmetric& ED25519() const = 0;
#if OT_CRYPTO_SUPPORTED_KEY_RSA
    EXPORT virtual CryptoAsymmetric& RSA() const = 0;
#endif
#if OT_CRYPTO_SUPPORTED_KEY_SECP256K1
    EXPORT virtual CryptoAsymmetric& SECP256K1() const = 0;
#endif

    // Symmetric encryption engines
    EXPORT virtual crypto::Symmetric& Symmetric() const = 0;

#if OT_CRYPTO_SUPPORTED_ALGO_AES
    EXPORT virtual CryptoSymmetric& AES() const = 0;
#endif
#if OT_CRYPTO_WITH_BIP32
    EXPORT virtual Bip32& BIP32() const = 0;
#endif
#if OT_CRYPTO_WITH_BIP39
    EXPORT virtual Bip39& BIP39() const = 0;
#endif

    EXPORT virtual std::unique_ptr<SymmetricKey> GetStorageKey(
        std::string& seed) const = 0;

    EXPORT virtual ~Crypto() = default;

protected:
    Crypto() = default;

private:
    Crypto(const Crypto&) = delete;
    Crypto(Crypto&&) = delete;
    Crypto& operator=(const Crypto&) = delete;
    Crypto& operator=(Crypto&&) = delete;
};
}  // namespace api
}  // namespace opentxs
#endif  // OPENTXS_API_CRYPTO_CRYPTO_HPP
