
#pragma once


namespace fire { 
namespace pb { 
namespace npc { 

class ImpExamAssistType : public FireNet::Marshal
{
public:
	enum {
		NOASSIST = 0, // ��ʹ��Э��
		DELWRONG = 1, // ɾ��һ�������
		CHORIGHT = 2, // ֱ��ѡ����ȷ��
	};

	ImpExamAssistType() {
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

	bool operator<(const ImpExamAssistType &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const ImpExamAssistType &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
} 
