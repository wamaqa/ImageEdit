#include "MainOperate.h"
#include "Command.h"
#include <opencv2/imgcodecs.hpp>
#include<opencv2\highgui\highgui.hpp>
ImageData* MainOperate::Exc(Json::Value& json)
{
	int cmd = json["Command"].asInt();
	long source = json["Source"].asInt64();
	Json::Value jsonData = json["Data"];
	switch (cmd)
	{
	case CMD_OpenFIle:
	{
		m_mat = cv::imread(jsonData[0].asString());
		ImageData* image_data = new ImageData();
		std::vector<int> param = std::vector<int>(2);
		param[0] = cv::IMWRITE_PNG_COMPRESSION;
		param[1] = 3;
		std::vector<uchar> buff;
		cv::imencode(".png", m_mat, buff, param);
		image_data->size = buff.size() * sizeof(uchar);
		image_data->Order = source;
		image_data->data = malloc(image_data->size);
		memcpy(image_data->data, &buff[0],image_data->size);
		return image_data;
	}break;
	case CMD_SetExposure:
	{
		double a = jsonData[0].asDouble();
		double b = jsonData[1].asDouble();
		double c = jsonData[2].asDouble();
		cv::Mat g_dstImage = cv::Mat::zeros(m_mat.size(), m_mat.type());
		for (int y = 0; y < m_mat.rows; y++) {
			for (int x = 0; x < m_mat.cols; x++) {
				for (int z = 0; z < m_mat.channels(); z++) {
					g_dstImage.at<cv::Vec3b>(y, x)[z] =
						cv::saturate_cast<uchar>((b * m_mat.at<cv::Vec3b>(y, x)[z]) + c);
				}
			}
		}
		ImageData* image_data = new ImageData();
		std::vector<int> param = std::vector<int>(2);
		param[0] = cv::IMWRITE_PNG_COMPRESSION;
		param[1] = 3;
		std::vector<uchar> buff;
		cv::imencode(".png", g_dstImage, buff, param);
		image_data->size = buff.size() * sizeof(uchar);
		image_data->Order = source;
		image_data->data = malloc(image_data->size);
		memcpy(image_data->data, &buff[0], image_data->size);
		return image_data;
	}break;
	default:;
	}
	return nullptr;
}

