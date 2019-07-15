#include "stdafx.h"
#include "GameMenuBackground.h"
#include "Game.h"


CGameMenuBackground::CGameMenuBackground()
{
    
    m_imgBackground = Image::FromFile(_T("menu_background1.png"));
}

CGameMenuBackground::~CGameMenuBackground()
{
}

void CGameMenuBackground::Draw(Graphics &gh) const
{
    gh.DrawImage(m_imgBackground, m_rect);
}