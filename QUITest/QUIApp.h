#pragma once

#include "ui/qapp.h"
#include "QUIView.h"

class QUIApp : public QApp
{
public:
    QUIApp(LPCWSTR szUIHtml);
    ~QUIApp(void);

protected:
    virtual BOOL InitRun();

private:
    QUIMainFrame        m_frame;
};

