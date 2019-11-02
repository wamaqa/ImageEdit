#pragma once

#ifndef _ConnectPipe_
#define _ConnectPipe_

#include "MemoryMap.h"
#include <json/features.h>
#include "Command.h"

class ConnectPipe
{
public:
	MemoryMap* memoryMapRead;
	MemoryMap* memoryMapWrite;


	ConnectPipe();
	Json::Value read();
	void write(const ImageData* data);
};
#endif
