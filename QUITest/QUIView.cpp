#include "StdAfx.h"
#include "QUIView.h"


QUIView::QUIView(void)
{
}

QUIView::~QUIView(void)
{
    for (LstViewItr i = m_lstChildView.begin(); 
        i != m_lstChildView.end(); ++i)
    {
        delete *i;
    }

    m_lstChildView.clear();
}

QView* QUIView::CustomControlCreate( HELEMENT he )
{
    QUIView* pChild = new QUIView;
    m_lstChildView.push_back(pChild);
    return pChild;
}

void QUIView::SetUIPath( LPCWSTR szHtmlUI )
{
    m_sHtmlPath.Format(L"qabs:%s", szHtmlUI);
}

//////////////////////////////////////////////////////////////////////////

