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

#include "common.h"

namespace
{
    constexpr uint8_t kQtumMainnetP2KH = 0x3a;
    constexpr uint8_t kQtumTestnetP2KH = 0x78;
}

namespace beam::qtum
{
    uint8_t getAddressVersion()
    {
#if defined(BEAM_MAINNET) || defined(SWAP_MAINNET)
        return kQtumMainnetP2KH;
#else
        return kQtumTestnetP2KH;
#endif
    }
} // namespace beam::qtum
