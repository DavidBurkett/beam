// Copyright 2019 The Beam Team
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include "wallet/wallet.h"
#include "utility/logger.h"
#include "utility/std_extension.h"

#include <unordered_map>

namespace beam::wallet
{
    using namespace beam::proto;

    /**
     *  Implementation of public swap offers bulletin board using not crypted BBS broadcasting.
     */
    class SwapOffersBoard
        : public FlyClient::IBbsReceiver,
          public IWalletDbObserver
    {
    public:
        SwapOffersBoard(FlyClient::INetwork& network, IWalletMessageEndpoint& messageEndpoint);

        /**
         *  FlyClient::IBbsReceiver implementation
         *  Executed to catch BBS messages received on subscribed channels
         */
        virtual void OnMsg(proto::BbsMsg&& msg) override;
        /**
         *  IWalletDbObserver implementation
         *  Watch for swap transaction status changes to update linked offer on board
         */
        virtual void onTransactionChanged(ChangeAction action, const std::vector<TxDescription>& items) override;

        void selectSwapCoin(AtomicSwapCoin coinType);

        auto getOffersList() const -> std::vector<SwapOffer>;
        void publishOffer(const SwapOffer& offer) const;

        void Subscribe(ISwapOffersObserver* observer);
        void Unsubscribe(ISwapOffersObserver* observer);

    private:
		FlyClient::INetwork& m_network;                     /// source of incoming BBS messages
        std::vector<ISwapOffersObserver*> m_subscribers;    /// used to notify subscribers about offers changes
        IWalletMessageEndpoint& m_messageEndpoint;          /// destination of outgoing BBS messages

        static const std::map<AtomicSwapCoin, BbsChannel> m_channelsMap;
        static constexpr uint8_t m_protocolVersion = 1;
        Timestamp m_lastTimestamp = getTimestamp() - 12*60*60;
        boost::optional<BbsChannel> m_activeChannel;
        std::unordered_map<TxID, SwapOffer> m_offersCache;

        auto getChannel(const SwapOffer& offer) const -> boost::optional<BbsChannel>;
        void updateOffer(const TxID& offerTxID, SwapOfferStatus newStatus) const;

    };

} // namespace beam::wallet
