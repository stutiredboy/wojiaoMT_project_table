
#pragma once


namespace fire { 
namespace pb { 
namespace mission { 

class ReadTimeType : public FireNet::Marshal
{
public:
	enum {
		TREASE_MAP = 1, // �ڱ�ͼ
		USE_TASK_ITEM = 2, // ʹ���������
		FOSSICK = 3, // �ɼ�
		OPEN_BOX = 4, // ������
		END_TALK_QUEST = 5, // �����Ի�������
		BEGIN_BATTLE_QUEST = 6, // 6��ʼս��������
		END_AREA_QUEST = 7, // ������
	};

	ReadTimeType() {
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

	bool operator<(const ReadTimeType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ReadTimeType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
