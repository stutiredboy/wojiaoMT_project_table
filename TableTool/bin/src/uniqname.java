
import java.io.*;
import java.util.*;

public class uniqname {
	private static void usage(String err) {
		if (null != err)
			System.out.println(err);
		System.out.println("Usage: java -cp . uniqname installdir [-c]");
		System.out.println("	-c            chdir to installdir");
		System.exit(1);
	}

	public static boolean isFileAndExists(File file) {
		return file.exists() && file.isFile();
	}

	public static boolean isSnailbin(File dir) {
		return dir.isDirectory()
			&& isFileAndExists(new File(dir, "uniqname.jar"))
			&& isFileAndExists(new File(dir, "xdb.jar"))
			&& isFileAndExists(new File(dir, "jio.jar"))
			&& isFileAndExists(new File("uniqname.xdb.xml"))
			&& isFileAndExists(new File("uniqname.install.xml"))
			;
	}

	public static void main(String args[]) throws IOException {
		boolean chdir = false;
		String installdirArg = null;
		for (int i = 0; i < args.length; ++i) {
			if (args[i].equals("-c")) chdir = true;
			else if (null == installdirArg) installdirArg = args[i];
			else
				usage("ERROR: too many installdir");
		}

		if (installdirArg == null)
			usage("ERROR: no installdir");

		File currentdir = new File(".");
		if (!isSnailbin(currentdir)) usage("ERROR: please run this program in snail/bin");
		File installdir = new File(args[0]);
		//if (installdir.exists()) usage("ERROR: installdir exists.");
		if (installdir.isFile()) usage("ERROR: installdir is file.");
		install(installdir, relatedir(installdir, currentdir).toString());
		if (chdir) {
			System.err.println("chdir not implement");
		}
	}

	public static void install(File installdir, String snaildir) throws IOException {
		installdir.mkdirs();

		copyIfNotExist("uniqname.xdb.xml", installdir);
		System.setProperty("line.separator", "\n");

		PrintStream ps = new PrintStream(
				new FileOutputStream(new File(installdir, "build.xml")),
				false, "utf8");
		ps.println("");
		ps.println("<project name=\"uniqname\" default=\"uniqname\">");
		ps.println("");
		ps.println("  <property name=\"snail.bin\" value=" + quote(snaildir) + "/>");
		ps.println("");
		ps.println("  <target name=\"uniqname\">");
		ps.println("    <copy file=\"${snail.bin}/uniqname.install.xml\" todir=\".\"/>");
		ps.println("    <ant antfile=\"uniqname.install.xml\" target=\"install\">");
		ps.println("        <property name=\"output.dir\" value=\".\"/>");
		ps.println("        <property name=\"snail.bin\" value=\"${snail.bin}\"/>");
		ps.println("        <property name=\"xdb.xml\" value=\"uniqname.xdb.xml\"/>");
		ps.println("    </ant>");
		ps.println("    <delete file=\"uniqname.install.xml\"/>");
		ps.println("  </target>");
		ps.println("");
		ps.println("</project>");

		ps.close();
	}

	public static String quote(String s) {
		return "\"" + s + "\"";
	}

	public static void copyIfNotExist(String src, File destDir) throws IOException {
		File dest = new File(destDir, src);
		if (false == dest.exists()) {
			System.out.println("copy " + src + " " + dest);
			InputStream is = new FileInputStream(src);
			try {
				OutputStream os = new FileOutputStream(dest);
				try {
					byte [] buffer = new byte[4096];
					int rc = 0;
					while ((rc = is.read(buffer)) > 0)
						os.write(buffer, 0, rc);
				} finally {
					os.close();
				}
			} finally {
				is.close();
			}
		}
	}

	@SuppressWarnings("unused")
	public static File relatedir(File from, File to) throws IOException {
		Deque<File> froms = new LinkedList<File>();
		for (File p = from.getCanonicalFile(); p != null; p = p.getParentFile())
			froms.addFirst(p);

		Deque<File> tos = new LinkedList<File>();
		for (File p = to.getCanonicalFile(); p != null; p = p.getParentFile())
			tos.addFirst(p);

		while (!froms.isEmpty() && !tos.isEmpty() && froms.getFirst().equals(tos.getFirst())) {
			froms.removeFirst();
			tos.removeFirst();
		}
//		System.out.println("from=" + froms); System.out.println("tos=" + tos);

		File relate = null;
		for (File unused : froms) {
			relate = null == relate ? new File("..") : new File(relate, "..");
		}
		for (File tof : tos) {
			relate = null == relate ? new File(tof.getName()) : new File(relate, tof.getName());
		}
		return null == relate ? new File(".") : relate;
	}
}