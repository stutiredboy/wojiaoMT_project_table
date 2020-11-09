
#pragma once


namespace fire { 
namespace pb { 
namespace clan { 

class ClanPositionType : public FireNet::Marshal
{
public:
	enum {
		ClanMember = 11, // ��Ա
		ClanArmyGroupElite4 = 10, // ���ľ��ž�Ӣ
		ClanArmyGroupElite3 = 9, // �������ž�Ӣ
		ClanArmyGroupElite2 = 8, // �ڶ����ž�Ӣ
		ClanArmyGroupElite1 = 7, // ��һ���ž�Ӣ
		ClanArmyGroup4 = 6, // ���ľ��ų�
		ClanArmyGroup3 = 5, // �������ų�
		ClanArmyGroup2 = 4, // �ڶ����ų�
		ClanArmyGroup1 = 3, // ��һ���ų�
		ClanViceMaster = 2, // ���᳤
		ClanMaster = 1, // �᳤
	};

	ClanPositionType() {
	}

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		return _os_;
	}

	bool operator<(const ClanPositionType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ClanPositionType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
