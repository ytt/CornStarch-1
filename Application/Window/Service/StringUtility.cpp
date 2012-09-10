#include <iostream>
#include "StringUtility.hpp"
using namespace std;

namespace CornStarch
{

vector<wxString> CStringUtility::split(wxString str, wxString delim)
{
    std::vector<wxString> items;
    std::size_t delimIndex = str.find_first_of(delim);
    if (wxString::npos == delimIndex){
        items.push_back(str.substr(0, delimIndex));
    }
    while (wxString::npos != (delimIndex = str.find_first_of(delim))){
        if (wxString::npos == str.find_first_not_of(delim)){
            break;
        }
        items.push_back(str.substr(0, delimIndex));
        delimIndex++;
        str = str.erase(0, delimIndex);
        if (wxString::npos == str.find_first_of(delim) && "" != str){
            items.push_back(str);
            break;
        }
    }
    return items;
}
int CStringUtility::findAny(wxString str, vector<wxString>& delim,
        int startIndex)
{
    int index = 10000;
    vector<wxString>::iterator it = delim.begin();
    while (it != delim.end()){
        int currentIndex = str.find(*it, startIndex);
        if (currentIndex != wxString::npos){
            if (currentIndex < index){
                index = currentIndex;
            }
        }
        it++;
    }
    if (index == 10000){
        return wxString::npos;
    }
    return index;
}
wxString CStringUtility::escape(const wxString& content)
{
    wxString result =content;
    result.Replace("\\","\\\\");
    result.Replace("\"","\\\"");
    return result;
}
}
