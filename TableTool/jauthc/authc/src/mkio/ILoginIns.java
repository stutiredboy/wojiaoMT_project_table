/**
 * 
 */
package mkio;

/**
 *
 */
public interface ILoginIns 
{
		public	class Param extends Object
		{
			// �������
			public String host;
			public String address;
			public String port;

			// ��½��֤����
			public String username;
			public String password;
			public boolean  isCheckVersion;
			public int      version;
			public boolean  iskickuser; // �Ƿ�ǿ�Ƶ�½��
			public int		logintype;  //��¼���� 0:normal login  1:auany login
			public String	mid;//�˺ŵ�ý���ʶ��Ĭ��Ϊlocojoy
			public int		reserved1;//�����ֶ�1
			public String 	reserved2;//�����ֶ�2
			public Param()
			{
				version = 0;
				isCheckVersion = false;
				iskickuser = false;
				logintype = 0;
				mid = "locojoy";
				reserved1 = 0;
				reserved2 = "";
			}
			public Param( Param pa )
			{
				this.host = pa.host;
				this.address = pa.address;
				this.port = pa.port;
				this.username = pa.username;
				this.password = pa.password;
				this.isCheckVersion = pa.isCheckVersion;
				this.version = pa.version;
				this.iskickuser = pa.iskickuser;
				this.logintype = pa.logintype;
				this.mid = pa.mid;
				this.reserved1 = pa.reserved1;
				this.reserved2 = pa.reserved2;
			}
			
			public void set(Param pa)
			{
				this.host = pa.host;
				this.address = pa.address;
				this.port = pa.port;
				this.username = pa.username;
				this.password = pa.password;
				this.isCheckVersion = pa.isCheckVersion;
				this.version = pa.version;
				this.iskickuser = pa.iskickuser;
				this.logintype = pa.logintype;
				this.mid = pa.mid;
				this.reserved1 = pa.reserved1;
				this.reserved2 = pa.reserved2;
			}
		};
		
		void start();
		
		public void start(int inputBufferSize, int outputBufferSize, 
				int receiveBufferSize, int sendBufferSize);
		
		void close();
		
		void sendMatrixCardResponse(int[] v);
		
		void sendHandSetResponse(int num);

		void instantAddCash(String cardnum, String cardpasswd);

		boolean send(mkio.Protocol p);

		mkio.Connector getConnector();
		
		mkio.Mkio getMkio();
		// ������
		public class Addiction
		{
			public enum Rate
			{
				eRate100, // ������Ϸ��100%���档
				eRate50,  // ����״̬��50%���档
				eRate0    // ����״̬��0%���档
			};
			int rate;        // ��ǰ�����ĳ���״̬��
			int msg;         // δ�á�
			int timeplay;    // �Ѿ����ߵ�ʱ�䡣
			java.util.Date time50;   // ����50%�����ʱ�䡣���rate�Ѿ���50%���飬��ô���ʱ��㽫С�ڵ�ǰʱ�䡣
			java.util.Date time0;    // ����0%�����ʱ�䡣���rate�Ѿ���0%���飬��ô���ʱ��㽫С�ڵ�ǰʱ�䡣

			Addiction() 
			{ 
				rate = 0; msg = 0; timeplay = 0; 
				time50 = new java.util.Date(); 
				time0 = new java.util.Date(); 
			}
		};
		boolean getAddiction(Addiction adict);

		//��������Ϣ
		public class ServerInfo 
		{
			public enum Award
			{
				eDoubleExp,	//˫������
				eDoubleMoney, //˫����Ǯ
				eDoubleDrop,	//˫������
				eDoubleSp,	//˫�����ܵ�
			};
			int flags; //��ǰ������״̬���������г���״̬��
			char load; //��ǰ���������� 1-green 2-yellow 3-red

			
			java.util.Map<Integer, Integer> extra;

			ServerInfo() 
			{
				flags = 0; load = 0;
			}
		};

		boolean getServerInfo(ServerInfo info); // onAuthError(eServerAttr, ...) �Ժ���Ϣ��׼�����ˡ�
		int getServerVersion(); // �� getServerInfo ͬ����ʱ�����á�

		public enum Algorithm
		{
			ALGORITHM_NONE, //        =  0x0, //ֻ������
			ALGORITHM_PHONE, //		  =  0x00000100,//�绰�ܱ�
			ALGORITHM_CARD, //        =  0x00010000,//����+�ܱ���
			ALGORITHM_HANDSET, //     =  0x00020000,//����+�ֻ��ܱ�
			ALGORITHM_USBKEY, //      =  0x00030000,//usbkey����ܱ���

			ALGORITHM_NEED_MODIFY_PASSWD, // = 0x00000200,//��Ҫ��ʾ��������
			ALGORITHM_NEED_MODIFY_MATRIX, // = 0x00000400,//��Ҫ��ʾ�����ܱ���

		};
		//if(getSecureLevel() & ALGORITHM_NEED_MODIFY_PASSWD == ALGORITHM_NEED_MODIFY_PASSWD) ����ʾ��������
		//if(getSecureLevel() & ALGORITHM_NEED_MODIFY_MATRIX == ALGORITHM_NEED_MODIFY_PASSWD) ����ʾ�����ܱ���
		Algorithm getSecureLevel(); //��ȡ�ʺŵ��ܱ��ȼ�  

		// ���ص�ǰ���ӵ�ping���ڲ���ʱ��顣
		int getServerPing();

		// ���ñ���������λ���롣Ĭ��ֵΪ5000��
		//   �����СֵΪ1000���ڲ�ʵ��ʱ����̫С�ļ����
		//   �� period <= 0     ֹͣ����͡�ͬʱֹͣ��� ServerPing��
		void setupKeepAlive(int period);

		// ��½�ɹ������ص�ǰ�������ĵ�ַ��
		String getHostAddress();

		boolean isCanEnterWorld();
		//public aio::Protocol::Manager::Session::ID GetSessionID() = 0;
		
		public ILoginUI getLoginUI();
		
		public Param getParam();
}
