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

#ifndef OPENTXS_CLIENT_OT_ME_HPP
#define OPENTXS_CLIENT_OT_ME_HPP

#include "opentxs/Version.hpp"

#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

namespace opentxs
{
class MadeEasy;
class OT_API;
class OTAPI_Exec;
class String;

namespace api
{
class Wallet;

namespace implementation
{
class Api;
}  // namespace implementation
}

class OT_ME
{
public:
    EXPORT std::int32_t VerifyMessageSuccess(
        const std::string& str_Message) const;

    EXPORT std::int32_t VerifyMsgBalanceAgrmntSuccess(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        const std::string& str_Message) const;

    EXPORT std::int32_t VerifyMsgTrnxSuccess(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        const std::string& str_Message) const;

    EXPORT std::int32_t InterpretTransactionMsgReply(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        const std::string& str_Attempt,
        const std::string& str_Response) const;

    EXPORT bool make_sure_enough_trans_nums(
        std::int32_t nNumberNeeded,
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string ping_notary(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string register_contract_nym(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& CONTRACT) const;

    EXPORT std::string register_contract_server(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& CONTRACT) const;

    EXPORT std::string register_contract_unit(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& CONTRACT) const;

    EXPORT std::string register_nym(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string unregister_nym(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string check_nym(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID) const;

    EXPORT std::string issue_asset_type(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& THE_CONTRACT) const;

    EXPORT std::string issue_basket_currency(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& THE_BASKET) const;

    EXPORT std::string exchange_basket_currency(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID,
        const std::string& THE_BASKET,
        const std::string& ACCOUNT_ID,
        bool IN_OR_OUT) const;

    EXPORT std::string retrieve_contract(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& CONTRACT_ID) const;

    EXPORT std::string load_or_retrieve_contract(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& CONTRACT_ID) const;

    EXPORT std::string create_asset_acct(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID) const;

    EXPORT std::string unregister_account(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID) const;

    EXPORT std::string stat_asset_account(const std::string& ACCOUNT_ID) const;

    EXPORT bool retrieve_account(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        bool bForceDownload = false) const;

    EXPORT bool retrieve_nym(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        bool bForceDownload = true) const;

    EXPORT std::string send_transfer(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_FROM,
        const std::string& ACCT_TO,
        std::int64_t AMOUNT,
        const std::string& NOTE) const;

    EXPORT std::string process_inbox(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        const std::string& RESPONSE_LEDGER) const;

    EXPORT bool accept_inbox_items(
        const std::string& ACCOUNT_ID,
        std::int32_t nItemType,
        const std::string& INDICES) const;

    EXPORT bool discard_incoming_payments(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& INDICES) const;

    EXPORT bool cancel_outgoing_payments(
        const std::string& NYM_ID,
        const std::string& ACCOUNT_ID,
        const std::string& INDICES) const;

    EXPORT bool accept_from_paymentbox(
        const std::string& ACCOUNT_ID,
        const std::string& INDICES,
        const std::string& PAYMENT_TYPE) const;

    EXPORT bool accept_from_paymentbox_overload(
        const std::string& ACCOUNT_ID,
        const std::string& INDICES,
        const std::string& PAYMENT_TYPE,
        std::string* pOptionalOutput = nullptr) const;

    EXPORT std::string load_public_encryption_key(
        const std::string& NYM_ID) const;

    EXPORT std::string load_public_signing_key(const std::string& NYM_ID) const;

    EXPORT std::string load_or_retrieve_encrypt_key(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID) const;

    EXPORT std::string send_user_msg_pubkey(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& RECIPIENT_PUBKEY,
        const std::string& THE_MESSAGE) const;

    EXPORT std::string send_user_pmnt_pubkey(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& RECIPIENT_PUBKEY,
        const std::string& THE_INSTRUMENT) const;

#if OT_CASH
    EXPORT std::string send_user_cash_pubkey(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& RECIPIENT_PUBKEY,
        const std::string& THE_INSTRUMENT,
        const std::string& INSTRUMENT_FOR_SENDER) const;
#endif  // OT_CASH

    EXPORT std::string send_user_msg(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& THE_MESSAGE) const;

    EXPORT std::string send_user_payment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& THE_PAYMENT) const;

#if OT_CASH
    EXPORT std::string send_user_cash(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& RECIPIENT_NYM_ID,
        const std::string& THE_PAYMENT,
        const std::string& SENDERS_COPY) const;
#endif  // OT_CASH

    EXPORT bool withdraw_and_send_cash(
        const std::string& ACCT_ID,
        const std::string& RECIPIENT_NYM_ID,
        std::int64_t AMOUNT) const;

    EXPORT std::string get_payment_instrument(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        std::int32_t nIndex,
        const std::string& PRELOADED_INBOX = "") const;

    EXPORT std::string get_box_receipt(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        std::int32_t nBoxType,
        std::int64_t TRANS_NUM) const;

#if OT_CASH
    EXPORT std::string retrieve_mint(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID) const;

    EXPORT std::string load_or_retrieve_mint(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID) const;
#endif  // OT_CASH

    EXPORT std::string create_market_offer(
        const std::string& ASSET_ACCT_ID,
        const std::string& CURRENCY_ACCT_ID,
        std::int64_t scale,
        std::int64_t minIncrement,
        std::int64_t quantity,
        std::int64_t price,
        bool bSelling,
        std::int64_t lLifespanInSeconds,
        const std::string& STOP_SIGN,
        std::int64_t ACTIVATION_PRICE) const;

    EXPORT std::string kill_market_offer(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ASSET_ACCT_ID,
        std::int64_t TRANS_NUM) const;

    EXPORT std::string kill_payment_plan(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        std::int64_t TRANS_NUM) const;

    EXPORT std::string cancel_payment_plan(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& THE_PAYMENT_PLAN) const;

    EXPORT std::string activate_smart_contract(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        const std::string& AGENT_NAME,
        const std::string& THE_SMART_CONTRACT) const;

    EXPORT std::string trigger_clause(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        std::int64_t TRANS_NUM,
        const std::string& CLAUSE_NAME,
        const std::string& STR_PARAM) const;

    EXPORT std::string withdraw_cash(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        std::int64_t AMOUNT) const;

    EXPORT bool easy_withdraw_cash(
        const std::string& ACCT_ID,
        std::int64_t AMOUNT) const;

    EXPORT std::string export_cash(
        const std::string& NOTARY_ID,
        const std::string& FROM_NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID,
        const std::string& TO_NYM_ID,
        const std::string& STR_INDICES,
        bool bPasswordProtected,
        std::string& STR_RETAINED_COPY) const;

    EXPORT std::string withdraw_voucher(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        const std::string& RECIP_NYM_ID,
        const std::string& STR_MEMO,
        std::int64_t AMOUNT) const;

    EXPORT std::string pay_dividend(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& SOURCE_ACCT_ID,
        const std::string& SHARES_INSTRUMENT_DEFINITION_ID,
        const std::string& STR_MEMO,
        std::int64_t AMOUNT_PER_SHARE) const;

    EXPORT std::string deposit_cheque(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        const std::string& STR_CHEQUE) const;

    EXPORT bool deposit_cash(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        const std::string& STR_PURSE) const;

    EXPORT bool deposit_local_purse(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& ACCT_ID,
        const std::string& STR_INDICES) const;

    EXPORT std::string get_market_list(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string get_market_offers(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& MARKET_ID,
        std::int64_t MAX_DEPTH) const;

    EXPORT std::string get_nym_market_offers(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID) const;

    EXPORT std::string get_market_recent_trades(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& MARKET_ID) const;

    EXPORT std::string adjust_usage_credits(
        const std::string& NOTARY_ID,
        const std::string& USER_NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& ADJUSTMENT) const;

    EXPORT std::string notify_bailment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID,
        const std::string& TXID) const;

    EXPORT std::string initiate_bailment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID) const;

    EXPORT std::string initiate_outbailment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& INSTRUMENT_DEFINITION_ID,
        const std::int64_t& AMOUNT,
        const std::string& THE_MESSAGE) const;

    EXPORT std::string request_connection(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::int64_t TYPE) const;

    EXPORT std::string store_secret(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::int64_t TYPE,
        const std::string& PRIMARY,
        const std::string& SECONDARY) const;

    EXPORT std::string acknowledge_bailment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& REQUEST_ID,
        const std::string& THE_MESSAGE) const;

    EXPORT std::string acknowledge_outbailment(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& REQUEST_ID,
        const std::string& THE_MESSAGE) const;

    EXPORT std::string acknowledge_notice(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& REQUEST_ID,
        const bool ACK) const;

    EXPORT std::string acknowledge_connection(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& TARGET_NYM_ID,
        const std::string& REQUEST_ID,
        const bool ACK,
        const std::string& URL,
        const std::string& LOGIN,
        const std::string& PASSWORD,
        const std::string& KEY) const;

    EXPORT std::string request_admin(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& PASSWORD) const;

    /** Ask a server to add a claim to the server nym's credentials.
     *
     *  Only successful if the requesting nym is the admin nym on the server. */
    EXPORT std::string server_add_claim(
        const std::string& NOTARY_ID,
        const std::string& NYM_ID,
        const std::string& SECTION,
        const std::string& TYPE,
        const std::string& VALUE,
        const bool PRIMARY) const;

    ~OT_ME() = default;

private:
    friend class api::implementation::Api;

    std::recursive_mutex& lock_;
    OTAPI_Exec& exec_;
    OT_API& otapi_;
    const MadeEasy& made_easy_;
    api::Wallet& wallet_;

    OT_ME(
        std::recursive_mutex& lock,
        OTAPI_Exec& exec,
        OT_API& otapi,
        MadeEasy& madeEasy,
        api::Wallet& wallet);
    OT_ME() = delete;
    OT_ME(const OT_ME&) = delete;
    OT_ME(const OT_ME&&) = delete;
    OT_ME& operator=(const OT_ME&) = delete;
    OT_ME& operator=(const OT_ME&&) = delete;
};
}  // namespace opentxs

#endif  // OPENTXS_CLIENT_OT_ME_HPP
