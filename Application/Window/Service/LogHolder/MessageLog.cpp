#include "MessageLog.hpp"

using namespace std;

namespace CornStarch
{;

CMessageLog::CMessageLog(void) : m_message(NULL)
{
}


CMessageLog::~CMessageLog(void)
{
    delete m_message;
}


//////////////////////////////////////////////////////////////////////


// 初期化を行う
void CMessageLog::init(CMessageData* message)
{
    m_message = message;

}

// ログを取得する
CMessageData* CMessageLog::getMessage(void) const
{
    return m_message;
}


}
