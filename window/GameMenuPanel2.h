#pragma once
#include "GameEntry.h"


class CGame;
class CGameMenuPanel2 : CGameEntryMoveable
{
public:
    CGameMenuPanel2();
    ~CGameMenuPanel2();

    CGame *m_pParent{ nullptr };


    virtual void Draw(Gdiplus::Graphics &gh) const;


    void OnMouseMove(UINT nFlags, CPoint point);

 
    void OnLButtonUp(UINT nFlags, CPoint point);


    Image *m_img{nullptr};

    bool m_bNormal{true};
};

