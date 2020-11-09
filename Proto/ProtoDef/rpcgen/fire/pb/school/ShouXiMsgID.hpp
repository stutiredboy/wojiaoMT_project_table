
#pragma once


namespace fire { 
namespace pb { 
namespace school { 

class ShouXiMsgID : public FireNet::Marshal
{
public:
	enum {
		ChallengeLevelNotEnough = 140245, // ��ս��ϯ-�����Ǻ�Σ�յģ�40���Ժ�������ս�ɣ���
		SchoolContriNotEnough = 140246, // ���ְҵ���׶Ȳ���500�㣬�޷�������ս��
		InTeam = 140247, // ���뿪���������μ���ս�ɣ�
		MoneyNotEnough = 140248, // �����ϵĽ�Ǯ������10000������
		ChallengeSuccess = 140249, // ��ս�ɹ�������Բ���ְҵ��ϯ-���Ӿ�ѡ�ˣ�
		ChallengeLost = 140250, // ��սʧ�ܣ�ϣ�����´��ٽ�����!
		NotSuccess = 140251, // ����δ�ɹ���ս��ϯ-���ӣ����ܲμӾ�ѡ��
		AlreadyCandidate = 140252, // ���ѳɹ���ѡ��
		VoteLevelNotEnough = 140253, // �ȼ���30������ҷ��ɲ���ͶƱŶ��
		TiLiNotEnough = 140254, // ������������100�㣬����ͶƱ��
		AlreadyVote = 140255, // ���������Ѿ�Ͷ��Ʊ��������Ͷ�ˣ�
		GiveShouXiTitle = 140256, // ��ϲ��������ϯ-���ӳƺš�
		CancelShouXiTitle = 140257, // �ܱ�Ǹ�����Ѳ�������ϯ-���ӡ�
		RefreshAbilityToMuch = 140258, // ��Ϣһ�£����������ɣ�
		ChallengeAffirm = 140259, // ��ս��ϯ-������Ҫ����10000����Ǯ���Ƿ�ȷ����ս��
		Cantvote = 140260, // ���ڲ���ͶƱʱ��Ŷ��
		CantChallenge = 140261, // ���ڲ�����սʱ��Ŷ��
	};

	ShouXiMsgID() {
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

	bool operator<(const ShouXiMsgID &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ShouXiMsgID &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
