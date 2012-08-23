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
void CMessageLog::init(const CMessageData& message)
{
    if (m_message == NULL){
        m_message = new CMessageData();
    }
    *m_message = message;

}

// ログを取得する
CMessageData* CMessageLog::getMessage(void) const
{
    return m_message;
}


}
