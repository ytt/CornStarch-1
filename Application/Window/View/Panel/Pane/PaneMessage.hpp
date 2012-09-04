#ifndef PANEMESSAGE_HPP_
#define PANEMESSAGE_HPP_
#include "../../../../DataStruct/MemberData.hpp"
#include <wx/wxprec.h>
#include <wx/richtext/richtextctrl.h>
#include <wx/wx.h>
#include <vector>
#include <wx/notebook.h>
#include <map>
#include <wx/panel.h>
#include "../../../Service/NickTable.hpp"
#include "LogTextCtrl.hpp"
#include "PaneMsg.hpp"

namespace CornStarch
{
class CPaneMessage : public wxNotebook
{
    CPaneMsg* m_allLogCtrl;
    CPaneMsg* m_systemLogCtrl;
    CPaneMsg* m_chatLogCtrl;

    wxPanel* m_panel1;
    wxPanel* m_panel2;
    wxPanel* m_panel3;

    bool isFilterPassed(const CMessage* message,const vector<IFilter*>& filters );
public:
    void init(wxWindow* parent);
    CPaneMessage();
    virtual ~CPaneMessage();

    void displayMessages(const std::vector<CMessage*>& messages,
        const CNickTable& nickTable,const CServiceConfiguration* configuration);
    void clear();
    void pushLog(const CMessage* log);
    void clearUnreadBackgroundColor();
};

} /* namespace CornStarch */
#endif /* PANEMESSAGE_HPP_ */
