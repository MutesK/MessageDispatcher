#pragma once

#include "Precompile.h"
#include "Protocol.h"

class PacketIdendityManager
{
	std::unordered_map<uint64_t, std::function<Message * ()>>   _CustomCreateor;

	PacketIdendityManager() = default;
public:
	static PacketIdendityManager& GetInstance()
	{
		static PacketIdendityManager Manager;
		return Manager;
	}

	template <class InheritancePacketClass>
	uint64_t IdendityNumber()
	{
		static_assert(std::is_base_of<Message, InheritancePacketClass>::value,
			"All Packet Class is Base of Protocol");

		const uint64_t Hash = std::hash<std::string>{}(typeid(InheritancePacketClass).name());

		_CustomCreateor[Hash] = []() {
			return new InheritancePacketClass();
		};

		return Hash;
	}

	Message* GeneratePacketClass(uint64_t PacketId)
	{
		if (_CustomCreateor.find(PacketId) == _CustomCreateor.end())
		{
			return nullptr;
		}

		return _CustomCreateor[PacketId]();
	}
};
