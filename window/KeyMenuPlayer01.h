#pragma once
#include "GameEntry.h"
#include "GameTimer.h"

class CGame;
class CKeyMenuPlayer01 : public CGameEntryMoveable
{
public:
    CKeyMenuPlayer01();
    ~CKeyMenuPlayer01();


    virtual void Draw(Gdiplus::Graphics &gh) const;


    void SetStop(bool bStop = true)
    {
        m_bStop = bStop;
    };
    bool GetStop() const
    {
        return m_bStop;
    }

private:
    mutable CGameTimeval m_time{300};

    Image *m_img[2];

    bool m_bStop{false};
};

