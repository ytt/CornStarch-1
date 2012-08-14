
#ifndef BASICCOMMANDINVOKER_HPP_
#define BASICCOMMANDINVOKER_HPP_
#include "ICommandInvoker.hpp"
#include "ChatServiceBase.hpp"
namespace CornStarch
{

class CBasicCommandInvoker : public ICommandInvoker
{
    const static wxString JOIN;
    const static wxString PART;
    const static wxString TOPIC;
    const static wxString NICK;

    CChatServiceBase* m_service;
public:
    CBasicCommandInvoker(CChatServiceBase* serivce);
    virtual ~CBasicCommandInvoker();

    bool invoke(const wxString& text);
   std::vector<wxString> getCommandList();

};

} /* namespace CornStarch */
#endif /* BASICCOMMANDINVOKER_HPP_ */
