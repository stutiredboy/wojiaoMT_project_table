
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class NpcServices : public FireNet::Marshal
{
public:
	enum {
		FORTUNE_WHEEL = 14, // ���˴�ת��
		SEND_MAIL = 69, // ����: (��̬����)
		CHECK_CHIEF_ABILITY = 96, // �鿴��ϯ-��������
		CHALLENGE_CHIEF = 97, // ��ս��ϯ-����
		RUN_FOR_CHIEF = 98, // ��Ҫ��ѡ
		VOTING = 99, // ��ҪͶƱ
		REFRESH_CHIEF_ABILITY = 100, // ��Ҫˢ����ϯ-��������
		ATTEND_IMPEXAM = 136, // ��Ҫ�μ��ǻ�����
		LEARN_IMPEXAM_RULE = 137, // �����˽��ǻ�������������
		WINNER_START = 166, // ׼������,��������ǵ�һ�ص���ս�ص�
		CHECK_PERSONAL_CREDIT = 167, // �����ѯ���Լ��Ļ����
		ADD_PET_LIFE = 168, // �������ӳ�������
		FIGHT_WINNER = 171, // ��ս�ھ���������
		ENTER_BINGFENG = 355, // �����������
		BACK_COPY_SERVICE = 1469, // �ص���������
		CIRCTASK_SCHOOL1 = 3000, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL2 = 3001, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL3 = 3002, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL4 = 3003, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL5 = 3004, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL6 = 3005, // ��ѭ������-ְҵ
		CIRCTASK_SCHOOL_SUBMIT1 = 3010, // ��ѭ�������ύ-ְҵ
		CIRCTASK_SCHOOL_SUBMIT2 = 3011, // ��ѭ�������ύ-ְҵ
		CIRCTASK_SCHOOL_SUBMIT3 = 3012, // ��ѭ�������ύ-ְҵ
		CIRCTASK_SCHOOL_SUBMIT4 = 3013, // ��ѭ�������ύ-ְҵ
		CIRCTASK_SCHOOL_SUBMIT5 = 3014, // ��ѭ�������ύ-ְҵ
		CIRCTASK_SCHOOL_SUBMIT6 = 3015, // ��ѭ�������ύ-ְҵ
		CATCH_IT = 4000, // ѭ������-׽��
		CATCH_IT_SUBMIT = 4001, // ѭ������-׽��
		CATCH_IT_QUERY = 4002, // ѭ������-��ѯ׽��
		CATCH_IT_BJ = 4003, // ѭ������-���׽��
		CATCH_IT_Battle = 4004, // ѭ������-׽������ս��
		TIMER_NPC_Battle = 4005, // ��ʱˢ�ֽ���ս��
		EVENT_NPC_Battle = 4006, // �¼�ˢ�ֽ���ս��
		SUBMIT_CIRCTASK = 5000, // �ύѭ������
		RENXING_CIRCTASK = 5001, // ����һ��ѭ������
		BUY_MEDICINE = 30000, // ����ҩƷ
		BUY_GOODS = 30001, // ������Ʒ
		BUY_EQUIP = 30002, // ����װ��
		BUY_PET = 30003, // �������
		OPEN_SHANGHUI = 30004, // ���̻�
		QUERY_LINEINST = 100049, // ��ѯ��Ӣ��������
		RESET_LINEINST = 100187, // ���ø���
		ONE_LIEVEL_TITLE = 900054, // һ����ν by changhao
		TWO_LIEVEL_TITLE = 900055, // ������ν by changhao
		THREE_LIEVEL_TITLE = 900056, // ������ν by changhao
		LEADER_SEE_CAMPAIGN_LIST = 900057, // �鿴��ѡ���� by changhao
		LEADER_MY_CAMPAIGN = 900058, // �ҵľ�ѡ by changhao
		LEADER_CHALLENGE = 900059, // ��ս���� by changhao
		LEADER_CAMPAIGN = 900060, // ��ѡ���� by changhao
		PET_STORE = 100012, // ����ֿ�
		EXCHANGE_CODE = 100600, // �һ���
		IMPEXAM_STATE = 100704, // �ǻ�����
		LOOK_YAO_QIAN = 200101, // �չ�ҡǮ��
		ENTER_1V1_PVP = 910000, // ����ȥ������
		LEAVE_1V1_PVP = 910004, // �뿪������
		ENTER_3V3_PVP = 910010, // ����ȥ3v3������
		LEAVE_3V3_PVP = 910014, // �뿪3v3������
		ENTER_5V5_PVP = 910020, // ����ȥ5v5������
		LEAVE_5V5_PVP = 910024, // �뿪5v5������
		WATCH_NPC_BATTLE = 910115, // ��ʱ�����׹ֹ�ս
		WATCH_EVENTNPC_BATTLE = 910116, // �¼������׹ֹ�ս
		WATCH_INST_NPC_BATTLE = 910201, // ���ḱ����ս��ť����
		END_INST_NPC_BATTLE = 910202, // ���ḱ����ֹս������
		ENTER_CLAN_FIGHT = 910030, // ���빫��ս by changhao
	};

	NpcServices() {
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

	bool operator<(const NpcServices &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const NpcServices &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 