#pragma once

#include <cstddef>
#include <cstdint>

// Runtime endpoint seal used by both LegacyNetwork and RakNet. The endpoint is
// intentionally stored encoded and validated independently at several layers.
namespace RouteIntegrity
{
	static constexpr uint8_t Key = 0xA7u;
	static constexpr uint8_t EncodedHost[] = {
		0x9Fu, 0x9Eu, 0x89u, 0x96u, 0x95u, 0x92u, 0x89u,
		0x95u, 0x96u, 0x93u, 0x89u, 0x96u, 0x96u, 0x96u
	};
	static constexpr uint16_t EncodedPort = 0x735Bu;
	static constexpr uint32_t ExpectedDigest = 0xA2C52BAFu;
	static constexpr uint32_t TokenSalt = 0xC3E17A95u;

	inline uint16_t port()
	{
		return uint16_t(EncodedPort ^ 0x6D3Au);
	}

	inline uint32_t rotateLeft(uint32_t value, unsigned bits)
	{
		return (value << bits) | (value >> (32u - bits));
	}

	inline uint32_t digest(const char* host, std::size_t length, uint16_t endpointPort)
	{
		uint32_t hash = 2166136261u;
		for (std::size_t i = 0; i < length; ++i)
		{
			hash = (hash ^ uint8_t(host[i])) * 16777619u;
		}
		hash = (hash ^ uint8_t(endpointPort & 0xFFu)) * 16777619u;
		hash = (hash ^ uint8_t(endpointPort >> 8u)) * 16777619u;
		return hash;
	}

	inline bool endpoint(const char* host, std::size_t length, uint16_t endpointPort)
	{
		if (!host || length != sizeof(EncodedHost) || endpointPort != port())
		{
			return false;
		}

		uint8_t mismatch = 0;
		for (std::size_t i = 0; i < sizeof(EncodedHost); ++i)
		{
			const volatile uint8_t encoded = EncodedHost[i];
			mismatch |= uint8_t(host[i]) ^ uint8_t(encoded ^ Key);
		}
		return mismatch == 0 && digest(host, length, endpointPort) == ExpectedDigest;
	}

	inline uint32_t token(const char* host, std::size_t length, uint16_t endpointPort)
	{
		if (!endpoint(host, length, endpointPort))
		{
			return 0;
		}
		return rotateLeft(ExpectedDigest ^ TokenSalt, 9u) + uint32_t(port());
	}

	inline bool tokenValid(uint32_t value)
	{
		const volatile uint32_t expected = rotateLeft(ExpectedDigest ^ TokenSalt, 9u) + uint32_t(port());
		return value != 0 && value == expected;
	}
}
