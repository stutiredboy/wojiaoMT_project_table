package mkio;

import java.io.File;

/**
 * 	������Ϣ��ȡ��������Ӧ��xio.xml�ļ������ɵ�xio.xml�в���Ҫauthc��ص�Э��
 * 	������⣺
 * 	1. Jauthc��xdb�޹أ�ֻ��xio�йأ�������еĸ�xdb���ݿ⣬�̳߳���صģ���������
 * 	k
 */
public class JAuthc 
{
	public static final String DefaultXioXML = "../jauthc/test.xio.xml";
	public static final String DefaultLibPath = ".";

	public static final String LibSecX86 = "sec_x86.dll";
	public static final String LibSecAmd64 = "libsec_amd64.so";
	
	public static void start()
	{
		start(DefaultXioXML, DefaultLibPath);
	}
	
	public static void start(String xioxml)
	{
		start(xioxml, DefaultLibPath);
	}
	
	public static void close()
	{
		LoginManager.getInstance().closeAll();
		mkio.Engine.getInstance().close();
	}
	/**
	 * 
	 * @param xioxml: xio��ص�Э������
	 * @param libpath: sec������������·��
	 */
	public static void start(String xioxml, String libpath)
	{	
		String seclibname = 
			System.getProperty("os.name").contains("Win") ?  "sec_amd64.dll" : "libsec_amd64.so";
		mkdb.util.Dbx.load(new File(libpath), null, seclibname);	
		mkio.Engine.getInstance().open();		
		try 
		{
			mkio.MkioConf.loadAndRegister(xioxml);
		} catch (Exception e1) 
		{
			e1.printStackTrace();
		}	
	}
	
	/** Jauthc��TraceDebug��ʱ����mkdb.Trace�������ڴ�mkdb.trace��ʱ��Ҳ�����Ӧ��trace
	 * 
	 */
	public static void openTraceDebug()
	{
		mkdb.Trace.openIf();
		mkdb.Trace.set(mkdb.Trace.DEBUG);
	}
	
	public static void closeTraceDebug()
	{
		mkdb.Trace.close();
	}
	
	public static LoginManager getLoginManager()
	{
		return LoginManager.getInstance();
	}
}
