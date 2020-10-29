package snail.tools;

public class Option {
	/**
	 * ���֣��磺-f
	 */
	private String name;

	/**
	 * ����ֵ�����������Ҫ��Ϊnull��
	 */
	private String valueName;

	/**
	 * �����������磺ָ�������ļ���
	 */
	private String description;

	/**
	 * Ĭ�ϲ�����null ��ʾ���ṩĬ��ֵ��
	 */
	private String valueDefault;

	/**
	 * ������ֵ�� �������������á�
	 */
	private String value = null; 
	private boolean present = false;

	/**
	 * ѡ�����������г��ֹ������������ó�true��
	 * 
	 * ������¼�����ǣ�����������Щ����Ҫ����ֵ��ѡ����Ƿ���־��ǲ�����
	 * @return
	 */
	public boolean isPresent() {
		return present;
	}

	public void setPresent() {
		this.present = true;
	}

	public Option(String [] option) {
		if (option.length != 4)
			throw new java.lang.IllegalArgumentException();
		setParams(option[0], option[1], option[2], option[3]);
	}

	private void setParams(String name, String valueName, String description, String valueDefault) {
		if (name != null && !Option.isOption(name))
			throw new IllegalArgumentException("Option name must startsWith '-'. name=" + name);
		// �� name Ϊ null ʱ�����ѡ���������������������������������
		this.name = name;
		this.valueName = valueName;
		this.description = description;
		this.valueDefault = valueDefault;
	}

	public Option(String name, String valueName, String description, String valueDefault) {
		this.setParams(name, valueName, description, valueDefault);
	}

	public boolean hasValue() {
		return valueName != null;
	}

	public String getName() {
		return name;
	}

	public static boolean isOption(String arg) {
		return arg.startsWith("-");
	}

	public String getValueName() {
		return valueName;
	}

	public String getDescription() {
		return description;
	} 

	public String getValueDefault() {
		return this.valueDefault;
	}

	@Override
	public String toString() {
		return this.name;
	}

	/**
	 * ���ؽ����õ���ֵ������Ϊnull
	 */
	public String getValuePresent() {
		return value;
	}
	/**
	 * ����ѡ���������֧�ֵ���String���͡�
	 */
	public String getValue() {
		if ( false == hasValue() )
			throw new java.lang.IllegalStateException(this + " : no value");

		if ( null != value )
			return value;

		if (valueDefault != null && valueDefault.equals("!")) // value must present
			throw new java.lang.IllegalArgumentException(this + " : value required!");

		return valueDefault; // maybe null
	}

	public void setValue(String value) {
		if ( false == hasValue() )
			throw new IllegalStateException(this + " : no value");
		this.value = value;
	}
}
