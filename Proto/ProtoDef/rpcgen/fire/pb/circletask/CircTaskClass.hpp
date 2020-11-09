
#pragma once


namespace fire { 
namespace pb { 
namespace circletask { 

class CircTaskClass : public FireNet::Marshal
{
public:
	enum {
		CircTask_Mail = 1, // ����
		CircTask_ItemUse = 2, // ��������
		CircTask_ItemCollect = 3, // �����ռ�
		CircTask_ItemFind = 4, // Ѱ�ҵ���
		CircTask_PetCatch = 5, // �������
		CircTask_Patrol = 6, // Ѳ��
		CircTask_CatchIt = 7, // ׽��
		CircTask_KillMonster = 8, // ɱ�ּ���
		CircTask_ChallengeNpc = 9, // ��սnpc
	};

	CircTaskClass() {
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

	bool operator<(const CircTaskClass &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const CircTaskClass &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
