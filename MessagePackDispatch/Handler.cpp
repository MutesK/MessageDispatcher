#include "Precompile.h"
#include "MessageDispatch.h"
#include "Handler.h"

Handler::Handler(const std::shared_ptr<MessageDispatcher>& Dispatcher)
	:_Dispatcher(Dispatcher)
{
}

void Handler::DispatchFunction(const uint64_t PacketID, const std::shared_ptr<Message>& message)
{
	_HandlerMap[PacketID](message);
}
