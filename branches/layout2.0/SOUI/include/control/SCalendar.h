/**
 * Copyright (C) 2014-2050 SOUI团队
 * All rights reserved.
 * 
 * @file       SCalendar.h
 * @brief      日历时间控件
 * @version    v1.0      
 * @author     soui      
 * @date       2014-05-25
 * 
 * Describe    此类完成日历控件
 */

#pragma once
#include "core/SWnd.h"
#include "Helper/LunarData.h"

namespace SOUI
{
    /**
     * @class      SCalendarCore
     * @brief      日历核心类
     * 
     * Describe    此类是日历的核心类 大部分函数都是静态函数
     */
    class SOUI_EXP SCalendarCore
    {
    public:
        /**
         * SCalendarCore::IsLeapYear
         * @brief    判断闰年
         * @param    WORD wYear -- 待判断的公历年份
		 * @param	 BOOL &bLeapYear -- 【输出参数】TRUE：闰年，FALSE：平年
         * @return   TRUE -- 成功  FALSE -- 失败
         *
         * Describe  判断是否是闰年
					 注意：有效范围是（1600年到6999年）
         */        
        static BOOL IsLeapYear(WORD wYear,BOOL &bLeapYear);

		/**
         * SCalendarCore::GetDaysNumInYear
         * @brief    计算日期在年内的序数（序数从0开始，即0为元旦）
         * @param    WORD wYear -- 公历年
		 * @param	 WORD wMonth -- 公历月
		 * @param	 WORD wDay -- 公历日
		 * @param	 WORD &wDays -- 【输出参数】年内序数
         * @return   TRUE -- 成功  FALSE -- 失败
         *
         * Describe  输入日期，计算该日期在这一年内的序数，序数从0开始
					 注意：有效范围是（START_YEAR年到END_YEAR-1年）
         */ 
		static BOOL GetDaysNumInYear(WORD wYear, WORD wMonth, WORD wDay,WORD &wDays);

		/**
         * SCalendarCore::GetDateFromDays
         * @brief    从年内序数计算月、日
         * @param    WORD wYear -- 公历年
		 * @param	 WORD wDays -- 年内序数
		 * @param	 WORD &wMonth -- 【输出参数】公历月
		 * @param	 WORD &wDay -- 【输出参数】公历日
         * @return   TRUE -- 成功  FALSE -- 失败
         *
         * Describe  输入年份以及年内序数，计算出月和日
					 注意：有效范围是（START_YEAR年到END_YEAR-1年
         */ 
		static BOOL GetDateFromDays(WORD wYear, WORD wDays, WORD &wMonth, WORD &wDay);

		/**
         * SCalendarCore::LunarGetNewYearOrdinal
         * @brief    从年内序数计算月、日
         * @param    WORD wLunarYear -- 农历年份
         * @return   该农历年的正月初一所对应的公历日期的年内序数
         *
         * Describe  输入农历年份，获取正月初一所对应的公历日期的年内序数
					 注意：有效范围是（START_YEAR年到END_YEAR-1年
         */
		static short LunarGetNewYearOrdinal(WORD wLunarYear);

        /**
         * SCalendarCore::GetDayOfWeek
         * @brief    返回星期几
         * @param    WORD wYear -- 公历年
         * @param    WORD wMonth -- 公历月
         * @param    WORD wDay -- 公历日
         * @return   返回:0,1,2,3,4,5,6分别对应日、一、二、三、四、五、六，-1表示日期错误或超出范围
         *
         * Describe  输入年月日返回星期几 
         *           注意:有效范围是(START_YEAR年1月1日 --- END_YEAR-1年12月31日)
         */
		static short GetDayOfWeek(WORD wYear,WORD wMonth,WORD wDay);

        /**
         * SCalendarCore::GetDaysOfMonth
         * @brief    返回指定月份的天数
         * @param    WORD wYear -- 公历年
         * @param    WORD wMonth -- 公历月
         * @return   返回该月的天数，返回0表示输入年月有误
         *
         * Describe  输入年月返回本月的天数 
         *           注意:有效范围是(START_YEAR年1月 --- END_YEAR-1年12月)
         */
        static WORD GetDaysOfMonth(WORD wYear,WORD wMonth);

        /**
         * SCalendarCore::LunarGetDaysofMonth
         * @brief    指定阴历年月分返回该月的天数
         * @param    WORD wLunarYear -- 年
         * @param    WORD wLunarMonth -- 月
		 * @param    WORD bLeapMonth -- 是否闰月
         * @return   返回该月的天数
         *
         * Describe  输入农历年月和闰，返回天数
         *           否则高字为0  注意:有效范围是(START_YEAR-1年十月---END_YEAR-1年（闰）十二月)
         */
        static WORD LunarGetDaysofMonth(WORD wLunarYear,WORD wLunarMonth,BOOL bLeapMonth=FALSE);

        /**
         * SCalendarCore::LunarGetLeapMonth
         * @brief    指定农历年返回该年的闰月月份
         * @param    WORD wLunarYear -- 年
         * @return   返回0表示当年没有闰月 否则是闰月的月份
         *
         * Describe  指定阴历年返回该年的闰月月份
         *           注意:有效范围是(START_YEAR年---END_YEAR-1年)
         */
        static WORD LunarGetLeapMonth(WORD wLunarYear);

		/**
         * SCalendarCore::GetLunar
         * @brief    公历转农历
		 * @param    WORD wYear -- 公历年
		 * @param    WORD wMonth -- 公历月
		 * @param    WORD wDay -- 公历日
         * @param    WORD &wLunarYear -- 【输出参数】农历年
		 * @param    WORD &wLunarMonth -- 【输出参数】公历月
		 * @param    WORD &wLunarDay -- 【输出参数】农历日
		 * @param    BOOL &bLeapMonth -- 【输出参数】农历是否闰月，TRUE：闰月；FALSE：非闰月
         * @return   TRUE -- 成功  FALSE -- 失败
         *
         * Describe  公历转农历
         *           注意:有效范围是(START_YEAR年---END_YEAR-1年)
         */
		static BOOL GetLunar(WORD wYear,WORD wMonth,WORD wDay,WORD &wLunarYear,WORD &wLunarMonth,WORD &wLunarDay,BOOL &bLeapMonth);

		/**
         * SCalendarCore::GetGregorian
         * @brief    农历转公历
		 * @param    WORD wLunarYear -- 农历年
		 * @param    WORD wLunarMonth -- 公历月
		 * @param    WORD wLunarDay -- 农历日
		 * @param    BOOL bLeapMonth -- 农历是否闰月，TRUE：闰月；FALSE：非闰月
		 * @param    WORD &wYear -- 【输出参数】公历年
		 * @param    WORD &wMonth -- 【输出参数】公历月
		 * @param    WORD &wDay -- 【输出参数】公历日
         * @return   TRUE -- 成功  FALSE -- 失败
         *
         * Describe  农历转公历
         *           注意:有效范围是(START_YEAR年---END_YEAR-1年)
         */
		static BOOL GetGregorian(WORD wLunarYear,WORD wLunarMonth,WORD wLunarDay,BOOL bLeapMonth,WORD &wYear,WORD &wMonth,WORD &wDay);

		/**
         * SCalendarCore::DateCheck
         * @brief    检验年、月、日的合法性
         * @param    WORD wYear  -- 公历年 
         * @param    WORD wMonth  -- 公历月 
         * @param    WORD wDay  -- 公历日 
         * @return	 FALSE-失败，TRUE-成功
         *
         * Describe  输入公历日期，检查日期的合法性
         *           注意:有效范围是(START_YEAR年1月1日---END_YEAR-1年12月31日)
         */
		static BOOL DateCheck(WORD wYear,WORD wMonth,WORD wDay);

        /**
         * SCalendarCore::FormatYear
         * @brief    格式化年份显示型式
         * @param    WORD iYear -- 年
         * @param    TCHAR *pBuffer -- 【输出参数】保存格式化后字符串
		 * @param    BOOL bLunar -- 是否为农历，默认为公历
         *
         * Describe  指定阴历年返回采用干支纪年法
         */        
        static void FormatYear(WORD  iYear, TCHAR *pBuffer,BOOL bLunar=FALSE);

        /**
         * SCalendarCore::FormatMonth
         * @brief    格式化月份显示型式
         * @param    WORD iMonth -- 月
         * @param    TCHAR *pBuffer -- 【输出参数】保存格式化后字符串
		 * @param    BOOL bLunar -- 是否为农历输出，默认为公历
         * @param    BOOL bLeapMonth -- 是否是闰月，默认非闰月，bLunar为FALSE时，此参数为无关项
         *
         * Describe  缺省参数bEeapMonth默认为公历
         */        
        static void FormatMonth(WORD iMonth, TCHAR *pBuffer, BOOL bLunar=FALSE, BOOL bLeapMonth=FALSE);
        
        /**
         * SCalendarCore::FormatDay
         * @brief    格式化日期显示型式
         * @param    WORD iDay -- 日
         * @param    TCHAR *pBuffer -- 【输出参数】保存格式化后字符串
		 * @param    BOOL bLunar -- 是否为农历输出，默认为公历
		 * @param    BOOL bShowHoliday -- 是否显示节气及农历假期，只有当bLunar为TRUE时有效，默认为FALSE
         *
         * Describe  默认是按照公历返回，比如说"2日"
         */
        static void FormatDay(WORD wYear,WORD wMonth,WORD wiDay,TCHAR *pBuffer,BOOL bLunar=FALSE,BOOL bShowHoliday=FALSE);

        /**
         * SCalendarCore::GetJieQi
         * @brief    获取指定月份中的两个节气日期
         * @param    WORD wYear  -- 公历年
         * @param    WORD wMonth  -- 公历月
         * @param    WORD wJieQi[2] -- 【输出参数】节气的日期
         * @return   返回值：TRUE -- 获取成功；FALSE -- 获取失败（或超出范围或输入有误）
         *
         * Describe  输入公历年月，返回该月份的两个节气 
         *           注意:有效范围是(START_YEAR年1月---END_YEAR-1年12月)
         */
        static BOOL GetJieQi(WORD wYear,WORD wMonth,WORD wJieQi[2]);

		/**
         * SCalendarCore::GetLunarHoliday
         * @brief    查询指定日期是否为农历节日以及节气、数九、梅雨、三伏
         * @param    WORD wYear -- 公历年
		 * @param    WORD wMonth -- 公历月
		 * @param    WORD wDay -- 公历日
         * @param    TCHAR *pBuffer -- 【输出参数】保存格式化后字符串
		 * @return   返回值：TRUE -- 有节日等信息；FALSE -- 无节日等信息（超出范围或输入有误）
         *
         * Describe  遇到一个日期对应两个或以上的情况，这里做了简单处理，优先级如下：
		 *			 节气 > 农历节日 > 数九、梅雨、三伏 > 农历月份
		 *			 注意:有效范围是(START_YEAR年1月1日---END_YEAR-1年12月31日)
         */
		static BOOL GetLunarHoliday(WORD wYear,WORD wMonth,WORD wDay,TCHAR *pBuffer);

    protected:
        /**
         * SCalendarCore::LunarExpandDX
         * @brief    展开大小月数据表（某一年的）
         * @param    WORD wLunarYear  -- 农历年 
         * @param    WORD wDayOfMonth[15]  -- 【输出参数】从上一年十一月开始到当前年份（闰）十二月的每月天数
         * @return   FALSE-失败，TRUE-成功
         *
         * Describe  输入农历年，获取每个月的天数
         */
		static BOOL LunarExpandDX(WORD wLunarYear,WORD wDayOfMonth[15]);

		/**
         * SCalendarCore::GetExtermSeason
         * @brief    查询指定日期对应的数九、三伏等信息
         * @param    WORD wYear -- 公历年
		 * @param    WORD wMonth -- 公历月
		 * @param    WORD wDay -- 公历日
         * @param    WORD wType -- 指定查询类型：REFTYPE_SUJIU、REFTYPE_MEIYU或REFTYPE_SANFU
		 * @param    WORD &sESIndex -- 【输出参数】对应在名字列表中的序号，详情见函数定义。
		 * @return   返回值：TRUE -- 有数九等信息；FALSE -- 无相关信息（或超出范围或输入有误）
         *
         * Describe  输入公历年、月、日，查询指定日期对应的数九、三伏等信息
		 *			 注意:有效范围是(START_YEAR年1月1日---END_YEAR-1年12月31日)
         */
		static BOOL GetExtermSeason(WORD wYear,WORD wMonth,WORD wDay,WORD wType,WORD &sESIndex);
    };

    /**
     * @class      SCalendar
     * @brief      日历类
     * 
     * Describe    此类是日历的核心类 大部分函数都是静态函数
     */
    class SOUI_EXP SCalendar : public SWindow
    {
    public:
        SOUI_CLASS_NAME(SCalendar, L"calendar")
        
        /**
         * SCalendarCore::SCalendar
         * @brief    构造函数
         * @param    WORD iYear -- 年
         * @param    WORD iMonth -- 月
         * @param    WORD iDay -- 日
         *
         * Describe  构造函数
         */
        SCalendar(WORD iYear, WORD iMonth, WORD iDay);

        /**
         * SCalendar::SCalendar
         * @brief    构造函数
         *
         * Describe  构造函数
         */
        SCalendar();

    public:
        /**
         * SCalendar::GetYear
         * @brief    获得年
         *
         * Describe  获得年
         */
        WORD GetYear(){return m_iYear;}
        
        /**
         * SCalendar::GetMonth
         * @brief    获得月
         *
         * Describe  获得月
         */
        WORD GetMonth(){return m_iMonth;}

        /**
         * SCalendar::GetDay
         * @brief    获得天
         *
         * Describe  获得天
         */
        WORD GetDay(){return m_iDay;}
        
        /**
         * SCalendar::GetDate
         * @brief    获得日期
         * @param    WORD iYear -- 年
         * @param    WORD iMonth -- 月
         * @param    WORD iDay -- 日         
         *
         * Describe  获得日期
         */
        void GetDate(WORD &iYear, WORD &iMonth, WORD &iDay);

        /**
         * SCalendar::SetDate
         * @brief    设置日期
         * @param    WORD iYear -- 年
         * @param    WORD iMonth -- 月
         * @param    WORD iDay -- 日         
         *
         * Describe  设置日期
         */        
        BOOL SetDate(WORD iYear, WORD iMonth, WORD iDay);

    protected:
      /**
       * SCalendar::Init
       * @brief    初始化函数
       *
       * Describe  初始化函数
       */            
        void Init();

        /**
         * SCalendar::OnPaint
         * @brief    绘画消息
         * @param    IRenderTarget *pRT -- 绘制设备句柄
         *
         * Describe  此函数是消息响应函数
         */
        void OnPaint(IRenderTarget *pRT);
        
        /**
         * SCalendar::OnLButtonDown
         * @brief    鼠标左键抬起事件
         * @param    UINT nFlags -- 标志
         * @param    CPoint point -- 鼠标坐标
         *
         * Describe  此函数是消息响应函数
         */
        void OnLButtonDown(UINT nFlags, CPoint point);
        
        /**
         * SCalendar::OnMouseMove
         * @brief    鼠标移动事件
         * @param    UINT nFlags -- 标志
         * @param    CPoint point -- 鼠标坐标
         *
         * Describe  此函数是消息响应函数
         */
        void OnMouseMove(UINT nFlags,CPoint pt);
        
        /**
         * SCalendar::OnMouseLeave
         * @brief    鼠标离开事件
         *
         * Describe  此函数是消息响应函数
         */
        void OnMouseLeave();

        
        /**
         * SCalendar::Load
         * @brief    加载xml
         * @param    pugi::xml_node xmlNode -- xml节点    
         *
         * Describe  通过加载xml来构造窗口
         */
        virtual BOOL InitFromXml(pugi::xml_node xmlNode);
    protected:
        /**
         * SCalendar::GetDayRect
         * @brief    获得日期的坐标
         * @param    WORD iDay  -- 日期         
         *
         * Describe  根据日期所在的周以及星期几，来计算坐标
         */    
        CRect GetDayRect(WORD iDay);
        WORD HitTest(CPoint  pt);

        /**
         * SCalendar::DrawTitle
         * @brief    绘制标题
         * @param    IRenderTarget *pRT -- 绘制设备句柄         
         *
         * Describe  返回只是该日期所在的坐标，采用CRect表示
         */    
        void DrawTitle(IRenderTarget *pRT);
        
        /**
         * SCalendar::DrawDate
         * @brief    绘制日期
         * @param    IRenderTarget *pRT -- 绘制设备句柄         
         *
         * Describe  绘制日期
         */            
        void DrawDate(IRenderTarget *pRT);

        /**
         * SCalendar::DrawDay
         * @brief    绘制日期--天
         * @param    IRenderTarget *pRT -- 绘制设备句柄         
         *
         * Describe  绘制日期--天
         */    
        void DrawDay(IRenderTarget *pRT,CRect & rcDay,WORD iDay );
        
        /**
         * SCalendar::RedrawDay
         * @brief    重新绘制日期--天
         * @param    CDCHandle dc -- 绘制设备句柄         
         *
         * Describe  重新绘制日期--天
         */    
        void RedrawDay(WORD iDay);

        /**
         * SCalendar::OnTodayClick
         * @brief    在日期---天的单击事件
         *
         * Describe  在日期---天的单击事件
         */            
        bool OnTodayClick(EventArgs *pArg);

        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"titleHeight", m_nTitleHei, FALSE)
            ATTR_INT(L"footerHeight", m_nFooterHei, FALSE)
            ATTR_COLOR(L"colorWeekend", m_crWeekend, FALSE)
            ATTR_COLOR(L"colorTitleBack", m_crTitleBack, FALSE)
            ATTR_COLOR(L"colorDay", m_crDay, FALSE)
            ATTR_SKIN(L"daySkin", m_pDaySkin, FALSE)
            ATTR_SKIN(L"titleSkin", m_pTitleSkin, FALSE)
            ATTR_I18NSTRT(L"title-1", m_strTitle[0], FALSE)
            ATTR_I18NSTRT(L"title-2", m_strTitle[1], FALSE)
            ATTR_I18NSTRT(L"title-3", m_strTitle[2], FALSE)
            ATTR_I18NSTRT(L"title-4", m_strTitle[3], FALSE)
            ATTR_I18NSTRT(L"title-5", m_strTitle[4], FALSE)
            ATTR_I18NSTRT(L"title-6", m_strTitle[5], FALSE)
            ATTR_I18NSTRT(L"title-7", m_strTitle[6], FALSE)
        SOUI_ATTRS_END()

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
        SOUI_MSG_MAP_END()
    protected:
        int             m_nTitleHei;    /**< 表头高度 */
        int             m_nFooterHei;   /**< 表尾高度 */
        ISkinObj    *m_pDaySkin;    /**< 日期项皮肤 */
        ISkinObj    *m_pTitleSkin;  /**< 表头皮肤 */

        COLORREF        m_crWeekend;    /**< 周末文字颜色 */
        COLORREF        m_crTitleBack;  /**< 表头背景色 */
        COLORREF        m_crDay;        /**< 选中日期颜色 */
        COLORREF        m_crDayBack;    /**< 选中日期背景颜色 */
        SStringT     m_strTitle[7];  /**< 表头文本 */

        WORD    m_iYear, m_iMonth, m_iDay; /**< 年月日 */
        int        m_iHoverDay;

    };
}//end of namespace

