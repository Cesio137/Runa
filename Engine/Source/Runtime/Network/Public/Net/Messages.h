#pragma once

#include <Net/Common.h>

namespace Nanometro {
	struct tcpMessage {
		std::array<char, 8192> message;
		std::string toString() const {
			return message.data();
		}
		uint32_t size = 0;
	};
	
    struct udpMessage {
		std::array<char, 1024> message;
		std::string toString() const {
			return message.data();
		}
		uint32_t size = 0;
	};
} // namespace Nanometro