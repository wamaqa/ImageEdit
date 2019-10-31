#pragma once
#include <iostream>
#include <assert.h>

#include <Windows.h>
#include <WinBase.h>

class MemoryMap
{
private:
    WCHAR m_name[256];
    bool m_change;
    HANDLE m_hMap;
    long m_size;
    wchar_t *m_preData;
    wchar_t *m_data;
public:
    bool change() const
    {
        return m_change;
    }


    long Size() const
    {
        return m_size;
    }

    int Init(int size);
    MemoryMap(const wchar_t * name);
    void Write(const wchar_t* str);
    wchar_t* read();
};

