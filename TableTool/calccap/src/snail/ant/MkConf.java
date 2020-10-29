package snail.ant;

import org.apache.tools.ant.*;
import java.io.*;
import java.util.*;

/*
 * ����ʱ����Ҫ�� ant.jar �ӵ� Libraries �С�
 * eclipse ��װ·�����������, �磺
 * c:\eclipse\plugins\org.apache.ant_VERSION\lib\ant.jar
 */
public class MkConf extends Task {
	@Override
	public void execute() throws BuildException {
		try {
			String all = null;
			{
				InputStreamReader fr = new InputStreamReader(new FileInputStream(src), encoding);
				StringBuilder sb = new StringBuilder();
				char [] cbuf = new char[8192];
				int rc = -1;
				while ((rc = fr.read(cbuf)) != -1) { sb.append(cbuf, 0, rc); }
				fr.close();
				all = sb.toString();
			}
			for (Place p : places)
				all = all.replaceAll(p.getName(), p.getValue());
			{
				OutputStreamWriter fw = new OutputStreamWriter(new FileOutputStream(dest), encoding);
				fw.write(all.toCharArray());
				fw.close();
			}
		} catch (Exception ex) {
			throw new BuildException(ex);
		}
	}

	private String src;
	private String dest;
	private String encoding = "GBK";
	private Set<Place> places = new HashSet<Place>();

	public void addPlace(Place place) {
		places.add(place);
	}

	public String getSrc() {
		return src;
	}
	
	public void setSrc(String src) {
		this.src = src;
	}
	
	public String getDest() {
		return dest;
	}
	
	public void setDest(String dest) {
		this.dest = dest;
	}

	public String getEncoding() {
		return encoding;
	}

	public void setEncoding(String encoding) {
		this.encoding = encoding;
	}
}
