#include "Precompile.h"
#include "Protocol.h"

void Message::Append_DestId(const uint64_t& destId)
{
	destIds.push_back(destId);
}
