
#pragma once


namespace fire { 
namespace pb { 
namespace move { 

class SpriteComponents : public FireNet::Marshal
{
public:
	enum {
		SPRITE_WEAPON = 1, // ����
		SPRITE_HEADDRESS = 2, // ͷ��
		SPRITE_BACKDRESS = 3, // ����
		SPRITE_FACEDRESS1 = 4, // ����1
		SPRITE_FACEDRESS2 = 5, // ����2
		SPRITE_HORSEDRESS = 6, // ����
		SPRITE_WEAPONCOLOR = 7, // ������ɫ	������ɫ	byte 1Ϊ��ɫ��2Ϊ��ɫ����4Ϊ��ɫ 5Ϊ��ɫ
		SPRITE_FASHION = 8, // ʱװ
		ROLE_COLOR1 = 50, // Ⱦɫ��λ1
		ROLE_COLOR2 = 51, // Ⱦɫ��λ2
		SPRITE_EQUIP_EFFECT = 60, // װ����Ч
	};

	SpriteComponents() {
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

	bool operator<(const SpriteComponents &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const SpriteComponents &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
