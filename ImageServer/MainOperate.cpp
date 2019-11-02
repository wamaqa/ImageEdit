#include "MainOperate.h"
#include "Command.h"
#include <opencv2/imgcodecs.hpp>
#include<opencv2\highgui\highgui.hpp>
ImageData* MainOperate::Exc(Json::Value& json) const
{
	int cmd = json["Command"].asInt();
	long source = json["Source"].asInt64();
	Json::Value jsonData = json["Data"];
	switch (cmd)
	{
	case CMD_OpenFIle:
	{
		cv::Mat mat = cv::imread(jsonData[0].asString());
		PostThreadMessage(source, WM_USER_Command, 12, 12);
		ImageData* image_data = new ImageData();
		std::vector<int> param = std::vector<int>(2);
		param[0] = cv::IMWRITE_PNG_COMPRESSION;
		param[1] = 1;
		std::vector<uchar> buff;
		cv::imencode(".png", mat, buff, param);
		image_data->size = buff.size() * sizeof(uchar);
		image_data->Order = source;
		image_data->data = malloc(image_data->size);
		memcpy(image_data->data, &buff[0],image_data->size);
		return image_data;
	}break;
	default:;
	}
	return nullptr;
}

