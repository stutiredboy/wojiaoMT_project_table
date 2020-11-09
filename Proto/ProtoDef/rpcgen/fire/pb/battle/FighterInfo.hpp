
#pragma once

#include <list>
#include <map>

namespace fire { 
namespace pb { 
namespace battle { 

class FighterInfo : public FireNet::Marshal
{
public:
	int fightertype; // ս����Ԫ����
	int64_t dataid; // ս����Ԫ�ı�� ����Ϊ�����roleid ����͹�����Ϊ���е�baseID
	std::wstring fightername; // ս����Ԫ����
	std::wstring title; // ս����Ԫ��ν
	int titleid; // ս����Ԫ��νID
	int awakestate; // ����״̬ 00000 5��bitλ���ӵ�λ����λ�ֱ��ʶ95��99״̬��0-δ���ѣ�1-���ѣ�����ֵ��int��ֵ��
	int index; // ս����Ԫ��ս���е����λ��
	char bgm; // �Ƿ���GM,0:�� 1����
	int maxhp; // ���Ѫ��
	int uplimithp; // Ѫ������
	int hp; // ��ǰѪ��
	int ep; // ��ǰЧ����
	int shape; // ����	����Ϊshortֵ
	int subtype; // �����ͣ�����Ϊ���ʣ�����Ϊ����Ұ���
	std::map<char, int> components; // ��ɫ��װ��Ϣkeyֵ�ο�SpriteComponents��ö�٣�valueΪ0��������ĳ����װ
	std::map<int, int> buffs; // ��ӵ�ս����ӵ�е���ս������ʾ��buff��valueΪ�غ�����Ϊ0��û�лغ����ƣ�
	int footlogoid; // ��ӡid
	std::list<int> petkeys; // �Ѿ���ս�ĳ���

	FighterInfo() {
		fightertype = 0;
		dataid = 0;
		titleid = 0;
		awakestate = 0;
		index = 0;
		bgm = 0;
		maxhp = 0;
		uplimithp = 0;
		hp = 0;
		ep = 0;
		shape = 0;
		subtype = 0;
		footlogoid = 0;
	}

	FighterInfo(int _fightertype_, int64_t _dataid_, const std::wstring & _fightername_, const std::wstring & _title_, int _titleid_, int _awakestate_, int _index_, char _bgm_, int _maxhp_, int _uplimithp_, int _hp_, int _ep_, int _shape_, int _subtype_, const std::map<char, int> & _components_, const std::map<int, int> & _buffs_, int _footlogoid_, const std::list<int> & _petkeys_)
		: fightertype(_fightertype_), dataid(_dataid_), fightername(_fightername_), title(_title_), titleid(_titleid_), awakestate(_awakestate_), index(_index_), bgm(_bgm_), maxhp(_maxhp_), uplimithp(_uplimithp_), hp(_hp_), ep(_ep_), shape(_shape_), subtype(_subtype_), components(_components_), buffs(_buffs_), footlogoid(_footlogoid_), petkeys(_petkeys_) {
	}

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << fightertype;
		_os_ << dataid;
		{
		// utf32 to utf16
		typedef unsigned short utf16;
		FireNet::Octets oct(fightername.length() * 2);
		for(size_t pos =0; pos < fightername.length(); pos++) {
		utf16 ch = (utf16)fightername[pos];
		oct.insert(oct.end(), &ch, 2);
		}
		_os_ << oct; //only for LE
		}
		{
		// utf32 to utf16
		typedef unsigned short utf16;
		FireNet::Octets oct(title.length() * 2);
		for(size_t pos =0; pos < title.length(); pos++) {
		utf16 ch = (utf16)title[pos];
		oct.insert(oct.end(), &ch, 2);
		}
		_os_ << oct; //only for LE
		}
		_os_ << titleid;
		_os_ << awakestate;
		_os_ << index;
		_os_ << bgm;
		_os_ << maxhp;
		_os_ << uplimithp;
		_os_ << hp;
		_os_ << ep;
		_os_ << shape;
		_os_ << subtype;
		_os_ << FireNet::MarshalContainer(components);
		_os_ << FireNet::MarshalContainer(buffs);
		_os_ << footlogoid;
		_os_ << FireNet::MarshalContainer(petkeys);
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> fightertype;
		_os_ >> dataid;
		{
		FireNet::Octets oct;
		_os_ >> oct ;
		if(oct.size() % 2 != 0) {
		throw Marshal::Exception();
		}
		fightername.reserve(oct.size()/2);
		typedef unsigned short utf16;
		// only for little endian
		for(utf16* ch = (utf16*)oct.begin(); ch != oct.end(); ch++)
		{
		fightername.insert(fightername.end(), (wchar_t)*ch);
		}
		}
		{
		FireNet::Octets oct;
		_os_ >> oct ;
		if(oct.size() % 2 != 0) {
		throw Marshal::Exception();
		}
		title.reserve(oct.size()/2);
		typedef unsigned short utf16;
		// only for little endian
		for(utf16* ch = (utf16*)oct.begin(); ch != oct.end(); ch++)
		{
		title.insert(title.end(), (wchar_t)*ch);
		}
		}
		_os_ >> titleid;
		_os_ >> awakestate;
		_os_ >> index;
		_os_ >> bgm;
		_os_ >> maxhp;
		_os_ >> uplimithp;
		_os_ >> hp;
		_os_ >> ep;
		_os_ >> shape;
		_os_ >> subtype;
		_os_ >> FireNet::MarshalContainer(components);
		_os_ >> FireNet::MarshalContainer(buffs);
		_os_ >> footlogoid;
		_os_ >> FireNet::MarshalContainer(petkeys);
		return _os_;
	}

};

} 
} 
} 
