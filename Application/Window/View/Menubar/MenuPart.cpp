#include "MenuPart.hpp"

namespace CornStarch
{;

CMenuPart::CMenuPart(void)
{
}


CMenuPart::~CMenuPart(void)
{
}


/////////////////////////////////


// タイトルを取得する
wxString CMenuPart::getTitle(void)
{
    return m_title;
}


/////////////////////////////////

// タイトルをセットする
void CMenuPart::setTitle(const wxString& title)
{
    m_title = title.Clone();
}

}
