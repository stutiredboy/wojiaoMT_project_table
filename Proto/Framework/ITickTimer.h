/********************************************************************
	filename: 	ITickTimer.h
	purpose:	һ����Tick����Timer����ʱ���Ǻ�׼
*********************************************************************/


#pragma once

#include "ITickObject.h"

class ITickTimer : public ITickObject 
{
public:
	explicit ITickTimer(const int& t);
	virtual ~ITickTimer();

	virtual void OnTimer() = 0;

	void CancelTimer();

	//���return false �Ǿͼ�����һ��Tick�����return ture���Ǿ�ֹͣ��һ��tick
	bool OnTick(int now, int delta);


private:

	int m_Count;//��ʱ��
	bool m_bCancel;
	int m_Time;//OnTimer������Ƶ��,���뼶

};
