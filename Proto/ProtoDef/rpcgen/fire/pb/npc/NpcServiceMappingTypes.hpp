
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class NpcServiceMappingTypes : public FireNet::Marshal
{
public:
	enum {
		NONE = 0,
		ACCEPT_CIRCLE_TASK = 1, // ������
		SUBMIT_CIRCLE_TASK = 2, // �ύ����
		QUERY_CIRCLE_TASK = 3, // ��ѯ����
		QUERY_CIRCLE_TEAM = 4, // ������
		QUERY_CIRCLE_BATTLE = 5, // ����ս��
		CIRCLE_PRODUCE = 6, // ������Ʒ
		RENXING_CIRCLE_TASK = 7, // ��������
		CHALLENGE_NPC = 9, // NPC��ս
		ENTER_INST = 10, // ���븱��
		POP_UI = 11, // ���������
		QUERY_CAMERA_URL = 12, // ����¼��·��
		ACCEPT_TUPO = 13, // ��ͻ������
	};

	NpcServiceMappingTypes() {
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

	bool operator<(const NpcServiceMappingTypes &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const NpcServiceMappingTypes &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
