#include "ServiceConfiguration.hpp"
using namespace std;
namespace CornStarch
{

CServiceConfiguration::CServiceConfiguration() :
        m_fontSize(12), m_isAutoConnect(true)
{

}

CServiceConfiguration::~CServiceConfiguration()
{
    map<wxString, vector<IFilter*> >::iterator it = m_filters.begin();
    while (it != m_filters.end()){
        int size = (int) (*it).second.size();
        for (int i = 0; i < size; i++){
            delete (*it).second[i];
        }
        ++it;
    }
}

} /* namespace CornStarch */
