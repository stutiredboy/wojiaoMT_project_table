
#pragma once

#include "fire/pb/battle/DemoBuff.hpp"
#include <list>

namespace fire { 
namespace pb { 
namespace battle { 

class DemoExecute : public FireNet::Marshal
{
public:
	int attackerid; // ����������id
	int hpconsume; // �����ߺ�Ѫ��ʼ��Ϊ������
	int mpconsume; // �����ߺ�����ʼ��Ϊ������
	int spconsume; // �����ߺ�ŭ��ʼ��Ϊ������
	int operationtype; // �������� �ο�OperationType�е�ֵ		����ǲ���ʧ�� ACTION_FAILURE
	int operationid; // ������ֵ��ʹ����Ʒʱʾ��ƷID���л�����ʱΪ���
	int msgid; // ����Ϊ0ʱ��Ϊ����ʱ����ʾID
	std::list<fire::pb::battle::DemoBuff> demobuffs;

	DemoExecute() {
		attackerid = 0;
		hpconsume = 0;
		mpconsume = 0;
		spconsume = 0;
		operationtype = 0;
		operationid = 0;
		msgid = 0;
	}

	DemoExecute(int _attackerid_, int _hpconsume_, int _mpconsume_, int _spconsume_, int _operationtype_, int _operationid_, int _msgid_, const std::list<fire::pb::battle::DemoBuff> & _demobuffs_)
		: attackerid(_attackerid_), hpconsume(_hpconsume_), mpconsume(_mpconsume_), spconsume(_spconsume_), operationtype(_operationtype_), operationid(_operationid_), msgid(_msgid_), demobuffs(_demobuffs_) {
	}

	bool _validator_() const {
		for (std::list<fire::pb::battle::DemoBuff>::const_iterator _i_ = demobuffs.begin(); _i_ != demobuffs.end(); ++_i_)
			if (!_i_->_validator_()) return false;
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << attackerid;
		_os_ << hpconsume;
		_os_ << mpconsume;
		_os_ << spconsume;
		_os_ << operationtype;
		_os_ << operationid;
		_os_ << msgid;
		_os_ << FireNet::MarshalContainer(demobuffs);
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> attackerid;
		_os_ >> hpconsume;
		_os_ >> mpconsume;
		_os_ >> spconsume;
		_os_ >> operationtype;
		_os_ >> operationid;
		_os_ >> msgid;
		_os_ >> FireNet::MarshalContainer(demobuffs);
		return _os_;
	}

};

} 
} 
} 
