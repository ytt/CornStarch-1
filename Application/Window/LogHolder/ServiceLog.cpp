#include "ServiceLog.hpp"

namespace CornStarch
{;

CServiceLog::CServiceLog(void)
{
    m_time = time(NULL);
}


CServiceLog::~CServiceLog(void)
{
}


//////////////////////////////////////////////////////////////////////

// 本名に対応するニックネームが未知か
bool CServiceLog::isUnknownNick(const wxString& name) const
{
    return false;
}

// ニックネームを更新する
void CServiceLog::updateNick(const wxString& nick)
{
}

}
