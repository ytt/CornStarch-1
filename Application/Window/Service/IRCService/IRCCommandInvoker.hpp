#include "../BasicCommandInvoker.hpp"
#include "../ChatServiceBase.hpp"

#ifndef IRCCOMMANDINVOKER_HPP_
#define IRCCOMMANDINVOKER_HPP_

namespace CornStarch
{
namespace IRC
{
class CIRCCommandInvoker: public CBasicCommandInvoker
{
    const static wxString INVITE;
    const static wxString KICK;
public:
    CIRCCommandInvoker(CChatServiceBase* service);
    virtual ~CIRCCommandInvoker();

    bool invoke(const wxString& text);
    std::vector<wxString> getCommandList();
};
}
} /* namespace CornStarch */
#endif /* IRCCOMMANDINVOKER_HPP_ */
