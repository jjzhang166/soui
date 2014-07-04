#include "duistd.h"
#include "mybuffer.h"
#include "res.mgr/DuiPools.h"

namespace SOUI
{
    SPools::SPools()
    {
    }

    SPools::~SPools(void)
    {
    }

    void SPools::Init( LPCTSTR pszInitXml ,LPCTSTR pszResType)
    {
        pugi::xml_document xmlDoc;
        if(LOADXML(xmlDoc,pszInitXml,pszResType))
        {
            Init(xmlDoc.first_child());
        }
    }

    void SPools::Init( pugi::xml_node xmlNode )
    {
        //load string table
        pugi::xml_node xmlStr=xmlNode.child(L"string");
        if(xmlStr)
        {
            DuiStringPool::Init(xmlStr);
        }
        //load style table
        pugi::xml_node xmlStyle=xmlNode.child(L"style");
        if(xmlStyle)
        {
            DuiStylePool::Init(xmlStyle);
        }
        //load skin
        pugi::xml_node xmlSkin=xmlNode.child(L"skins");
        if(xmlSkin)
        {
            DuiSkinPool::Init(xmlSkin);
        }
        pugi::xml_node xmlObjAttr=xmlNode.child(L"objattr");
        //load objattr
        if(xmlObjAttr)
        {
            DuiCSS::Init(xmlObjAttr);
        }
    }

    void SPools::Clear()
    {
        DuiStringPool::RemoveAll();
        DuiStylePool::RemoveAll();
        DuiSkinPool::RemoveAll();
        DuiCSS::RemoveAll();
    }
}//end of namespace
