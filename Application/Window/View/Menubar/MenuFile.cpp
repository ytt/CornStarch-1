#include "MenuFile.hpp"

namespace CornStarch
{
;

CMenuFile::CMenuFile(void)
{
}

CMenuFile::~CMenuFile(void)
{
}

///////////////////////////////////

void CMenuFile::init(void)
{
    setTitle(wxT("ファイル(&F)"));
    Append(MENU_FILE_SAVE, wxT("設定のエクスポート"));
    Append(MENU_FILE_LOAD, wxT("設定のインポート"));
    AppendSeparator();
    Append(wxID_EXIT, wxT("終了(&X)\tAlt-X"));
}

}
