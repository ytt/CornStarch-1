#include "MenuEdit.hpp"

namespace CornStarch
{

CMenuEdit::CMenuEdit()
{

}

CMenuEdit::~CMenuEdit()
{
}

void CMenuEdit::init(void)
{
    setTitle(wxT("編集(&E)"));

    Append(wxID_UNDO, _("取り消す\tCtrl+Z"));
    Append(wxID_REDO, _("やり直す\tCtrl+Y"));
    AppendSeparator();
    Append(wxID_CUT, _("切り取り\tCtrl+X"));
    Append(wxID_COPY, _("コピー\tCtrl+C"));
    Append(wxID_PASTE, _("貼り付け\tCtrl+V"));

    AppendSeparator();
    Append(wxID_SELECTALL, _("全て選択\tCtrl+A"));

    AppendSeparator();
    Append(CMenuPart::MENU_EDIT_FIND, wxT("検索\tCtrl+F"));
	
#ifdef _WIN32
    Append(CMenuPart::MENU_EDIT_AUTOCOMPLETE, wxT("入力補助\tTAB"));
#endif
}

} /* namespace CornStarch */

