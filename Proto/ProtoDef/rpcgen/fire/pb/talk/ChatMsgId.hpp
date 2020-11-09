
#pragma once


namespace fire { 
namespace pb { 
namespace talk { 

class ChatMsgId : public FireNet::Marshal
{
public:
	enum {
		CHAT_SPEED_LIMIT = 140497, // �벻Ҫ˵��̫��
		CANNOT_USE_TEAM_CHANNEL = 140498, // �㻹û�ж���
		CHAT_WORLD_CHANNEL_TIME_LIMIT = 140500, // ÿ��N�����������Ƶ������
		CHAT_WORLD_CHANNEL_LEVEL_LIMIT = 140501, // �ȼ�����N������������Ƶ������
		CANNOT_USE_FACTION_CHANNEL = 141053, // δ���빫��,����ʹ�ù���Ƶ��
		CHAT_TEAM_APPLY_CHANNEL_TIME_LIMIT = 150028, // ÿ��N��������������Ƶ������
		CHAT_SCHOOL_CHANNEL_LEVEL_LIMIT = 160471, // �ȼ�����N��������ְҵƵ������
		CHAT_CURRENT_CHANNEL_LEVEL_LIMIT = 142924, // �ȼ�����N�������ڵ�ǰƵ������
	};

	ChatMsgId() {
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

	bool operator<(const ChatMsgId &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ChatMsgId &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
