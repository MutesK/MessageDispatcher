#include "Precompile.h"
#include "Protocol.h"
#include "Handler.h"
#include "MessageDispatch.h"
#include "PacketIdendityManager.h"

class InheritanceProtocolExample final : public Message
{
public:
    InheritanceProtocolExample()
        :Message(PacketIdendityManager::GetInstance().IdendityNumber<InheritanceProtocolExample>())
    {
    }
    virtual ~InheritanceProtocolExample()
    {
    }
};



class CustomHandler : public Handler
{
public:
    CustomHandler(const std::shared_ptr<MessageDispatcher>& Dispatcher)
        :Handler(Dispatcher)
    {
        RegisterPacket<InheritanceProtocolExample>([=](const std::shared_ptr<Message>& Protocol) { HandleInheritance(Protocol); });
    
       
    }

    void HandleInheritance(const std::shared_ptr<Message>& Protocol)
    {
        const auto Recv = std::dynamic_pointer_cast<InheritanceProtocolExample>(Protocol);

        std::cout << Protocol->_id << std::endl;
    }

};

int main()
{
    std::shared_ptr<InheritanceProtocolExample> Example = std::make_shared<InheritanceProtocolExample>();

    std::shared_ptr<MessageDispatcher> Dispatcher = std::make_shared<MessageDispatcher>();
    Dispatcher->RegisterHandler(std::make_shared<CustomHandler>(Dispatcher));
    
    Dispatcher->Send(Example);
}

