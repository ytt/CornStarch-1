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

//
//// ログの種類を取得
//CServiceLog::LOG_TYPE CServiceLog::getLogType(void) const
//{
//    return m_type;
//}

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
