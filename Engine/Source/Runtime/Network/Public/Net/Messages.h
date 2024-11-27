#pragma once

#include <Net/Common.h>

namespace Nanometro
{
    struct FUdpMessage
    {
        FUdpMessage() { raw_data.resize(1024); }
        std::vector<std::byte> raw_data;
        size_t size = 0;

        std::string toString() const
        {
            std::string str;
            str.resize(size);
            std::transform(raw_data.begin(), raw_data.end(), str.begin(),
                           [](std::byte byte) { return static_cast<char>(byte); });
            return str;
        }
    };

    struct FTcpMessage
    {
        std::vector<std::byte> raw_data;
        size_t size = 0;

        std::string to_string() const
        {
            std::string str;
            str.resize(size);
            std::transform(raw_data.begin(), raw_data.end(), str.begin(),
                           [](std::byte byte) { return static_cast<char>(byte); });
            return str;
        }
    };

    struct FWsMessage
    {
        FDataFrame data_frame;
        std::vector<std::byte> payload;
        size_t size = 0;

        std::string to_string() const
        {
            if (data_frame.opcode == EOpcode::TEXT_FRAME || data_frame.opcode == EOpcode::BINARY_FRAME)
            {
                std::string str;
                str.resize(payload.size());
                std::transform(payload.begin(), payload.end(), str.begin(),
                               [](std::byte byte) { return static_cast<char>(byte); });
                return str;
            }
            return "";
        }
    };
} // namespace Nanometro
