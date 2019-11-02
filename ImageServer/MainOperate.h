#pragma once
#ifndef _MainOperate_
#define _MainOperate_
#include "ConnectPipe.h"
#include <json/value.h>
#include "BaseOperate.h"
#include "Command.h"

class MainOperate : public BaseOperate
{
public:

	ImageData* Exc(Json::Value &json) const;
};

#endif
