
#ifndef CLIENTCOMMANDINVOKER_HPP_
#define CLIENTCOMMANDINVOKER_HPP_
#include "ICommandInvoker.hpp"

namespace CornStarch
{

class CClientCommandInvoker: public ICommandInvoker
{
protected:
    const static wxString JUMP;
    const static wxString _DELETE;
    const static wxString NEW;
    const static wxString QUIT;
    const static wxString CONNECT;
    const static wxString DISCONNECT;
public:
    CClientCommandInvoker();
    virtual ~CClientCommandInvoker();

   std::vector<wxString> getCommandList();
};

} /* namespace CornStarch */
#endif /* CLIENTCOMMANDINVOKER_HPP_ */
