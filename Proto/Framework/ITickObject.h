/********************************************************************
	filename: 	ITickObject.h
	purpose:	
*********************************************************************/

#pragma once

class ITickObject 
{
public:
	virtual ~ITickObject(){}

	//���return false �Ǿͼ�����һ��Tick�����return ture���Ǿ�ֹͣ��һ��tick
	virtual bool OnTick(int now, int delta) = 0;
};
