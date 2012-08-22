#include "IRCCommandInvoker.hpp"
#include "IRCService.hpp"

namespace CornStarch
{
namespace IRC
{
const wxString CIRCCommandInvoker::INVITE = "/invite ";
const wxString CIRCCommandInvoker::KICK = "/kick ";
CIRCCommandInvoker::CIRCCommandInvoker(CChatServiceBase* service): CBasicCommandInvoker(service)
{

}

CIRCCommandInvoker::~CIRCCommandInvoker()
{
}

bool CIRCCommandInvoker::invoke(const wxString& text)
{
//    CIRCService* service = dynamic_cast<CIRCService*>(m_service);
//    if (text.StartsWith(CIRCCommandInvoker::INVITE)){
//        wxString channle = text;
//        wxString argument = channle.Remove(0,
//                CIRCCommandInvoker::INVITE.size());
//        service->(argument);
//        return true;
//    } else if (text.StartsWith(CIRCCommandInvoker::KICK)){
//        wxString channle = text;
//        wxString argument = channle.Remove(0, CIRCCommandInvoker::KICK.size());
//        service->(argument);
//        return true;
//    } else{
//    }
    return CBasicCommandInvoker::invoke(text);
}
vector<wxString> CIRCCommandInvoker::getCommandList()
{
    vector<wxString> vector = CBasicCommandInvoker::getCommandList();
    vector.push_back(CIRCCommandInvoker::INVITE);
    vector.push_back(CIRCCommandInvoker::KICK);
    return vector;
}
}
} /* namespace CornStarch */
