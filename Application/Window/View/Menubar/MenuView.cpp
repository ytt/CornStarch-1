#include "MenuView.hpp"

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
    append(MENU_VIEW_ZOOM, wxT("拡大\tCtrl++"));
    append(MENU_VIEW_SHRINK, wxT("縮小\tCtrl+-"));
}
} /* namespace CornStarch */
