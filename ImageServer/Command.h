#pragma once
#ifndef _Command_
#define _Command_

#include <opencv2\core\hal\interface.h>

//WM_USER                         0x0400

#define  WM_USER_Command  0x0401



#define CMD_OpenFIle 0x0001


struct ImageData
{
	long size;
	long Order;
	void *data;
};

#endif
