
#pragma once


namespace fire { 
namespace pb { 
namespace battle { 

class AIOperation : public FireNet::Marshal
{
public:
	int actionseq; // ��һ�غϵĽű��У��ڼ���ResultItem
	int actionmoment; // -1:�������ж�ǰ��0���������ж���;1-28����ӦID��ս��������ʱ
	int actionfighterid; // ��������ս����
	int actionid; // ��Ҫ����AIAction ID

	AIOperation() {
		actionseq = 0;
		actionmoment = 0;
		actionfighterid = 0;
		actionid = 0;
	}

	AIOperation(int _actionseq_, int _actionmoment_, int _actionfighterid_, int _actionid_)
		: actionseq(_actionseq_), actionmoment(_actionmoment_), actionfighterid(_actionfighterid_), actionid(_actionid_) {
	}

	bool _validator_() const {
		return true;
	}

	FireNet::Marshal::OctetsStream & marshal(FireNet::Marshal::OctetsStream & _os_) const {
		_os_ << actionseq;
		_os_ << actionmoment;
		_os_ << actionfighterid;
		_os_ << actionid;
		return _os_;
	}

	const FireNet::Marshal::OctetsStream & unmarshal(const FireNet::Marshal::OctetsStream & _os_) {
		_os_ >> actionseq;
		_os_ >> actionmoment;
		_os_ >> actionfighterid;
		_os_ >> actionid;
		return _os_;
	}

	bool operator<(const AIOperation &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const AIOperation &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		_c_ = actionseq - _o_.actionseq;
		if (0 != _c_) return _c_;
		_c_ = actionmoment - _o_.actionmoment;
		if (0 != _c_) return _c_;
		_c_ = actionfighterid - _o_.actionfighterid;
		if (0 != _c_) return _c_;
		_c_ = actionid - _o_.actionid;
		if (0 != _c_) return _c_;
		return _c_;
	}

};

} 
} 
} 
