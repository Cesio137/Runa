/*
* Copyright (c) 2023-2024 Nathan Miguel
*/

#include "network/udp/udp_client.h"

namespace Runa {
    UDPClient::~UDPClient() {
        should_stop_context = true;
        udp.resolver.cancel();
        if (is_connected()) close();
        thread_pool->stop();
        rbuffer.raw_data.clear();
        rbuffer.raw_data.shrink_to_fit();
    }


}