
#pragma once


namespace fire { 
namespace pb { 

class LogPriority : public FireNet::Marshal
{
public:
	enum {
		LOG_FORMAT = 15, // �����Ϊ��׼����־���磺�˺ŵ�½����ֵ��������ء�
		LOG_STAT = 16, // ÿ5���Ӽ�¼�ʼ���������Ǯ�޸�������Ʒ�޸����ȡ�
		LOG_GM = 17, // ��¼GM������log
		LOG_MONEY = 18, // ��¼��Ǯ�Ĳ�������������ԭ��
		LOG_CHAR2 = 19, // �����¼����¼����BASE64�����¼��
		LOG_COUNTER = 20, // ÿ5���Ӽ�¼�ʼ���������Ǯ�޸�������Ʒ�޸����ȡ�
		LOG_XINGCHENG = 21, // �����ϸ��Ϊ��־���磺�ƶ�����֣���ӣ�ʰȡ�ȡ�
		LOG_TRADE = 22, // ÿ���̳����ļ�¼��
		LOG_FUSHI = 23, // �ۼƼ�¼��ҳ�ֵ�����������ķ�ʯ������
	};

	LogPriority() {
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

	bool operator<(const LogPriority &_o_) const {
		return compareTo(_o_) < 0;
	}

	int compareTo(const LogPriority &_o_) const {
		if (&_o_ == this) return 0;
		int _c_ = 0;
		return _c_;
	}

};

} 
} 
