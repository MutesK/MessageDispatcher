#pragma once

class Handler;
class Message;
class MessageDispatcher final
{
	std::vector<std::shared_ptr<Handler>> _HandlerMap;
	std::unordered_map<uint64_t, const Handler*> _PacketIDHandlerMap;

	friend class Handler;
public:
	MessageDispatcher() = default;
	~MessageDispatcher() = default;

	void RegisterHandler(const std::shared_ptr<Handler>& Handler);
	void RegisterPacket(const uint64_t& PacketID, const Handler* const pHandler);

	void Send(const std::shared_ptr<Message> Protocol);
	void RecviedMessage(const msgpack::sbuffer& serializedBuffer);
};

