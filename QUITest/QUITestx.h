#pragma once

#include "BaseType.h"

class QUITest
{
    SINGLETON_ON_DESTRUCTOR(QUITest)
    {

    }

public:
    QUITest(void);

    // 不要调用的太快！
    BOOL TestUI(LPCWSTR szUIDir, LPCWSTR szMainUI);

protected:
    bool PackUIZip(LPCWSTR szDir, LPCWSTR szDest);
    static unsigned __stdcall thread_ui( void* pparam );
private:
    QString     m_sZip;
    QString     m_sMainUI;
};

