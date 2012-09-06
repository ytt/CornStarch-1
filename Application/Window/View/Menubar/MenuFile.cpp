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
    Append(wxID_EXIT, wxT("終了(&X)\tAlt-X"));
}

}
