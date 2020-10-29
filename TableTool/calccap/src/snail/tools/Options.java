package snail.tools;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * ������ѡ��
 * 
 * sample
 	1 ����ѡ��
	String [][] _opts_ = {
	//	ѡ����       ֵ��      ��������            Ĭ��ֵ
		{"-input",  "file", "input file name",  null},           // ���Բ��ṩ������ֵΪnull��
		{"-output", "file", "output file name", "defaultValue"}, // ���Բ��ṩ����ΪĬ��ֵ��
		{"-mode",   "N",    "mode no.",         "!"},            // �����ṩ��
		{null,      null,   "help only",     null},           // ֻ�����������������
		{"-debug",  null,   "debug?",   null},                   // �޲���ֵ��
	};
		//////////////////////////////////////////
		// ����ֵ�����
		// ֵ��       ˵��                       Ĭ��ֵ
		// null      ����Ҫ����                  ���Դ����
		// valueName ��Ҫ��������Ϊ��������        null          ���Բ��ṩ����ֵ������ֵΪnull��
		//                                     !             ���벻�ṩ����ֵ��
		//                                     defaultValue  ���Բ��ṩ����ֵ����ΪĬ��ֵ��
		//
		// ע�⣺"��" ��������ʾ����ֵ�������ã������޷����������Ĭ��ֵ��

	2 ��ʼ��ѡ��
	Options opts = new Options(_opts_);

	3 ����������
	opts.parse(args);

	4 ʹ��
	opts.getValue("-input");
	opts.getValue("-output");
	opts.getValue("-debug") != null;

	5 ��ӡѡ��
	opts.printUsage("java -jar myjar"); // ����Ĳ���Ҳ������ MainClass �����֡�

	6 ��ӡ������ӣ���1�Ķ���
	Usage: java -jar myjar [options]
		-input  file  input file name
		-output file  output file name - default: defaultValue
		-mode   N     mode no.
		-debug        debug?
 *
 */
public class Options {
	private Map<String, Option> options = new HashMap<String, Option>();
	private List<String> tokens = new LinkedList<String>(); // ������˳�򱣴治��ѡ��Ĳ�����
	private List<Option> ordered = new ArrayList<Option>();  // ������˳�����������
	private int maxOptionNameLength = 0;
	private int maxValueNameLength = 0;

	public Options() {
	}

	public Options(String [][] options) {
		this.add(options);
	}

	public void add(String [][] options) {
		for (String[] option : options)
			this.add(option);
	}

	public void add(String[] option) {
		this.add(new Option(option));
	}

	public void add(Option option) {
		if (option.getName() != null && null != options.put(option.getName(), option))
			throw new RuntimeException(option + " : duplicate name");
		ordered.add(option);
		if (option.getName() != null && option.getName().length() > maxOptionNameLength)
			maxOptionNameLength = option.getName().length();
		if (option.getValueName() != null && option.getValueName().length() > maxValueNameLength)
			maxValueNameLength = option.getValueName().length();
	}

	public void parse(String [] args) {
		parse(args, 0);
	}

	public void parse(String [] args, int offset) {
		Option last = null;
		for (int i = offset; i < args.length; ++i) {
			String arg = args[i];
			if (Option.isOption(arg)) {
				last = options.get(arg);
				if (null == last)
					throw new IllegalArgumentException(arg + " : unknown option");
				last.setPresent();
			} else if (null != last) {
				last.setValue(arg);
				last = null; // a option has one value
			} else {
				tokens.add(arg);
			}
		}

		// verify ��֤��Ҫ�Ĳ��������ṩ��
		for (Option option : options.values())
			if (option.hasValue())
				option.getValue();
	}

	/**
	 * ���ݼ���˳���ӡ����ѡ���Լ�������
	 */
	public String toString() {
		StringBuilder sb = new StringBuilder();
		String lineSeprarator = System.getProperty("line.separator", "\n");
		int nl = this.maxOptionNameLength + 2;
		int vl = this.maxValueNameLength + 2;

		for (Option opt : ordered) {
			sb.append("    ");
			if (null != opt.getName()) sb.append(opt.getName());
			sb.append(Tool.spaceN(nl, opt.getName()));
			if (null != opt.getValueName()) sb.append(opt.getValueName());
			sb.append(Tool.spaceN(vl, opt.getValueName()));
			sb.append(": ").append(opt.getDescription());
			if (opt.hasValue() && opt.getValueDefault() != null) {
				if (opt.getValueDefault().equals("!"))
					; // sb.append(" :REQUIRED!");
				else
					sb.append(" :DEFAULT=").append(opt.getValueDefault());
			}
			sb.append(lineSeprarator);
		}
		return sb.toString();
	}

	/**
	 * �������е�ѡ�
	 * @return
	 */
	public Map<String, Option> getOptions() {
		return options;
	}

	/**
	 * ����ѡ��֮��Ĳ����б�
	 * @return
	 */
	public List<String> getTokens() {
		return tokens;
	}

	public boolean hasToken() {
		return false == tokens.isEmpty();
	}

	/**
	 * ����ѡ�����ֵ��
	 * 
	 * �����޲�����ѡ� null ��ʾ���ѡ��û�г��ֹ�
	 * �����в�����ѡ��϶����᷵�� null��
	 * 
	 * @param optname
	 * @return
	 * @throws RuntimeException if option not exist
	 */
	public String getValue(String optname) {
		Option option = this.getOption(optname);
		if (option.hasValue())
			return option.getValue();
		return option.isPresent() ? "" : null;
	}
//
//	/**
//	 * ѡ�����ֵ�Ƿ�����
//	 * 
//	 * �����޲�����ѡ�true ��ʾѡ�������ã�false ��ʾѡ��δ�����á�
//	 * �����в�����ѡ�true ���������ã�not null��false��ʾ����û�����ã��ܲ��ܵõ������Ϳ��Ƿ���Ĭ��ֵ��  
//	 * 
//	 * @param optname
//	 * @return
//	 * @throws RuntimeException if option not exist
//	 */
//	public boolean isPresent(String optname) {
//		Option option = this.getOption(optname);
//		if (option.getValueType() == Option.VALUE_TYPE_NONE)
//			return option.isPresent();
//		return option.getValuePresent() != null;
//	}

	/**
	 * ����ѡ�
	 * @param optname ��������ȷ�����֡�
	 * @return
	 */
	public Option getOption(String optname) {
		Option option = this.options.get(optname);
		if (null == option)
			throw new RuntimeException(optname + " : unknown option");
		return option;
	}

	public static void main(String args[]) {
		String [][] _opts_ = {
				//	ѡ����       ֵ��      ��������            Ĭ��ֵ
					{"-input",  "file", "input file name",  null},           // ���Բ��ṩ������ֵΪnull
					{"-output", "file", "output file name", "defaultValue"}, // ���Բ��ṩ����ΪĬ��ֵ
					{"-mode",   "N",    "mode no.",         "!"},            // �����ṩ��
					{null,      null,   "help only",     null},           // ֻ�����������������
					{"-debug",  null,   "debug?",   null},                   // �޲���ֵ
				};

		Options opts = new Options(_opts_);
		System.out.println(opts);

		opts.parse(args);
		for (String optName : opts.getOptions().keySet())
			System.out.println(optName + "=" + opts.getValue(optName));
		System.out.println(opts.getTokens());
	}
}