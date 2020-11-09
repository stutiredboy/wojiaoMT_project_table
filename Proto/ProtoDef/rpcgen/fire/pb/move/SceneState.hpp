
#pragma once


namespace fire { 
namespace pb { 
namespace move { 

class SceneState : public FireNet::Marshal
{
public:
	enum {
		BATTLE_FIGHTER = 1, // 1:ս��״̬
		BATTLE_WATCHER = 2, // 2:��ս״̬
		BATTLE_REPLAY = 4, // 4:�ۿ�¼��
		PLAY_CG = 8, // 8:��������
		NO_PAY_DAY = 16, // 16û��֧���տ� by changhao
		GM_FLAG = 2097152, // 22:��������ʾgmͼ��
	};

	SceneState() {
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

	bool operator<(const SceneState &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const SceneState &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
