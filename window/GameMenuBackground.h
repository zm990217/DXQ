#pragma once

#include "GameEntry.h"

class CGame;

class CGameMenuBackground : public CGameEntryMoveable
{
public:
    CGameMenuBackground();
    ~CGameMenuBackground();

    void SetParent(CGame *g)
    {
        m_pParent = g;
    };

    CGame *m_pParent{ nullptr };

    
    virtual void Draw(Graphics &gh) const;

   
    RectF m_rect{0, 0, 1920, 1080};

 
    Image *m_imgBackground;
};
