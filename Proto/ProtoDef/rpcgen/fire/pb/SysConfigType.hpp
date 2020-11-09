
#pragma once


namespace fire { 
namespace pb { 

class SysConfigType : public FireNet::Marshal
{
public:
	enum {
		Music = 1, // ����
		Volume = 2, // ����
		SoundSpecEffect = 3, // ��Ч
		SceneEffect = 4, // ������Ч
		MaxScreenShowNum = 5, // ����ͬ�������ʾ����
		ScreenRefresh = 6, // ����ˢ��Ƶ��
		AutoVoiceGang = 7, // �Զ�����--����Ƶ��
		AutoVoiceWorld = 8, // �Զ�����--����Ƶ��
		AutoVoiceTeam = 9, // �Զ�����--���Ƶ��
		AutoVoiceSchool = 10, // �Զ�����--ְҵƵ��
		RefuseFriend = 11, // �ܾ���������
		WorldChannel = 12, // ����Ƶ��
		GangChannel = 13, // ����Ƶ��
		SchoolChannel = 14, // ְҵƵ��
		CurrentChannel = 15, // ��ǰƵ��
		TeamChannel = 16, // ���Ƶ��
		PVPNotify = 17, // PVPNotify
		friendchatencrypt = 18, // ���������¼����
		friendmessage = 19, // ֻ���ܺ�����Ϣ
		rolePointAdd = 20, // rolePointAdd
		petPointAdd = 21, // petPointAdd
		skillPointAdd = 22, // skillPointAdd
		huoyueduAdd = 23, // huoyueduAdd
		zhenfaAdd = 24, // zhenfaAdd
		skillopen = 25, // ���ܿ���
		factionopen = 26, // ���Ὺ��
		petopen = 27, // ���￪��
		patopen = 28, // ��ս����
		zuduichannel = 29, // ���Ƶ��
		guajiopen = 30, // �һ�����
		zhiyinopen = 31, // ָ������
		huodongopen = 32, // �����
		refuseqiecuo = 33, // �д�
		ts_julonghuwei = 34, // ���;�������
		ts_julongjuntuan = 35, // ���;�������
		ts_guanjunshilian = 36, // ���͹ھ�����
		ts_renwentansuo = 37, // ��������̽��
		ts_1v1 = 38, // ����1v1
		ts_gonghuifuben = 39, // ���͹��ḱ��
		ts_3v3 = 40, // ����3v3
		ts_zhihuishilian = 41, // �����ǻ�����
		refuseclan = 42, // �ܾ���������
		refuseotherseeequip = 43, // �ܾ����˲鿴װ�� by changhao
		screenrecord = 44, // ¼������
		equipendure = 45, // װ���;�
		ts_gonghuizhan = 46, // ����ս
		rolldianshezhi = 47, // ROLL������
		framesimplify = 48, // �����
	};

	SysConfigType() {
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

	bool operator<(const SysConfigType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const SysConfigType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
