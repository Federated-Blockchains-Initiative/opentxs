/************************************************************
*
*  OTSettings.hpp
*
*/

/************************************************************
 -----BEGIN PGP SIGNED MESSAGE-----
 Hash: SHA1

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
 *  Copyright (C) 2010-2013 by "Fellow Traveler" (A pseudonym)
 *
 *  EMAIL:
 *  FellowTraveler@rayservers.net
 *
 *  BITCOIN:  1NtTPVVjDsUfDWybS4BwvHpG2pdS9RnYyQ
 *
 *  KEY FINGERPRINT (PGP Key in license file):
 *  9DD5 90EB 9292 4B48 0484  7910 0308 00ED F951 BB8E
 *
 *  OFFICIAL PROJECT WIKI(s):
 *  https://github.com/FellowTraveler/Moneychanger
 *  https://github.com/FellowTraveler/Open-Transactions/wiki
 *
 *  WEBSITE:
 *  http://www.OpenTransactions.org/
 *
 *  Components and licensing:
 *   -- Moneychanger..A Java client GUI.....LICENSE:.....GPLv3
 *   -- otlib.........A class library.......LICENSE:...LAGPLv3
 *   -- otapi.........A client API..........LICENSE:...LAGPLv3
 *   -- opentxs/ot....Command-line client...LICENSE:...LAGPLv3
 *   -- otserver......Server Application....LICENSE:....AGPLv3
 *  Github.com/FellowTraveler/Open-Transactions/wiki/Components
 *
 *  All of the above OT components were designed and written by
 *  Fellow Traveler, with the exception of Moneychanger, which
 *  was contracted out to Vicky C (bitcointrader4@gmail.com).
 *  The open-source community has since actively contributed.
 *
 *  -----------------------------------------------------
 *
 *   LICENSE:
 *   This program is free software: you can redistribute it
 *   and/or modify it under the terms of the GNU Affero
 *   General Public License as published by the Free Software
 *   Foundation, either version 3 of the License, or (at your
 *   option) any later version.
 *
 *   ADDITIONAL PERMISSION under the GNU Affero GPL version 3
 *   section 7: (This paragraph applies only to the LAGPLv3
 *   components listed above.) If you modify this Program, or
 *   any covered work, by linking or combining it with other
 *   code, such other code is not for that reason alone subject
 *   to any of the requirements of the GNU Affero GPL version 3.
 *   (==> This means if you are only using the OT API, then you
 *   don't have to open-source your code--only your changes to
 *   Open-Transactions itself must be open source. Similar to
 *   LGPLv3, except it applies to software-as-a-service, not
 *   just to distributing binaries.)
 *
 *   Extra WAIVER for OpenSSL, Lucre, and all other libraries
 *   used by Open Transactions: This program is released under
 *   the AGPL with the additional exemption that compiling,
 *   linking, and/or using OpenSSL is allowed. The same is true
 *   for any other open source libraries included in this
 *   project: complete waiver from the AGPL is hereby granted to
 *   compile, link, and/or use them with Open-Transactions,
 *   according to their own terms, as long as the rest of the
 *   Open-Transactions terms remain respected, with regard to
 *   the Open-Transactions code itself.
 *
 *   Lucre License:
 *   This code is also "dual-license", meaning that Ben Lau-
 *   rie's license must also be included and respected, since
 *   the code for Lucre is also included with Open Transactions.
 *   See Open-Transactions/src/otlib/lucre/LUCRE_LICENSE.txt
 *   The Laurie requirements are light, but if there is any
 *   problem with his license, simply remove the Lucre code.
 *   Although there are no other blind token algorithms in Open
 *   Transactions (yet. credlib is coming), the other functions
 *   will continue to operate.
 *   See Lucre on Github:  https://github.com/benlaurie/lucre
 *   -----------------------------------------------------
 *   You should have received a copy of the GNU Affero General
 *   Public License along with this program.  If not, see:
 *   http://www.gnu.org/licenses/
 *
 *   If you would like to use this software outside of the free
 *   software license, please contact FellowTraveler.
 *   (Unfortunately many will run anonymously and untraceably,
 *   so who could really stop them?)
 *
 *   DISCLAIMER:
 *   This program is distributed in the hope that it will be
 *   useful, but WITHOUT ANY WARRANTY; without even the implied
 *   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *   PURPOSE.  See the GNU Affero General Public License for
 *   more details.

 -----BEGIN PGP SIGNATURE-----
 Version: GnuPG v1.4.9 (Darwin)

 iQIcBAEBAgAGBQJRSsfJAAoJEAMIAO35UbuOQT8P/RJbka8etf7wbxdHQNAY+2cC
 vDf8J3X8VI+pwMqv6wgTVy17venMZJa4I4ikXD/MRyWV1XbTG0mBXk/7AZk7Rexk
 KTvL/U1kWiez6+8XXLye+k2JNM6v7eej8xMrqEcO0ZArh/DsLoIn1y8p8qjBI7+m
 aE7lhstDiD0z8mwRRLKFLN2IH5rAFaZZUvj5ERJaoYUKdn4c+RcQVei2YOl4T0FU
 LWND3YLoH8naqJXkaOKEN4UfJINCwxhe5Ke9wyfLWLUO7NamRkWD2T7CJ0xocnD1
 sjAzlVGNgaFDRflfIF4QhBx1Ddl6wwhJfw+d08bjqblSq8aXDkmFA7HeunSFKkdn
 oIEOEgyj+veuOMRJC5pnBJ9vV+7qRdDKQWaCKotynt4sWJDGQ9kWGWm74SsNaduN
 TPMyr9kNmGsfR69Q2Zq/FLcLX/j8ESxU+HYUB4vaARw2xEOu2xwDDv6jt0j3Vqsg
 x7rWv4S/Eh18FDNDkVRChiNoOIilLYLL6c38uMf1pnItBuxP3uhgY6COm59kVaRh
 nyGTYCDYD2TK+fI9o89F1297uDCwEJ62U0Q7iTDp5QuXCoxkPfv8/kX6lS6T3y9G
 M9mqIoLbIQ1EDntFv7/t6fUTS2+46uCrdZWbQ5RjYXdrzjij02nDmJAm2BngnZvd
 kamH0Y/n11lCvo1oQxM+
 =uSzz
 -----END PGP SIGNATURE-----
 **************************************************************/

#ifndef OPENTXS_CORE_OTSETTINGS_HPP
#define OPENTXS_CORE_OTSETTINGS_HPP

#include "OTString.hpp"

namespace opentxs
{

class OTSettings
{
private:
    OTSettings(const OTSettings&);
    OTSettings& operator=(const OTSettings&);

    class OTSettingsPvt;
    OTSettingsPvt* pvt;

    bool b_Loaded;

    String m_strConfigurationFileExactPath;

    // Core (Load and Save)
    EXPORT bool Load(const String& strConfigurationFileExactPath);
    EXPORT bool Save(const String& strConfigurationFileExactPath);

    // Log (log to Output in a well-formated way).
    EXPORT bool LogChange_str(const String& strSection, const String& strKey,
                              const String& strValue);

public:
    EXPORT OTSettings();

    EXPORT OTSettings(const String& strConfigFilePath);

    EXPORT ~OTSettings();

    EXPORT void SetConfigFilePath(const String& strConfigFilePath);
    EXPORT bool HasConfigFilePath();

    // Core (Public Load and Save)
    EXPORT bool Load();
    EXPORT bool Save();

    EXPORT const bool& IsLoaded() const;

    // Configuration Helpers
    //

    // Core (Reset Config, and Check if Config is empty)
    EXPORT bool Reset();
    EXPORT bool IsEmpty() const;

    // Check Only (get value of key from configuration, if the key exists, then
    // out_bKeyExist will be true.)
    EXPORT bool Check_str(const String& strSection, const String& strKey,
                          String& out_strResult, bool& out_bKeyExist) const;
    EXPORT bool Check_long(const String& strSection, const String& strKey,
                           int64_t& out_lResult, bool& out_bKeyExist) const;
    EXPORT bool Check_bool(const String& strSection, const String& strKey,
                           bool& out_bResult, bool& out_bKeyExist) const;

    // Set Only (set new or update value, out_bNewOrUpdate will be true if the
    // value changes.)
    EXPORT bool Set_str(const String& strSection, const String& strKey,
                        const String& strValue, bool& out_bNewOrUpdate,
                        const String& strComment = "");
    EXPORT bool Set_long(const String& strSection, const String& strKey,
                         const int64_t& lValue, bool& out_bNewOrUpdate,
                         const String& strComment = "");
    EXPORT bool Set_bool(const String& strSection, const String& strKey,
                         const bool& bValue, bool& out_bNewOrUpdate,
                         const String& strComment = "");

    // Check for a Section, if the section dosn't exist, it will be made and
    // out_bIsNewSection will be true.)
    EXPORT bool CheckSetSection(const String& strSection,
                                const String& strComment,
                                bool& out_bIsNewSection);

    // Check for Key, and returns if the key exists, otherwise will set the
    // default key. If the default key is set, then out_bIsNew will be true.)
    EXPORT bool CheckSet_str(const String& strSection, const String& strKey,
                             const String& strDefault, String& out_strResult,
                             bool& out_bIsNew, const String& strComment = "");
    EXPORT bool CheckSet_long(const String& strSection, const String& strKey,
                              const int64_t& lDefault, int64_t& out_lResult,
                              bool& out_bIsNew, const String& strComment = "");
    EXPORT bool CheckSet_bool(const String& strSection, const String& strKey,
                              const bool& bDefault, bool& out_bResult,
                              bool& out_bIsNew, const String& strComment = "");

    // Set Option helper function for setting bool's
    EXPORT bool SetOption_bool(const String& strSection, const String& strKey,
                               bool& bVariableName);
};

} // namespace opentxs

#endif // OPENTXS_CORE_OTSETTINGS_HPP
