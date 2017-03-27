#include "souistd.h"
#include "layout\SLinearLayout.h"
#include "helper\SplitString.h"
#include <algorithm>

namespace SOUI
{

    SLinearLayoutParam::SLinearLayoutParam()
	{
		Clear();
	}

    bool SLinearLayoutParam::IsMatchParent(ORIENTATION orientation) const
    {
        switch(orientation)
        {
        case Horz:
            return width == SIZE_MATCH_PARENT;
        case Vert:
            return height == SIZE_MATCH_PARENT;
        case Any:
            return IsMatchParent(Horz)|| IsMatchParent(Vert);
        case Both:
        default:
            return IsMatchParent(Horz) && IsMatchParent(Vert);
        }
    }

	bool SLinearLayoutParam::IsWrapContent(ORIENTATION orientation) const
	{
        switch(orientation)
        {
        case Horz:
            return width == SIZE_WRAP_CONTENT;
        case Vert:
            return height == SIZE_WRAP_CONTENT;
        case Any:
            return IsWrapContent(Horz)|| IsWrapContent(Vert);
        case Both:
        default:
            return IsWrapContent(Horz) && IsWrapContent(Vert);
        }
	}

    bool SLinearLayoutParam::IsSpecifiedSize(ORIENTATION orientation) const
    {
        switch(orientation)
        {
        case Horz:
            return width >= SIZE_SPEC;
        case Vert:
            return height >= SIZE_SPEC;
        case Any:
            return IsSpecifiedSize(Horz)|| IsSpecifiedSize(Vert);
        case Both:
        default:
            return IsSpecifiedSize(Horz) && IsSpecifiedSize(Vert);
        }

    }

    int SLinearLayoutParam::GetSpecifiedSize(ORIENTATION orientation) const
    {
        switch(orientation)
        {
        case Horz:
            return width;
        case Vert:
            return height;
        case Any: 
        case Both:
        default:
            SASSERT_FMTA(FALSE,"GetSpecifiedSize can only be applyed for Horz or Vert");
            return 0;
        }
    }


    HRESULT SLinearLayoutParam::OnAttrSize(const SStringW & strValue,BOOL bLoading)
    {
		SStringWList szStr ;
		if(2!=SplitString(strValue,L',',szStr)) return E_FAIL;

		OnAttrWidth(szStr[0],bLoading);
		OnAttrHeight(szStr[1],bLoading);
        return S_OK;
    }

    HRESULT SLinearLayoutParam::OnAttrWidth(const SStringW & strValue,BOOL bLoading)
    {
        if(strValue.CompareNoCase(L"matchParent") == 0)
            width = SIZE_MATCH_PARENT;
        else if(strValue.CompareNoCase(L"wrapContent") == 0)
            width = SIZE_WRAP_CONTENT;
        else
            width = _wtoi(strValue);
        return S_OK;
    }

    HRESULT SLinearLayoutParam::OnAttrHeight(const SStringW & strValue,BOOL bLoading)
    {
        if(strValue.CompareNoCase(L"matchParent") == 0)
            height = SIZE_MATCH_PARENT;
        else if(strValue.CompareNoCase(L"wrapContent") == 0)
            height = SIZE_WRAP_CONTENT;
        else
            height = _wtoi(strValue);
        return S_OK;
    }

	void SLinearLayoutParam::Clear()
	{
		width = SIZE_WRAP_CONTENT;
		height = SIZE_WRAP_CONTENT;
		weight = 0.0f;
		gravity = G_Undefined;
	}

	void SLinearLayoutParam::SetMatchParent(ORIENTATION orientation)
	{
        switch(orientation)
        {
        case Horz:
            width = SIZE_MATCH_PARENT;
            break;
        case Vert:
            height = SIZE_MATCH_PARENT;
            break;
        case Both:
            width = height = SIZE_MATCH_PARENT;
            break;
        }
	}

	void SLinearLayoutParam::SetWrapContent(ORIENTATION orientation)
	{
        switch(orientation)
        {
        case Horz:
            width = SIZE_WRAP_CONTENT;
            break;
        case Vert:
            height = SIZE_WRAP_CONTENT;
            break;
        case Both:
            width = height = SIZE_WRAP_CONTENT;
            break;
        }
	}

	void SLinearLayoutParam::SetSpecifiedSize(ORIENTATION orientation, int nSize)
	{
        switch(orientation)
        {
        case Horz:
            width = nSize;
            break;
        case Vert:
            height = nSize;
            break;
        case Both:
            width = height = nSize;
            break;
        }

	}

	void * SLinearLayoutParam::GetRawData()
	{
		return (SLinearLayoutParamStruct*)this;
	}


	//////////////////////////////////////////////////////////////////////////
    SLinearLayout::SLinearLayout(void):m_gravity(G_Undefined)
    {
    }

    SLinearLayout::~SLinearLayout(void)
    {
    }

    void SLinearLayout::LayoutChildren(SWindow * pParent)
    {
        CRect rcParent = pParent->GetChildrenLayoutRect();
		        
        CSize *pSize = new CSize [pParent->GetChildrenCount()];
		SWindow ** pChilds = new SWindow * [pParent->GetChildrenCount()];
		int nChilds = 0;
		
        int offset = 0;
        float fWeight= 0.0f;

        {//assign width or height

            int iChild = 0;

			SWindow *pChild=pParent->GetNextLayoutChild(NULL);
            while(pChild)
            {
				SLinearLayoutParam *pLinearLayoutParam = pChild->GetLayoutParamT<SLinearLayoutParam>();

                CSize szChild(SIZE_WRAP_CONTENT,SIZE_WRAP_CONTENT);
                if(pLinearLayoutParam->IsMatchParent(Horz))
                    szChild.cx = rcParent.Width();
                else if(pLinearLayoutParam->IsSpecifiedSize(Horz))
                {
                    szChild.cx = pLinearLayoutParam->GetSpecifiedSize(Horz);
                    szChild.cx += pLinearLayoutParam->rcExtend.left + pLinearLayoutParam->rcExtend.right;
                }

                if(pLinearLayoutParam->IsMatchParent(Vert))
                    szChild.cy = rcParent.Height();
                else if(pLinearLayoutParam->IsSpecifiedSize(Vert))
                {
                    szChild.cy = pLinearLayoutParam->GetSpecifiedSize(Vert);
                    szChild.cy += pLinearLayoutParam->rcExtend.top + pLinearLayoutParam->rcExtend.bottom;
                }
                
                if(pLinearLayoutParam->weight > 0.0f)
                {
                    fWeight += pLinearLayoutParam->weight;
                }

                if(szChild.cx == SIZE_WRAP_CONTENT || szChild.cy == SIZE_WRAP_CONTENT)
                {
                    CSize szCalc = pChild->GetDesiredSize(szChild.cx,szChild.cy);
                    if(szChild.cx == SIZE_WRAP_CONTENT)
                    {
                        szChild.cx = szCalc.cx;
                        szChild.cx += pLinearLayoutParam->rcExtend.left + pLinearLayoutParam->rcExtend.right;
                    }
                    if(szChild.cy == SIZE_WRAP_CONTENT) 
                    {
                        szChild.cy = szCalc.cy;
                        szChild.cy += pLinearLayoutParam->rcExtend.top + pLinearLayoutParam->rcExtend.bottom;
                    }
                }

				pChilds[iChild] = pChild;
                pSize [iChild] = szChild;
                offset += m_orientation == Vert ? szChild.cy:szChild.cx;

				iChild++;
				pChild=pParent->GetNextLayoutChild(pChild);
            }

			nChilds = iChild;
        }

        int size = m_orientation == Vert? rcParent.Height():rcParent.Width();
        if(fWeight > 0.0f && size > offset)
        {//assign size by weight
            int nRemain = size - offset;
			for(int iChild = 0;iChild < nChilds;iChild ++)
            {
				SWindow *pChild = pChilds[iChild];

				SLinearLayoutParam *pLinearLayoutParam = pChild->GetLayoutParamT<SLinearLayoutParam>();

                if(pLinearLayoutParam->weight > 0.0f)
                {
                    LONG & szChild = m_orientation == Vert? pSize[iChild].cy:pSize[iChild].cx;
                    szChild += (int)(nRemain*pLinearLayoutParam->weight/fWeight);
                }
            }
        }
        {//assign position
            offset = 0;
			for(int iChild = 0;iChild < nChilds;iChild ++)
			{
				SWindow *pChild = pChilds[iChild];


                SLinearLayoutParam *pLinearLayoutParam = pChild->GetLayoutParamT<SLinearLayoutParam>();

                Gravity gravity = pLinearLayoutParam->gravity == G_Undefined? m_gravity:pLinearLayoutParam->gravity;
                if(gravity == G_Undefined) gravity = G_Left;

                if(m_orientation == Vert)
                {
                    CRect rcChild(CPoint(0,offset),pSize[iChild]);
                    rcChild.OffsetRect(rcParent.TopLeft());
                    if(gravity == G_Center)
                        rcChild.OffsetRect((rcParent.Width()-rcChild.Width())/2,0);
                    else if(gravity == G_Right)
                        rcChild.OffsetRect(rcParent.Width()-rcChild.Width(),0);
                    
                    CRect rcChild2 = rcChild;
                    rcChild2.DeflateRect(pLinearLayoutParam->rcExtend);

                    pChild->OnRelayout(rcChild2);

                    offset += rcChild.Height();
                }else
                {
                    CRect rcChild(CPoint(offset,0),pSize[iChild]);
                    rcChild.OffsetRect(rcParent.TopLeft());
                    if(gravity == G_Center)
                        rcChild.OffsetRect(0,(rcParent.Height()-rcChild.Height())/2);
                    else if(gravity == G_Right)
                        rcChild.OffsetRect(0,rcParent.Height()-rcChild.Height());

                    CRect rcChild2 = rcChild;
                    rcChild2.DeflateRect(pLinearLayoutParam->rcExtend);

                    pChild->OnRelayout(rcChild2);

                    offset += rcChild.Width();
                }

            }

        }

		delete []pChilds;
		delete []pSize;

    }

	//nWidth,nHeight == -1:wrap_content
	CSize SLinearLayout::MeasureChildren(SWindow * pParent,int nWidth,int nHeight) const
	{
		CSize *pSize = new CSize [pParent->GetChildrenCount()];


        ILayoutParam * pParentLayoutParam = pParent->GetLayoutParam();

		int iChild = 0;

		SWindow *pChild = pParent->GetNextLayoutChild(NULL);
		while(pChild)
		{
			SLinearLayoutParam *pLinearLayoutParam = pChild->GetLayoutParamT<SLinearLayoutParam>();

			CSize szChild(SIZE_WRAP_CONTENT,SIZE_WRAP_CONTENT);
			if(pLinearLayoutParam->IsMatchParent(Horz))
            {
                if(!pParentLayoutParam->IsWrapContent(Horz))
                    szChild.cx = nWidth;
            }
			else if(pLinearLayoutParam->IsSpecifiedSize(Horz))
            {
                szChild.cx = pLinearLayoutParam->GetSpecifiedSize(Horz);
                szChild.cx += pLinearLayoutParam->rcExtend.left + pLinearLayoutParam->rcExtend.right;
            }
			if(pLinearLayoutParam->IsMatchParent(Vert))
            {
                if(!pParentLayoutParam->IsWrapContent(Vert))
                    szChild.cy = nHeight;
            }
			else if(pLinearLayoutParam->IsSpecifiedSize(Vert))
            {
                szChild.cy = pLinearLayoutParam->GetSpecifiedSize(Vert);
                szChild.cy += pLinearLayoutParam->rcExtend.top + pLinearLayoutParam->rcExtend.bottom;
            }
			if(szChild.cx == SIZE_WRAP_CONTENT || szChild.cy == SIZE_WRAP_CONTENT)
			{
                int nWid = szChild.cx, nHei = szChild.cy;
                if(nWid == SIZE_WRAP_CONTENT)
                    nWid = nWidth * pParentLayoutParam->IsWrapContent(Horz)?-1:1; //把父窗口的WrapContent属性通过-1标志传递给GetDesiredSize
                if(nHei == SIZE_WRAP_CONTENT)
                    nHei = nHeight * pParentLayoutParam->IsWrapContent(Vert)?-1:1;//把父窗口的WrapContent属性通过-1标志传递给GetDesiredSize

				CSize szCalc = pChild->GetDesiredSize(nWid,nHei);
				if(szChild.cx == SIZE_WRAP_CONTENT) 
                {
                    szChild.cx = szCalc.cx;
                    szChild.cx += pLinearLayoutParam->rcExtend.left + pLinearLayoutParam->rcExtend.right;
                }
				if(szChild.cy == SIZE_WRAP_CONTENT) 
                {
                    szChild.cy = szCalc.cy;
                    szChild.cy += pLinearLayoutParam->rcExtend.top + pLinearLayoutParam->rcExtend.bottom;
                }
			}

			pSize [iChild++] = szChild;

			pChild = pParent->GetNextLayoutChild(pChild);
		}
		

		CSize szRet;
		for(int i=0;i<iChild;i++)
		{
			if(m_orientation == Horz)
			{
				szRet.cx += pSize[i].cx;
				szRet.cy = (std::max)(szRet.cy,pSize[i].cy);
			}else
			{
				szRet.cx = (std::max)(szRet.cx,pSize[i].cx);
				szRet.cy += pSize[i].cy;
			}
		}
		delete []pSize;
		return szRet;
	}

	bool SLinearLayout::IsParamAcceptable(ILayoutParam *pLayoutParam) const
	{
		return !!pLayoutParam->IsClass(SLinearLayoutParam::GetClassName());
	}

	ILayoutParam * SLinearLayout::CreateLayoutParam() const
	{
		SLinearLayoutParam *pRet = NULL;
		CreateLayoutParam((IObjRef**)&pRet);
		return pRet;
	}

	HRESULT SLinearLayout::CreateLayoutParam(IObjRef ** ppObj)
	{
		*ppObj = new SLinearLayoutParam();
		return S_OK;
	}

}
