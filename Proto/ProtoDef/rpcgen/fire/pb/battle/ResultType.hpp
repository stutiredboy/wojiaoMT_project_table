
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class ResultType : public FireNet::Marshal
{
public:
	enum {
		RESULT_HPCHANGE = 1, // 1:Ŀ��HP�仯
		RESULT_MPCHANGE = 2, // 2:Ŀ��MP�仯
		RESULT_SPCHANGE = 4, // 3:Ŀ��SP�仯
		RESULT_ULHPCHANGE = 8, // 4:��ǰѪ���ޣ��ˣ��仯
		RESULT_REST = 16, // 5:��Ϣ
		RESULT_HURT = 32, // 6:Ŀ������
		RESULT_CRITIC = 64, // 7:Ŀ�걻����
		RESULT_DEFENCE = 128, // 8:Ŀ�����
		RESULT_PARRY = 256, // 9:Ŀ���мܣ����ƶ�����ֻ����ͨ�����ᴥ���мܣ�
		RESULT_DODGE = 512, // 10:Ŀ������
		RESULT_RUNAWAY = 1024, // 11:Ŀ������
		RESULT_SEIZE = 2048, // 12:Ŀ�걻��׽
		RESULT_SUMMONBACK = 4096, // 13:Ŀ�걻�ٻ�
		RESULT_DEATH = 8192, // 14:Ŀ������������ԭ��
		RESULT_KICKOUT = 16384, // 15:Ŀ�걻���ɣ�û�й�꼼�ܵĹֺͳ�������ʱ��
		RESULT_GHOST = 32768, // 16:Ŀ�������״̬���й�꼼�ܵĹֺͳ�������ʱ��
		RESULT_RELIVE = 65536, // 17:����
		RESULT_SUMMONPET = 131072, // 18:Ŀ���л�����
		RESULT_IGNORE_PHYDIC_EFEN = 262144, // 19:���Է���
		RESULT_ABORBE = 524288, // 20:����
		RESULT_FIRE_MANA = 1048576, // 21:����
		RESULT_GODBLESS = 2097152, // 22:����
		RESULT_EPCHANGE = 4194304, // 23:Ŀ��EP�仯
		RESULT_DEAD_FULL_RELIVE = 8388608, // 24:��Ѫ����
		RESULT_SHAPECHAGE = 16777216, // 25:ģ�͸ı�
	};

	ResultType() {
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

	bool operator<(const ResultType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ResultType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
