
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class pf {
	/**
	 * <ul>
	 * <li> 不能更改现有的端口顺序。
	 * <li> 增加端口时，只能在后面添加。
	 * <li> 最多只支持16个端口。
	 * <li> glinkd 需要解析这些映射， 为了避免更新时同步，把16个端口都分配好。
	 * </ul>
	 */
	private static int [] wellKnownPorts = new int[] {
			1098, 1099, 2098, 2099, /* jmx */ 22, /* ssh */ 80, 443, 8080, 3128, 8443, /* http */
			512, 513, 514, 23, /* rexec rlogin rsh telnet */ 873, /* rsync */ 1194,  /* openvpn */
			};

	{
		if (wellKnownPorts.length > 16)
			throw new RuntimeException("too many well known ports.");
	}

	static int port2index(int port) {
		for (int index = 0; index < wellKnownPorts.length; ++index)
			if (wellKnownPorts[index] == port)
				return index;
		return -1;
	}

	static int index2port(int index) {
		//if (index < 0 || index >= ports.length)
		//	throw new IllegalArgumentException();
		return wellKnownPorts[index];
	}

	static void decode(String qport, List<Integer> result) {
		int iport = Integer.parseInt(qport, 16);

		// 紧凑模式最多只支持16个端口。
		if (0 != (iport & 0xffff0000))
			throw new IllegalArgumentException("too many compact ports. qport=" + qport);

		for (int index = 0; index < 16; ++index) {
			int bit = 1 << index;
			if ((iport & bit) != 0)
				result.add(index2port(index));
		}
	}

	static String encode(List<Integer> ports) {
		StringBuilder sb = new StringBuilder();
		int iports = 0;
		for (Integer port : ports) {
			int index = port2index(port);
			if (index >= 0) {
				// compact
				int bit = 1 << index;
				iports |= bit;
				continue;
			}

			sb.append("p").append(port);
		}
		if (0 != iports)
			sb.append("q").append(Integer.toHexString(iports));
		return sb.toString();
	}

	///////////////////////////////////////////////////////////////////////
	// 
	private Integer aid;
	private Integer zoneid;
	private boolean grantable;
	private List<Integer> ports = new ArrayList<Integer>();
	private String username;

	public void setFinished() {
		if (null == username)
			throw new RuntimeException("username is null.");
		Integer [] _ports = ports.toArray(new Integer[ports.size()]);
		Arrays.sort(_ports);
		ports = Arrays.asList(_ports);
	}

	pf () {	
		grantable = false;
	}

	pf(String sacc) {
		this.set(sacc);
		setFinished();
	}

	private void setAid(String aid) {
		if (null != this.aid)
			throw new RuntimeException("too many aid.");
		this.aid = Integer.valueOf(aid);
	}

	private void setZoneid(String zoneid) {
		if (null != this.zoneid)
			throw new RuntimeException("too many zoneid.");
		this.zoneid = Integer.valueOf(zoneid);
	}

	private void setUserName(String username) {
		if (null != this.username)
			throw new RuntimeException("too many username.");
		this.username = username;
	}
	
	private void addPort(String port) {
		Integer i = Integer.valueOf(port);
		if (i < 0 || i > 0xffff)
			throw new RuntimeException("Invalid Port. port=" + port);
		this.ports.add(i);
	}

	private void setGrant(String piece) {
		if (!piece.isEmpty())
			throw new IllegalArgumentException("'g' has no argument: " + piece);
		grantable = true;
	}

	public String encode() {
		if (null != aid && null != zoneid)
			println("--WARNING: aid or zoneid.");
		StringBuilder sb = new StringBuilder(); 
		if (this.grantable) sb.append("g");
		if (null != aid)    sb.append("a").append(aid);
		if (null != zoneid) sb.append("z").append(zoneid);
		sb.append(pf.encode(ports));
		sb.append("u").append(username);
		return sb.toString();
	}

	private void setPiece(String piece) {
		switch (piece.charAt(0)) {
		case 'a': this.setAid(piece.substring(1)); break;
		case 'z': this.setZoneid(piece.substring(1)); break;
		case 'p': this.addPort(piece.substring(1)); break;
		case 'q': pf.decode(piece.substring(1), this.ports); break;
		case 'u': this.setUserName(piece.substring(1)); break;
		case 'g': this.setGrant(piece.substring(1)); break;
		default:  throw new IllegalArgumentException("Unknown prefix! value=" + piece);
		}
	}

	public void set(String sacc) {
		int startpos = -1;
		for (int i = 0; i < sacc.length(); ++i) {
			char c = sacc.charAt(i);
			switch (c) {
			case 'a': case 'z': case 'p': case 'q': case 'g': case 'u':
				if (startpos >= 0)
					this.setPiece(sacc.substring(startpos, i));
				startpos = i;
				break;
			}
			if ('u' == c) // last piece
				break;
		}
		if (startpos == -1)
			throw new IllegalArgumentException("Invalid Format! str=" + sacc);
		if (startpos < sacc.length())
			setPiece(sacc.substring(startpos));
	}

	public String toString() {
		return "aid=" + aid + " zoneid=" + zoneid + " ports=" + ports + " user=" + username;
	}

	/**
	 * 
	 * @param args
	 */
	public static void main(String args[]) {
		if (args.length < 1)
			printUsageAndExit();

		if (args[0].equals("-d")) {
			for (int i = 1; i < args.length; ++i)
				println(new pf(args[i]));
			return;
		}

		pf acc = new pf();
		try {
			for (int i = 0; i < args.length; ++i)
				acc.set(args[i]);
			acc.setFinished();
		} catch (Exception ex) {
			ex.printStackTrace();
			printUsageAndExit();
		}
		println(acc);
		String sacc = acc.encode();
		if (sacc.length() > 16)
			println("--WARNING: account too long.");
		println(sacc);
	}

	private static void printUsageAndExit() {
		println("Usage:");
		println("  java pf [g] [aAID] [zZONEID] [[pPORT] [pPORT]...] uUSERNAME");
		println("          create acount.");
		println("  java pf -d account...");
		println("          decode account.");
		System.exit(0);
	}

	private static void println(Object obj) {
		System.out.println(obj);
	}
}
