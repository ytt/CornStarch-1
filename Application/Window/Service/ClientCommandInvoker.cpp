#include "ClientCommandInvoker.hpp"
using namespace std;

namespace CornStarch
{
const wxString CClientCommandInvoker::JUMP = "/jump";
const wxString CClientCommandInvoker::_DELETE = "/delete";
const wxString CClientCommandInvoker::NEW = "/new";
const wxString CClientCommandInvoker::DISCONNECT = "/disconnect";
const wxString CClientCommandInvoker::CONNECT = "/connect";
const wxString CClientCommandInvoker::QUIT = "/quit";

CClientCommandInvoker::CClientCommandInvoker()
{

}

CClientCommandInvoker::~CClientCommandInvoker()
{
}

vector<wxString> CClientCommandInvoker::getCommandList()
{
    vector<wxString> vector;
    vector.push_back(CClientCommandInvoker::JUMP);
    vector.push_back(CClientCommandInvoker::CONNECT);
    vector.push_back(CClientCommandInvoker::DISCONNECT);
    vector.push_back(CClientCommandInvoker::NEW);
    vector.push_back(CClientCommandInvoker::_DELETE);
    vector.push_back(CClientCommandInvoker::QUIT);
    return vector;
}
} /* namespace CornStarch */
