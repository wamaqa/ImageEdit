#pragma once
#ifndef _MemoryMap_
#define _MemoryMap_
#include <iostream>
#include <assert.h>

#include <Windows.h>
#include <WinBase.h>

class MemoryMap
{
private:
    WCHAR m_name[256];
    HANDLE m_hMap;
    long m_size;
	void* m_data;
public:

    long Size() const
    {
        return m_size;
    }

    int Init(int size);
    MemoryMap(const wchar_t * name);
    void Write(const void* str);
	void Write(const void* str, int size);
    void* read();
};
#endif

