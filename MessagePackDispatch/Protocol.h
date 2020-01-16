#pragma once

class Message
{
public:
	uint64_t _id;
	intptr_t		    senderId;
	std::list<intptr_t> destIds;
public:
	Message(uint64_t id)
		:_id(id)
	{
	}
	virtual ~Message() = default;

	void Append_DestId(const uint64_t& destId);
	void Set_SenderId(const intptr_t& senderId);

	MSGPACK_DEFINE(_id);
};
