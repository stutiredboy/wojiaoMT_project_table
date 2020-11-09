
#pragma once

#include "fire/pb/battle/DemoAttr.hpp"
#include "fire/pb/battle/DemoBuff.hpp"
#include <list>
#include <map>

namespace fire { 
namespace pb { 
namespace battle { 

class NewDemoResult : public FireNet::Marshal
{
public:
	enum {
		HP_CHANGE = 1, // �ܻ���Ѫ���仯��Ϊ���Ǽ�Ѫ��Ϊ���ǿ�Ѫ
		MP_CHANGE = 2, // �ܻ���ħ���仯��Ϊ���Ǽ�����Ϊ���ǿ���
		SP_CHANGE = 3, // �ܻ���ŭ���仯��Ϊ���Ǽ�ŭ����Ϊ���ǿ�ŭ��
		UL_HP_CHANGE = 4, // �ܻ��ߵ�ǰѪ���ޱ仯��Ϊ���Ǽӣ�Ϊ���Ǽ�
		TARGET_RESULT = 5, // �ܻ��߽�����ͣ�ResultType��ö��ֵ����
		RETURN_HURT = 6, // �ܻ�����ɵķ���ֵ�����Ϊ0�����û�з���
		ATTACK_BACK = 7, // �ܻ�����ɵķ���ֵ�����Ϊ0�����û�з���
		STEAL_HP = 8, // ��������������Ѫֵ�����Ϊ0�����û����Ѫ
		ATTACKER_RESULT = 9, // �����߽�����ͣ�ResultType��ö��ֵ����
		PROTECTER_ID = 10, // ������ID
		PROTECTER_HP_CHANGE = 11, // ������Ѫ���仯��Ϊ���Ǽ�Ѫ��Ϊ���ǿ�Ѫ����Ȼ��Ϊ���ģ�
		PROTECTER_RESULT = 12, // �����߽�����ͣ�ResultType��ö��ֵ����
		ASSISTER_ID = 13, // �ϻ���ID
		STEAL_MP = 14, // ����������������ֵ�����Ϊ0�����û������
		RETURN_HURT_DEATH = 15, // ��������Ϊ�����˻򷴻��������������˵ı仯
		PROTECTER_MAXHP_CHANGE = 16, // ��������Ϊ�����������������˵ı仯
		MESSAGE_ID = 17, // �ж�ʱ������ʾID
		HP_GODBLESS = 18, // ����Ѫ���仯
		EP_CHANGE = 19, // �ܻ���Ч����仯��Ϊ���Ǽ�Ч���㣬Ϊ���ǿ�Ч����
		SHAPE_CHANGE = 20, // ģ�͸ı�
	};

	int resulttype; // ������� 0��ͨ 1���� 2���� 3׷�� 4���� 5ս������ 6������
	int targetid; // Ŀ��id��������
	int flagtype; // �������ṩ�ͻ��˱�ʾ
	std::list<fire::pb::battle::DemoBuff> demobuffs; // ÿһ��demo��buff�仯
	std::list<fire::pb::battle::DemoAttr> demoattrs; // ÿһ��demo����������ֵ
	std::map<int, int> datas; // �洢���ݣ�key�ο�����ֵ����datas��ĳkeyֵû����valueĬ��Ϊ0

	NewDemoResult() {
		resulttype = 0;
		targetid = 0;
		flagtype = 0;
	}

	NewDemoResult(int _resulttype_, int _targetid_, int _flagtype_, const std::list<fire::pb::battle::DemoBuff> & _demobuffs_, const std::list<fire::pb::battle::DemoAttr> & _demoattrs_, const std::map<int, int> & _datas_)
		: resulttype(_resulttype_), targetid(_targetid_), flagtype(_flagtype_), demobuffs(_demobuffs_), demoattrs(_demoattrs_), datas(_datas_) {
	}

	bool _validator_() const {
		for (std::list<fire::pb::battle::DemoBuff>::const_iterator _i_ = demobuffs.begin(); _i_ != demobuffs.end(); ++_i_)
			if (!_i_->_validator_()) return false;
		for (std::list<fire::pb::battle::DemoAttr>::const_iterator _i_ = demoattrs.begin(); _i_ != demoattrs.end(); ++_i_)
			if (!_i_->_validator_()) return false;
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << resulttype;
		_os_ << targetid;
		_os_ << flagtype;
		_os_ << FireNet::MarshalContainer(demobuffs);
		_os_ << FireNet::MarshalContainer(demoattrs);
		_os_ << FireNet::MarshalContainer(datas);
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> resulttype;
		_os_ >> targetid;
		_os_ >> flagtype;
		_os_ >> FireNet::MarshalContainer(demobuffs);
		_os_ >> FireNet::MarshalContainer(demoattrs);
		_os_ >> FireNet::MarshalContainer(datas);
		return _os_;
	}

};

} 
} 
} 
