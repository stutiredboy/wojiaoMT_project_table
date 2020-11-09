
#pragma once

#include "fire/pb/battle/DemoAttr.hpp"
#include "fire/pb/battle/DemoBuff.hpp"
#include <list>

namespace fire { 
namespace pb { 
namespace battle { 

class DemoResult : public FireNet::Marshal
{
public:
	int resulttype; // ������� 0��ͨ 1���� 2���� 3׷�� 4���� 5ս������ 6������
	int targetid; // �ܻ���id
	int flagtype; // �������ṩ�ͻ��˱�ʾ
	int hpchange; // �ܻ���Ѫ���仯��Ϊ���Ǽ�Ѫ��Ϊ���ǿ�Ѫ
	int mpchange; // �ܻ���ħ���仯��Ϊ���Ǽ�����Ϊ���ǿ���
	int spchange; // �ܻ���ŭ���仯��Ϊ���Ǽ�ŭ����Ϊ���ǿ�ŭ��
	int epchange; // �ܻ���Ч����仯��Ϊ���Ǽ�Ч���㣬Ϊ���ǿ�Ч����
	int shapechange; // ģ�͸ı� 0ΪĬ������Ϊ�����õġ�
	int uplimithpchange; // �ܻ��ߵ�ǰѪ���ޱ仯��Ϊ���Ǽӣ�Ϊ���Ǽ�
	int targetresult; // �ܻ��߽�����ͣ�ResultType��ö��ֵ����
	int returnhurt; // �ܻ�����ɵķ���ֵ�����Ϊ0�����û�з���
	int attackback; // �ܻ�����ɵķ���ֵ�����Ϊ0�����û�з���
	int stealhp; // ��������������Ѫֵ�����Ϊ0�����û����Ѫ
	int attackerresult; // �����߽�����ͣ�ResultType��ö��ֵ����
	int attackerulhpchange; // ������Ѫ���ޱ仯
	int protecterid; // ������ID
	int protecterhpchange; // ������Ѫ���仯��Ϊ���Ǽ�Ѫ��Ϊ���ǿ�Ѫ����Ȼ��Ϊ���ģ�
	int protecterulhpchange; // ������Ѫ���ޱ仯
	int protecterresult; // �����߽�����ͣ�ResultType��ö��ֵ����
	int assisterid; // �ϻ���ID
	int stealmp; // ����������������ֵ�����Ϊ0�����û������
	int godblesshp; // ����Ѫ���仯
	std::list<fire::pb::battle::DemoBuff> demobuffs; // ÿһ��demo��buff�仯
	std::list<fire::pb::battle::DemoAttr> demoattrs; // ÿһ��demo����������ֵ

	DemoResult() {
		resulttype = 0;
		targetid = 0;
		flagtype = 0;
		hpchange = 0;
		mpchange = 0;
		spchange = 0;
		epchange = 0;
		shapechange = 0;
		uplimithpchange = 0;
		targetresult = 0;
		returnhurt = 0;
		attackback = 0;
		stealhp = 0;
		attackerresult = 0;
		attackerulhpchange = 0;
		protecterid = 0;
		protecterhpchange = 0;
		protecterulhpchange = 0;
		protecterresult = 0;
		assisterid = 0;
		stealmp = 0;
		godblesshp = 0;
	}

	DemoResult(int _resulttype_, int _targetid_, int _flagtype_, int _hpchange_, int _mpchange_, int _spchange_, int _epchange_, int _shapechange_, int _uplimithpchange_, int _targetresult_, int _returnhurt_, int _attackback_, int _stealhp_, int _attackerresult_, int _attackerulhpchange_, int _protecterid_, int _protecterhpchange_, int _protecterulhpchange_, int _protecterresult_, int _assisterid_, int _stealmp_, int _godblesshp_, const std::list<fire::pb::battle::DemoBuff> & _demobuffs_, const std::list<fire::pb::battle::DemoAttr> & _demoattrs_)
		: resulttype(_resulttype_), targetid(_targetid_), flagtype(_flagtype_), hpchange(_hpchange_), mpchange(_mpchange_), spchange(_spchange_), epchange(_epchange_), shapechange(_shapechange_), uplimithpchange(_uplimithpchange_), targetresult(_targetresult_), returnhurt(_returnhurt_), attackback(_attackback_), stealhp(_stealhp_), attackerresult(_attackerresult_), attackerulhpchange(_attackerulhpchange_), protecterid(_protecterid_), protecterhpchange(_protecterhpchange_), protecterulhpchange(_protecterulhpchange_), protecterresult(_protecterresult_), assisterid(_assisterid_), stealmp(_stealmp_), godblesshp(_godblesshp_), demobuffs(_demobuffs_), demoattrs(_demoattrs_) {
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
		_os_ << hpchange;
		_os_ << mpchange;
		_os_ << spchange;
		_os_ << epchange;
		_os_ << shapechange;
		_os_ << uplimithpchange;
		_os_ << targetresult;
		_os_ << returnhurt;
		_os_ << attackback;
		_os_ << stealhp;
		_os_ << attackerresult;
		_os_ << attackerulhpchange;
		_os_ << protecterid;
		_os_ << protecterhpchange;
		_os_ << protecterulhpchange;
		_os_ << protecterresult;
		_os_ << assisterid;
		_os_ << stealmp;
		_os_ << godblesshp;
		_os_ << FireNet::MarshalContainer(demobuffs);
		_os_ << FireNet::MarshalContainer(demoattrs);
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> resulttype;
		_os_ >> targetid;
		_os_ >> flagtype;
		_os_ >> hpchange;
		_os_ >> mpchange;
		_os_ >> spchange;
		_os_ >> epchange;
		_os_ >> shapechange;
		_os_ >> uplimithpchange;
		_os_ >> targetresult;
		_os_ >> returnhurt;
		_os_ >> attackback;
		_os_ >> stealhp;
		_os_ >> attackerresult;
		_os_ >> attackerulhpchange;
		_os_ >> protecterid;
		_os_ >> protecterhpchange;
		_os_ >> protecterulhpchange;
		_os_ >> protecterresult;
		_os_ >> assisterid;
		_os_ >> stealmp;
		_os_ >> godblesshp;
		_os_ >> FireNet::MarshalContainer(demobuffs);
		_os_ >> FireNet::MarshalContainer(demoattrs);
		return _os_;
	}

};

} 
} 
} 
