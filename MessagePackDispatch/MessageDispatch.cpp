#include "Precompile.h"
#include "MessageDispatch.h"
#include "Protocol.h"
#include "Handler.h"
#include "PacketIdendityManager.h"

void MessageDispatcher::RegisterHandler(const std::shared_ptr<Handler>& Handler)
{
	_HandlerMap.push_back(Handler);
}

void MessageDispatcher::RegisterPacket(const uint64_t& PacketID, const Handler* const pHandler)
{
	_PacketIDHandlerMap[PacketID] = pHandler;
}

void MessageDispatcher::Send(const std::shared_ptr<Message> Protocol)
{
	// Using MuteNet Send
	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, *Protocol);

	// SendNet Buffer
	RecviedMessage(sbuf);  // Test code
}

void MessageDispatcher::RecviedMessage(const msgpack::sbuffer& serializedBuffer)
{
	const msgpack::object_handle objectHandle = msgpack::unpack(serializedBuffer.data(), 
		serializedBuffer.size());

	const auto PacketObject = objectHandle.get();

	// Generate Packet Class
	Message tempMessage(0);
	PacketObject.convert(tempMessage);

	auto dispatchMessage = std::shared_ptr<Message>(PacketIdendityManager::GetInstance().GeneratePacketClass(tempMessage._id));
	auto handler = _PacketIDHandlerMap[tempMessage._id];

	const_cast<Handler*>(handler)->DispatchFunction(tempMessage._id, dispatchMessage);
}
