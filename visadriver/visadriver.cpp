// visadriver.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "include/visa.h"
#include <string>
#pragma comment(lib,"visa32.lib")
#define MAX_SCPI_LENGTH 255                         // 最大的SCPI命令 
#define DEFAULT_TIMEOUT 5000                    // 超时:5000ms   

int main(void)
{
	ViStatus nReturnStatus = 0;                         // 保存返回数值
	ViSession rmSession = 0, pnInstrHandle;
	ViPUInt32 retCnt = 0;
	ViByte wrtBuf[MAX_SCPI_LENGTH];                     // 写缓冲区
	ViByte rdBuf[MAX_SCPI_LENGTH];                      // 读缓冲区
	int Return_Count;
	nReturnStatus = viOpenDefaultRM(&rmSession);
	nReturnStatus = viOpen(rmSession, ViRsrc("TCPIP0::172.141.114.6::5001::SOCKET"), VI_NULL, VI_NULL, &pnInstrHandle);

	/*- Configure VISA Formatted I/O ----------------------------------------*/
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_TMO_VALUE, DEFAULT_TIMEOUT);        // 设置超时
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SUPPRESS_END_EN, VI_FALSE);        // 不发送终止符
	nReturnStatus = viSetAttribute(pnInstrHandle, VI_ATTR_SEND_END_EN, VI_FALSE);        // 不接收终止符

	nReturnStatus = viQueryf(pnInstrHandle, ViRsrc("*IDN?\n"), ViRsrc("%s"), rdBuf);
	nReturnStatus = viWrite(pnInstrHandle, "*IDN?", 6, retCnt);
	viClose(pnInstrHandle);
	viClose(rmSession);
    return 0;
}

