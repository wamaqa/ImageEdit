#include "ConnectPipe.h"
#include "StringUtils.h"
#include <json/value.h>
#include <json/reader.h>

ConnectPipe::ConnectPipe()
{
	memoryMapRead = new MemoryMap(L"ImageEdit");
	memoryMapWrite = new MemoryMap(L"ImageServer");
	memoryMapRead->Init(1024);
	memoryMapWrite->Init(8*1024*1024 * 100);
}

Json::Value ConnectPipe::read()
{
	wchar_t* data = static_cast<wchar_t*>(memoryMapRead->read());
	Json::Value json;
	Json::CharReaderBuilder readerBuilder;
	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	string str = WChar2Ansi(data);
	bool res;
	JSONCPP_STRING errs;
	res = jsonReader->parse(str.c_str(), str.c_str() + str.length(), &json, &errs);
	return json;
}

void ConnectPipe::write(const ImageData* data)
{
	memoryMapWrite->Write(data->data, data->size);
	PostMessage((HWND)data->Order, WM_USER_Command, data->size, 12);
}
