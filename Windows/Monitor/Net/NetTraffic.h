#pragma once

#pragma comment(lib,"Iphlpapi.lib");

class NetTraffic
{
public:
	NetTraffic(void);
	~NetTraffic(void);


	int getNetInfo(void);
};
