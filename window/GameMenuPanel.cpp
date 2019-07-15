#include "stdafx.h"
#include "GameMenuPanel.h"
#include "Game.h"



CGameMenuPanel::CGameMenuPanel()
{
    
    m_imgBackground = Image::FromFile(_T("menu_background1.png"));

   
    m_menuItems[0].index = 0;
    for(int i = 0; i < 2; ++i) {
        TCHAR path[MAX_PATH];
        _stprintf_s(path, _T("menu_1player_%d.png"), i);
        auto imgPtr = Image::FromFile(path);
        RectF rc(150, 775, static_cast<float>(imgPtr->GetWidth()),
                 static_cast<float>(imgPtr->GetHeight()));
        m_menuItems[0].vImgInfoPtr.push_back(make_tuple(imgPtr, rc));
    }
    
    m_menuItems[1].index = 0;
    for(int i = 0; i < 2; ++i) {
        TCHAR path[MAX_PATH];
        _stprintf_s(path, _T("menu_2plyaer_%d.png"), i);
        auto imgPtr = Image::FromFile(path);
        RectF rc(700, 775, static_cast<float>(imgPtr->GetWidth())
                 , static_cast<float>(imgPtr->GetHeight()));
        m_menuItems[1].vImgInfoPtr.push_back(make_tuple(imgPtr, rc));
    }
}

CGameMenuPanel::~CGameMenuPanel()
{
}

void CGameMenuPanel::Draw(Graphics &gh) const
{
    gh.DrawImage(m_imgBackground, m_rect);

    
    for(auto menuItem : m_menuItems) {
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
        gh.DrawImage(img, rect);
    }
}

void CGameMenuPanel::OnMouseMove(UINT nFlags, CPoint point)
{
    PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
   
    for(auto &menuItem : m_menuItems) {
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
        if(rect.Contains(pt)) {
            menuItem.index = 1;
        }
        else {
            menuItem.index = 0;
        }
    }
}


void CGameMenuPanel::OnLButtonUp(UINT nFlags, CPoint point)
{
    PointF pt(static_cast<float>(point.x), static_cast<float>(point.y));
    {
        auto &menuItem = m_menuItems[0];
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
        if(rect.Contains(pt)) {
           
             m_pParent->SetStep(CGame::EGameTypeOne2BotMenu);
            return;
        }
    }
    {
        auto &menuItem = m_menuItems[1];
        auto img = get<0>(menuItem.vImgInfoPtr[menuItem.index]);
        auto rect = get<1>(menuItem.vImgInfoPtr[menuItem.index]);
        if(rect.Contains(pt)) {
            
            m_pParent->SetStep(CGame::EGameTypeOne2OneMenu);
            return;
        }
    }
}
