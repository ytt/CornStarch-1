#ifndef ISCRIPTCOMMANDINVOKER_HPP_
#define ISCRIPTCOMMANDINVOKER_HPP_
#include <vector>
#include <wx/wxprec.h>
#include <wx/wx.h>

namespace CornStarch
{

class ICommandInvoker
{
public:
    ICommandInvoker(){};
    virtual ~ICommandInvoker(){};
    virtual bool invoke(const wxString& text)= 0;
    virtual std::vector<wxString> getCommandList() = 0;
};

} /* namespace CornStarch */
#endif /* ISCRIPTCOMMANDINVOKER_HPP_ */
