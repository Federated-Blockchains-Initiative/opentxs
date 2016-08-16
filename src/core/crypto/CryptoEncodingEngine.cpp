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

#include "opentxs/core/crypto/CryptoEncodingEngine.hpp"

#include "opentxs/core/crypto/BitcoinCrypto.hpp"
#include "opentxs/core/crypto/OTPassword.hpp"
#include "opentxs/core/OTData.hpp"

#include "base64/base64.h"

#include <iostream>
#include <regex>

namespace opentxs
{

std::string CryptoEncodingEngine::Base58CheckEncode(
    const std::uint8_t* inputStart,
    const size_t& size) const
{
    return ::EncodeBase58Check(inputStart, inputStart + size);
}

std::string CryptoEncodingEngine::Base64Encode(
    const std::uint8_t* inputStart,
    const size_t& size) const
{
    std::string output;
    output.resize(::Base64encode_len(size)+1);
    ::Base64encode(
        const_cast<char*>(output.c_str()),
        reinterpret_cast<const char*>(inputStart),
        size);

    return BreakLines(output);
}

bool CryptoEncodingEngine::Base58CheckDecode(
    const std::string&& input,
    Data& output) const
{
    return ::DecodeBase58Check(input.c_str(), output);
}

bool CryptoEncodingEngine::Base64Decode(
    const std::string&& input,
    Data& output) const
{
    output.resize(::Base64decode_len(input.c_str()), 0x0);

    return (0 < ::Base64decode(
        reinterpret_cast<char*>(output.data()),
        input.c_str()));
}

std::string CryptoEncodingEngine::BreakLines(const std::string& input) const
{
    std::string output;
    size_t width = 0;

    for (auto& character : input) {
        output.push_back(character);

        if (++width >= LineWidth) {
            output.push_back('\n');
            width = 0;
        }
    }

    if (0 != width) {
        output.push_back('\n');
    }

    return output;
}

std::string CryptoEncodingEngine::DataEncode(const std::string& input) const
{
    return Base64Encode(
        reinterpret_cast<const uint8_t*>(input.c_str()),
        input.size());
}

std::string CryptoEncodingEngine::DataEncode(const OTData& input) const
{
    return Base64Encode(
        static_cast<const uint8_t*>(input.GetPointer()),
        input.GetSize());
}

std::string CryptoEncodingEngine::DataDecode(const std::string& input) const
{
    Data decoded;

    if (Base64Decode(SanatizeBase64(input), decoded)) {

        return std::string(
            reinterpret_cast<const char*>(decoded.data()), decoded.size());
    }

    return "";
}

std::string CryptoEncodingEngine::IdentifierEncode(
    const OTData& input) const
{
    return Base58CheckEncode(
        static_cast<const uint8_t*>(input.GetPointer()),
        input.GetSize());
}

std::string CryptoEncodingEngine::IdentifierEncode(const OTPassword& input) const
{
    if (input.isMemory()) {
        return Base58CheckEncode(
            static_cast<const uint8_t*>(input.getMemory()),
            input.getMemorySize());
    } else {
        return Base58CheckEncode(
            reinterpret_cast<const uint8_t*>(input.getPassword()),
            input.getPasswordSize());
    }
}

std::string CryptoEncodingEngine::IdentifierDecode(const std::string& input) const
{
    Data decoded;

    if (Base58CheckDecode(SanatizeBase58(input), decoded)) {

        return std::string(
            reinterpret_cast<const char*>(decoded.data()), decoded.size());
    }

    return "";
}

bool CryptoEncodingEngine::IsBase62(const std::string& str) const
{
    return str.find_first_not_of(
               "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHI"
               "JKLMNOPQRSTUVWXYZ") == std::string::npos;
}

String CryptoEncodingEngine::Nonce(const uint32_t size) const
{
    OTData unusedOutput;
    return Nonce(size, unusedOutput);
}

String CryptoEncodingEngine::Nonce(const uint32_t size, OTData& rawOutput) const
{
    rawOutput.zeroMemory();
    rawOutput.SetSize(size);

    OTPassword source;
    source.randomizeMemory(size);

    String nonce(IdentifierEncode(source));

    rawOutput.Assign(source.getMemory(), source.getMemorySize());
    return nonce;
}

std::string CryptoEncodingEngine::RandomFilename() const { return Nonce(16).Get(); }

std::string CryptoEncodingEngine::SanatizeBase58(const std::string& input) const
{
    return std::regex_replace(input, std::regex("[^1-9A-HJ-NP-Za-km-z]"), "");
}

std::string CryptoEncodingEngine::SanatizeBase64(const std::string& input) const
{
    return std::regex_replace(input, std::regex("[^0-9A-Za-z+/=]"), "");
}
}  // namespace opentxs