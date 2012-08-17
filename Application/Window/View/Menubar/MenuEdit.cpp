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
    append(CMenuPart::MENU_EDIT_SELECT_ALL,
        wxT("全てを選択\tCtrl+A"));
    AppendSeparator();
    append(CMenuPart::MENU_EDIT_AUTOCOMPLETE,
        wxT("入力補完\tTab"));
    append(CMenuPart::MENU_EDIT_FIND,
        wxT("検索\tCtrl+F"));
}

} /* namespace CornStarch */
