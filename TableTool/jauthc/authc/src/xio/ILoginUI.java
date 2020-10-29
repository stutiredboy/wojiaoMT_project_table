/**
 * 
 */
package xio;

/**
 *
 */
public interface ILoginUI 
{
	
		public enum Action
		{
			eConnect, // ���ӷ���������
			eServer,  // �������ڲ������յ�gnet::ErrorInfoЭ��
			eNet,     // ����������ӽ����Ժ��շ�����
			eTimeout, // ��ʱ����
			eVersion, // �汾��ƥ�䡣
			eProtocol, // Э�鴦�����
			eServerAttr, // newLogin ʱ���ṩ�û��ʺţ��õ���������Ϣ�Ժ��������ϻᱻ�رգ�������������״̬��
		};
	
		void onAuthHandSet(int num);
		void onAuthMatrixCard(int[] x, int[] y);
		void onAuthOk(int userid);

		void onAuthError(Action a, int e, String detail);

		void onAnnounceForbidInfo(char type, int time, int createtime, String reason);
		
		
		/************************************************************************/
		/* InstantAddCashRep��retcode�������£�
		0.�ɹ� 
		1.���Ų����� 
		2.�û������� 
		3.�Ʒ��������� 
		4.������� 
		5.�ÿ��ѹ��� 
		6.�涨ʱ����ͬһ�ſ���ֵ�������ޣ���ֹ�Գ�ֵ�����룩
		11.�û��ڸ÷��������������ڵȴ����������Ժ����� 
		12. �û����е㿨��ֵδ�����꣬���Ժ����� 
		13. �û�����������ܳ�ֵ 
		-1.��������
	    */
		/************************************************************************/
		void onInstantAddCashRep(int retcode, int userid, int reserved);

		void dispatch(xio.Manager manager, xio.Xio connection, xio.Protocol p);
		/*{
			mkdb.Xdb.executor().execute(p);
		}*/
}
