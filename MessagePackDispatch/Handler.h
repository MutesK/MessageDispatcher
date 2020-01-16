#pragma once

#include "MessageDispatch.h"
#include "Protocol.h"

class Handler abstract
{
	std::shared_ptr<MessageDispatcher> _Dispatcher;
	std::unordered_map<uint64_t, std::function<void(std::shared_ptr<Message>)>> _HandlerMap;

public:
	Handler(const std::shared_ptr<MessageDispatcher>& Dispatcher);
	virtual ~Handler() = default;

	template <class PacketClass>
	void RegisterPacket(const std::function<void(std::shared_ptr<Message>)>& function);

	void DispatchFunction(const uint64_t PacketID,
		const std::shared_ptr<Message>& message);

};

template<class PacketClass>
inline void Handler::RegisterPacket(const std::function<void(std::shared_ptr<Message>)>& function)
{
	const auto packetID = PacketIdendityManager::GetInstance().IdendityNumber<PacketClass>();

	_Dispatcher->RegisterPacket(packetID, this);
	_HandlerMap[packetID] = function;
}


template <class Functor>
class LambdaBinder
{
	Functor _function;

public:
	LambdaBinder(const Functor& function)
		:_function(function)
	{
	}
};