#pragma once
#include <map>
#include <vector>
#include <string>
#define MAX_UUID 50
#include "CVector.h"
#include "Common.h"


class CTriLoaction
{
public:
	CTriLoaction(void);
	~CTriLoaction(void);
private:
	//std::vector<CVector2> m_Out;//新建链表
	std::map<std::string ,std::vector<BEACON_VALUE>*> m_mapBeacon;
	double m_Parameter;
	bool TimeOutClear(std::vector<BEACON_VALUE> *arraybeacon,unsigned int nowtime,double cleartime);
	int m_nCount;
	CVector2  m_UpLocation;
	CVector2 outRefresh;
	unsigned int m_UpTime;
public:
	//设置环境参数n
	void setParametern(double n);
	//输入扫描到的Beacon
	//N 扫描Beacon点数，beacon Beacon值
	void SetScanning(unsigned int N, BEACON_VALUE *beacon );
	//定位计算
	bool Location(double *outx,double *outy);
};