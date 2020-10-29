
#pragma once

#include "rpcgen.hpp"
#include "gnet/PortForward.hpp"
#include "pfio.hpp"

namespace portforward
{

	/*
	����ת����
	�������ƣ�
	�������ӣ�
	�������
	*/
	class Forward
	{
	public:
		Forward( int sid, int accid, int lid);
		~Forward();

		int  getPortsid() const          { return this->portsid; }
		long getAcceptorId() const       { return this->acceptorid; }

		///////////////////////////////////////////////////////////
		// PortForward �����������
		void ForwardData(const GNET::Octets & data);
		void ForwardAck(long ackedSize);

		std::string str() const;

	private:
		int 	linkid;
		int  	portsid;    // �˿�ת�����
		int 	acceptorid; // ���ؼ������

		// ��������
		int windowSize;   // δ��ȷ�ϵ�ת������
		int forwardSize;  // :recv ��ת��������������see OnRecv
		int sendSize;     // ::send ��ȥ������������

		GNET::Octets buffer;
		PortForwardIO * io;

		friend class PortForwardIO;

		// ��������ʱ�׳��쳣
		int send(const GNET::Octets & data);

		// IO events
		void OnIORecv( GNET::Octets& data);
		void OnIOSend();
		void OnIODestroy();

		// ��ֹ����
		Forward(const Forward&);
		void operator=(const Forward&);
	};

	class Forwards //: public aio::ASocketFactory
	{
		typedef std::map<int, Forward *> forwards_t;
		forwards_t forwards; // portsid -> Forward

		typedef std::map<int, LocalAcceptor *> acceptor_t;
		acceptor_t acceptor; // acid -> LocalAcceptor

		int 		m_linkclientid;
	public:
		~Forwards();

		void SetLinkClientID( int id)
		{
			m_linkclientid = id;
		}
		int GetLinkClientID() const
		{
			return m_linkclientid;
		}

		// ����
		// �½�����ת���˿�
		bool cmdNewLocal( const std::string& servername, const std::string& host, int port, const std::string& rhost, const std::string& rport);
		// �رձ��ؼ�����closePorts �Ƿ�һ��ر���������ӳ�䡣
		void cmdCloseLocal( int acceptorid, bool closePorts);
		void cmdCloseForward(int portsid, int reason); // �ر�ĳ��ӳ�䲢�ҷ���Э���Զ�ˡ�
		void cmdPrintLocal();              // ��ӡ���ж˿�ӳ����Ϣ��

		void cmdCloseAll();

		// Э��
		void process(const gnet::PortForward & pf);

		LocalAcceptor* GetLocalAcceptor( int accid)
		{
			acceptor_t::const_iterator it = acceptor.find( accid);
			if( it == acceptor.end())
				return NULL;
			else
				return it->second;
		}

		LocalAcceptor* RemoveLocalAcceptor( int accid)
		{
			acceptor_t::iterator it = acceptor.find( accid);
			if( it == acceptor.end())
				return NULL;
			LocalAcceptor* la = it->second;
			acceptor.erase( it);
			return la;
		}


		// Forward ����
		Forward * newForward(int portsid, int acceptorid)
		{
			std::pair<forwards_t::iterator, bool> ii = forwards.insert(std::make_pair(portsid, (Forward*)NULL));
			if (ii.second)
				ii.first->second = new Forward( portsid, acceptorid, m_linkclientid);
			return ii.first->second;
		}

		Forward * findForward(int portsid)
		{
			forwards_t::iterator it = forwards.find(portsid);
			if (it != forwards.end())
				return it->second;
			return NULL;
		}

		Forward * removeForward(int portsid)
		{
			Forward * tmp = NULL;
			forwards_t::iterator it = forwards.find(portsid);
			if (it != forwards.end())
			{
				tmp = it->second;
				forwards.erase(it);
			}
			return tmp;
		}

		void RemoveAcceptorSID( int accid, int sid)
		{
			if( LocalAcceptor* la = GetLocalAcceptor( accid))
				la->portsids.erase( sid);
		}
	};


} // namespace portforward

