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

#include "laser_connection.h"

namespace beam::wallet::lightning
{
LaserConnection::LaserConnection(proto::FlyClient& fc)
    : proto::FlyClient::NetworkStd(fc)
{

}

LaserConnection::~LaserConnection()
{

}

void LaserConnection::PostRequestInternal(proto::FlyClient::Request& r)
{
    if (proto::FlyClient::Request::Type::Transaction == r.get_Type())
        std::cout << "### Broadcasting transaction ###" << std::endl;

    if (proto::FlyClient::Request::Type::BbsMsg == r.get_Type())
        std::cout << "### Bbs mesage out ###" << std::endl;    

    proto::FlyClient::NetworkStd::PostRequestInternal(r);
}
}  // namespace beam::wallet::lightning