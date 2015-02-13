#pragma once

#include "ui/QWindow.h"

class QUIView : public QFrame
{
    typedef std::list<QUIView*> LstView;
    typedef LstView::iterator LstViewItr;
public:
    QUIView(void);
    ~QUIView(void);

    void SetUIPath(LPCWSTR szHtmlUI);

protected:
    virtual QView* CustomControlCreate(HELEMENT he);

private:
    LstView     m_lstChildView;
};

class QUIMainFrame : public QUIView
{
public:
    

};
