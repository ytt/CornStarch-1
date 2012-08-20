#include "LinkableRichTextCtrl.hpp"
#include <vector>
#include "../../../Service/StringUtility.hpp"
using namespace std;

namespace CornStarch
{

CLinkableRichTextCtrl::CLinkableRichTextCtrl()
{
}

CLinkableRichTextCtrl::~CLinkableRichTextCtrl()
{

}
void CLinkableRichTextCtrl::setNavigateHaldler()
{
    // リンククリック時
    this->Connect(this->GetId(), wxEVT_COMMAND_TEXT_URL,
            wxTextUrlEventHandler(CLinkableRichTextCtrl::onNavigate));
}
void CLinkableRichTextCtrl::onNavigate(wxTextUrlEvent& event)
{
    wxString url = event.GetString();
    wxString command = "open " + url;
    system(command.c_str());

    // キャレットをリンクの場所から移動
    this->MoveEnd();

}
void CLinkableRichTextCtrl::writeLinkableText(const wxString& content)
{
    vector<wxString> delimiter;
    delimiter.push_back("http");
    delimiter.push_back("//");


    vector<wxString> delimiterSpace;
    delimiterSpace.push_back(" ");
    delimiterSpace.push_back("　");

    int urlIndex = CStringUtility::findAny(content,delimiter);// content.find("http", 0);
    if (urlIndex != wxString::npos){
        // リンクが始まるまでの文字を表示
        if (urlIndex != 0){
            WriteText(content.substr(0, urlIndex));
        }
        int endIndex = 0;
        while (urlIndex != wxString::npos){
            endIndex = CStringUtility::findAny(content,delimiterSpace,urlIndex);//content.find(" ", urlIndex);

            wxString url;
            if (endIndex != wxString::npos){
                url = content.substr(urlIndex, endIndex - urlIndex);
            } else{
                url = content.substr(urlIndex);
            }
#ifndef _WIN32
            if(url.find("//")==0)
            {
                url = "smb:"+ url;
            }
#endif
            this->BeginUnderline();
            this->BeginURL(url);
            WriteText(url);
            this->EndURL();
            this->EndUnderline();

            if (endIndex != wxString::npos){
                urlIndex = CStringUtility::findAny(content,delimiter,endIndex);//content.find("http", endIndex);
                // 次のリンクまでの文字を表示
                if (urlIndex != wxString::npos){
                    WriteText(content.substr(endIndex, urlIndex - endIndex));
                }
            } else{
                // 継続文字がなければ終了。
                return;
            }
        }
        // 残りの文字を表示
        WriteText(content.substr(endIndex));
    } else{
        WriteText(content);
    }
}
} /* namespace CornStarch */
