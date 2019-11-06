#pragma once
#ifndef _MainOperate_
#define _MainOperate_
#include "ConnectPipe.h"
#include <json/value.h>
#include "BaseOperate.h"
#include "Command.h"
#include <opencv2/core/mat.hpp>

class MainOperate : public BaseOperate
{
public:
	cv::Mat m_mat;
	ImageData* Exc(Json::Value &json);
};

#endif
