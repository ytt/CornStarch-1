#include "MenuView.hpp"
#include  <wx/sysopt.h>
namespace CornStarch
{

CMenuView::CMenuView()
{
}
CMenuView::~CMenuView()
{
}

void CMenuView::init(void)
{
    setTitle(wxT("表示(&V)"));
    Append(MENU_UPDATE, wxT("更新\tF5"));

    AppendSeparator();
    Append(MENU_VIEW_ZOOM, wxT("拡大\tCtrl++"));
    Append(MENU_VIEW_SHRINK, wxT("縮小\tCtrl+-"));
    AppendSeparator();
    Append(MENU_VIEW_SELECT_NEXT_TAB, wxT("次のタブを選択\tCTRL+Tab"));
    Append(MENU_VIEW_SELECT_PREVOUS_TAB, wxT("前のタブを選択\tCTRL+Shift+Tab"));
}
} /* namespace CornStarch */
