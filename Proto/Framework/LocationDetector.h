//////////////////////////////////////////////////////////////////////////
// File:		LocationDetector.h
// Author:	���
// Date:		2016/05/10
//////////////////////////////////////////////////////////////////////////

#ifndef _LocationDetector_h_
#define _LocationDetector_h_

#include "Singleton.hpp"
#include <string>
#include <vector>

class LocationDetector : public CSingleton < LocationDetector >
{
public:
	struct Location
	{
		double mLongitude;  // ����
		double mLatitude;  // γ��
		std::string mName;  // �������磺����.������.�쳩԰
	};
	typedef std::vector<Location> LocationArray;

private:
	std::string mFinishCallbackFunc;
	LocationArray mLocations;

public:
	LocationDetector();
	~LocationDetector();
    
    // ���ض�λ�����Ƿ����
    bool isAvailable() const;
    // ���ر�APP�Ƿ�����ʹ�ö�λ
    bool isAllowed() const;

	// ������ɶ�λ��Ļص��ű�����
	void setFinishCallbackFunction(const std::string& finishCallbackFunc) { mFinishCallbackFunc = finishCallbackFunc; }
	// ��ʼ��λ
	void startDetect();

	// ��λ��ɺ���Ե������к�����ȡ��λ��Ϣ

	// ��ȡλ������
	int getLocationCount() const { return (int)mLocations.size(); }
	// ��ȡλ��
	const Location getLocation(int index) const;

    // called by platform
	void clear() { mLocations.clear(); }
	void addLocation(const Location& loc) { mLocations.push_back(loc); }

	void onFinishDetect(bool bSuccess);
};

#endif