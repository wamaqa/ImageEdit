#pragma warning(disable : 4996)
#include "MemoryMap.h"

int MemoryMap::Init(int size)
{
	m_size = size * sizeof(wchar_t);
	m_data = malloc(m_size);
	m_hMap = ::OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, m_name);
	if (!m_hMap)
	{
		PSECURITY_DESCRIPTOR pSec = (PSECURITY_DESCRIPTOR)LocalAlloc(LMEM_FIXED, SECURITY_DESCRIPTOR_MIN_LENGTH);
		if (!pSec)
		{
			return GetLastError();
		}
		if (!InitializeSecurityDescriptor(pSec, SECURITY_DESCRIPTOR_REVISION))
		{
			LocalFree(pSec);
			return GetLastError();
		}
		if (!SetSecurityDescriptorDacl(pSec, TRUE, NULL, TRUE))
		{
			LocalFree(pSec);
			return GetLastError();
		}
		SECURITY_ATTRIBUTES attr;
		attr.bInheritHandle = FALSE;
		attr.lpSecurityDescriptor = pSec;
		//´´½¨  
		m_hMap = ::CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_EXECUTE_READWRITE, 0, m_size, m_name);
		if (!m_hMap)
		{
			return -1;
		}
	}
	return 0;
}

MemoryMap::MemoryMap(const wchar_t* name)
{
	wcscpy(m_name, name);
}



void MemoryMap::Write(const void* buff)
{
	LPVOID lpBase = ::MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	memcpy(lpBase, buff, m_size);
}

void MemoryMap::Write(const void* buff, int size)
{
	LPVOID lpBase = ::MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	memcpy(lpBase, buff, size);
}

void* MemoryMap::read()
{
	LPVOID lpBase = ::MapViewOfFile(m_hMap, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (lpBase == NULL)
	{
		return nullptr;
	}
	void *w = lpBase;
	memcpy(m_data, w, m_size);
	return m_data;

}
