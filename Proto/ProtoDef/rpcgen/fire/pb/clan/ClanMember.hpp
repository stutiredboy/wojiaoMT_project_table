
#pragma once


namespace fire { 
namespace pb { 
namespace clan { 

class ClanMember : public FireNet::Marshal
{
public:
	int64_t roleid; // ��ɫid
	int shapeid; // ͷ��id
	std::wstring rolename; // ��Ա����
	short rolelevel; // ��ɫ�ȼ�
	int rolecontribution; // ���ṱ�׶�
	int weekcontribution; // ���ܹ��ṱ�׶�
	int historycontribution; // ��ʷ���ṱ�׶�
	int rolefreezedcontribution; // ����Ĺ��ṱ�׶�
	int preweekcontribution; // ���ܹ��ṱ�׶�
	int lastonlinetime; // Ϊ0��ʾ���ߣ������ʾ�ϴ�����ʱ��,��λ����
	char position;
	char school; // ְҵ(ְҵ)
	int jointime; // ���빫��ʱ��
	short weekaid; // ����Ԯ��
	int historyaid; // ��ʷԮ��
	char isbannedtalk; // �Ƿ����  0 δ���ԣ� 1����
	int fightvalue; // �ۺ�ս��
	short claninstnum; // �μӹ��ḱ������
	short clanfightnum; // �μӹ���ս����

	ClanMember() {
		roleid = 0;
		shapeid = 0;
		rolelevel = 0;
		rolecontribution = 0;
		weekcontribution = 0;
		historycontribution = 0;
		rolefreezedcontribution = 0;
		preweekcontribution = 0;
		lastonlinetime = 0;
		position = 0;
		school = 0;
		jointime = 0;
		weekaid = 0;
		historyaid = 0;
		isbannedtalk = 0;
		fightvalue = 0;
		claninstnum = 0;
		clanfightnum = 0;
	}

	ClanMember(int64_t _roleid_, int _shapeid_, const std::wstring & _rolename_, short _rolelevel_, int _rolecontribution_, int _weekcontribution_, int _historycontribution_, int _rolefreezedcontribution_, int _preweekcontribution_, int _lastonlinetime_, char _position_, char _school_, int _jointime_, short _weekaid_, int _historyaid_, char _isbannedtalk_, int _fightvalue_, short _claninstnum_, short _clanfightnum_)
		: roleid(_roleid_), shapeid(_shapeid_), rolename(_rolename_), rolelevel(_rolelevel_), rolecontribution(_rolecontribution_), weekcontribution(_weekcontribution_), historycontribution(_historycontribution_), rolefreezedcontribution(_rolefreezedcontribution_), preweekcontribution(_preweekcontribution_), lastonlinetime(_lastonlinetime_), position(_position_), school(_school_), jointime(_jointime_), weekaid(_weekaid_), historyaid(_historyaid_), isbannedtalk(_isbannedtalk_), fightvalue(_fightvalue_), claninstnum(_claninstnum_), clanfightnum(_clanfightnum_) {
	}

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << roleid;
		_os_ << shapeid;
		{
		// utf32 to utf16
		typedef unsigned short utf16;
		FireNet::Octets oct(rolename.length() * 2);
		for(size_t pos =0; pos < rolename.length(); pos++) {
		utf16 ch = (utf16)rolename[pos];
		oct.insert(oct.end(), &ch, 2);
		}
		_os_ << oct; //only for LE
		}
		_os_ << rolelevel;
		_os_ << rolecontribution;
		_os_ << weekcontribution;
		_os_ << historycontribution;
		_os_ << rolefreezedcontribution;
		_os_ << preweekcontribution;
		_os_ << lastonlinetime;
		_os_ << position;
		_os_ << school;
		_os_ << jointime;
		_os_ << weekaid;
		_os_ << historyaid;
		_os_ << isbannedtalk;
		_os_ << fightvalue;
		_os_ << claninstnum;
		_os_ << clanfightnum;
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> roleid;
		_os_ >> shapeid;
		{
		FireNet::Octets oct;
		_os_ >> oct ;
		if(oct.size() % 2 != 0) {
		throw Marshal::Exception();
		}
		rolename.reserve(oct.size()/2);
		typedef unsigned short utf16;
		// only for little endian
		for(utf16* ch = (utf16*)oct.begin(); ch != oct.end(); ch++)
		{
		rolename.insert(rolename.end(), (wchar_t)*ch);
		}
		}
		_os_ >> rolelevel;
		_os_ >> rolecontribution;
		_os_ >> weekcontribution;
		_os_ >> historycontribution;
		_os_ >> rolefreezedcontribution;
		_os_ >> preweekcontribution;
		_os_ >> lastonlinetime;
		_os_ >> position;
		_os_ >> school;
		_os_ >> jointime;
		_os_ >> weekaid;
		_os_ >> historyaid;
		_os_ >> isbannedtalk;
		_os_ >> fightvalue;
		_os_ >> claninstnum;
		_os_ >> clanfightnum;
		return _os_;
	}

};

} 
} 
} 
