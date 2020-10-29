package mytools;

<#if !defineOnly>
import org.apache.poi.ss.usermodel.Row;
import org.apache.poi.ss.usermodel.Sheet;
import org.apache.poi.ss.usermodel.Cell;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
</#if>

public class ConvMain {

	public interface Checkable{
		public void checkValid(java.util.Map<String,java.util.Map<Integer,? extends Object> > objs);
	}
	final static private org.apache.log4j.Logger logger = org.apache.log4j.Logger
			.getLogger(ConvMain.class);
<#if !defineOnly>			
	public static String getCellValue(Row w,String name,java.util.ArrayList<String> collnames){
		int index=collnames.indexOf(name);
		if(index<0) throw new IllegalArgumentException("����Ĳ���,name="+name);
		Cell c=w.getCell(index);
		if(c==null){
			return null;
		}
		if (c.toString() == "")
			return null;
		switch(c.getCellType()){
		case Cell.CELL_TYPE_BLANK:
			return null;
		case Cell.CELL_TYPE_NUMERIC:
			 double d = c.getNumericCellValue();
			 if((int)d == d)
			 	return String.valueOf((int)d);
			 else
			 	return String.valueOf(d);
		case Cell.CELL_TYPE_STRING: {
			return c.getStringCellValue();
		}
		case Cell.CELL_TYPE_BOOLEAN:
			return String.valueOf(c.getBooleanCellValue());
		case Cell.CELL_TYPE_FORMULA:
			{
				try {
					return String.valueOf(c.getNumericCellValue());
				} catch (IllegalStateException e) {
					return String.valueOf(c.getRichStringCellValue().toString());
				}
			}
		default:			
			throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
		}
	}
	
	public static Integer getIntegerCellValue(Row w,String name,java.util.ArrayList<String> collnames){
		int index=collnames.indexOf(name);
		if(index<0) throw new IllegalArgumentException("����Ĳ���,name="+name);
		Cell c=w.getCell(index);
		if(c==null){
			return null;
		}
		/*
		if (name.equals("��̯����ʱ��")) {
			Boolean bis = (c.toString() == "");
			logger.error("�ļ�����:"+c.toString()+"end" + bis.toString());
		}*/
		if (c.toString() == "")
			return null;
		
		switch(c.getCellType()){
		case Cell.CELL_TYPE_BLANK:
			return null;
		case Cell.CELL_TYPE_NUMERIC:
			return (int)c.getNumericCellValue();
		case Cell.CELL_TYPE_STRING: {			
			if (!isIntNumberic(c.getStringCellValue())) {
				return null;
			}
			return Integer.valueOf(c.getStringCellValue());	
		}
		case Cell.CELL_TYPE_FORMULA:
			{
				try {
					return Integer.valueOf((int)c.getNumericCellValue());
				} catch (IllegalStateException e) {
					String str = c.getRichStringCellValue().toString();
					if (str.equals(""))
						return null;
					return Integer.valueOf(c.getRichStringCellValue().toString());
					//throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
				}
			}
		default:
			throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
		}
	}
	
	public static Long getLongCellValue(Row w,String name,java.util.ArrayList<String> collnames){
		int index=collnames.indexOf(name);
		if(index<0) throw new IllegalArgumentException("����Ĳ���,name="+name);
		Cell c=w.getCell(index);
		if(c==null){
			return null;
		}
		if (c.toString() == "")
			return null;
		switch(c.getCellType()){
		case Cell.CELL_TYPE_BLANK:
			return null;
		case Cell.CELL_TYPE_NUMERIC:
			return (long)c.getNumericCellValue();
		case Cell.CELL_TYPE_STRING: {
			if (!isIntNumberic(c.getStringCellValue()))
				return null;
			return Long.valueOf(c.getStringCellValue());
		}
		case Cell.CELL_TYPE_FORMULA:
			{
				try {
					return Long.valueOf((long)c.getNumericCellValue());
				} catch (IllegalStateException e) {
					return Long.valueOf(c.getRichStringCellValue().toString());
				}
			}
		default:
			throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
		}
	}
	
	public static Boolean getBooleanCellValue(Row w,String name,java.util.ArrayList<String> collnames){
		int index=collnames.indexOf(name);
		if(index<0) throw new IllegalArgumentException("����Ĳ���,name="+name);
		Cell c=w.getCell(index);
		if(c==null){
			return null;
		}
		if (c.toString() == "")
			return null;
		switch(c.getCellType()){
		case Cell.CELL_TYPE_BLANK:
			return null;
		case Cell.CELL_TYPE_NUMERIC:
			return c.getNumericCellValue()!=0;
		case Cell.CELL_TYPE_STRING:
			{
				String t=c.getStringCellValue();
				if(t.equals("��") || t.equals("true") || t.equals("TRUE"))
					return true;
				else if(t.equals("��") || t.equals("false") || t.equals("FALSE"))
					return false;
				else
					throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з��ִ����ֵ"+t);
			}
		case Cell.CELL_TYPE_BOOLEAN:
			return c.getBooleanCellValue();
		case Cell.CELL_TYPE_FORMULA:
			{
				try {
					String t = String.valueOf(c.getNumericCellValue());
					if(t.equals("��") || t.equals("true"))
						return true;
					else if(t.equals("��") || t.equals("false"))
						return false;
					else
						throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з��ִ����ֵ"+t);
				} catch (IllegalStateException e) {
					String t = String.valueOf(c.getRichStringCellValue().toString());
					if(t.equals("��") || t.equals("true"))
						return true;
					else if(t.equals("��") || t.equals("false"))
						return false;
					else
						throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з��ִ����ֵ"+t);
				}
			}
		default:
			throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
		}		
	}
	
	public static Double getDoubleCellValue(Row w,String name,java.util.ArrayList<String> collnames){
		int index=collnames.indexOf(name);
		if(index<0) throw new IllegalArgumentException("����Ĳ���,name="+name);
		Cell c=w.getCell(index);
		if(c==null){
			return null;
		}
		if (c.toString() == "")
			return null;
		switch(c.getCellType()){
		case Cell.CELL_TYPE_BLANK:
			return null;
		case Cell.CELL_TYPE_NUMERIC:
			return c.getNumericCellValue();
		case Cell.CELL_TYPE_STRING:{
			if (!isNumberic(c.getStringCellValue()))
				return null;
			return Double.valueOf(c.getStringCellValue());
		}
		case Cell.CELL_TYPE_FORMULA:
			{
				try {
					return Double.valueOf(c.getNumericCellValue());
				} catch (IllegalStateException e) {
					return Double.valueOf(c.getRichStringCellValue().toString());
				}
			}
		default:
			throw new RuntimeException("�ڵ�"+w.getRowNum()+"�е�\""+name+"\"�ֶ��з���δ֪��cell����"+c.getCellType());
		}
	}
	</#if>
	private static void usage(){
		System.out.println("usage: java -jar xxx.jar inputdir server_outputdir client_outputdir");
	}
	
	private static final String[] serverClassList={
		<#list serverClassList as classname>
			"${classname}",
		</#list>		
	};
	
	private static final String[] clientClassList={
		<#list clientClassList as classname>
			"${classname}",
		</#list>		
	};
	
	@SuppressWarnings("unchecked")
	public static boolean isNumberic(String str){
		Pattern pattern = Pattern.compile("^(-?\\d+)(\\.\\d+)?$");
		Matcher isNum = pattern.matcher(str);
		if (!isNum.matches())
			return false;
		return true;
	}
	
	@SuppressWarnings("unchecked")
	public static boolean isIntNumberic(String str){
		Pattern pattern = Pattern.compile("^-?\\d+$");
		Matcher isNum = pattern.matcher(str);
		if (!isNum.matches())
			return false;
		return true;
	}
	
	@SuppressWarnings("unchecked")
	public static boolean doCheck(java.util.Map objs){
		boolean ret=true;
		for(Object obj:objs.values()){
			if(!(obj instanceof java.util.Map<?,?>)) continue;
			java.util.Map<Integer,? extends Object> m =(java.util.Map<Integer,? extends Object>)obj;
			for(java.util.Map.Entry<Integer,? extends Object> o:m.entrySet())
			if(o.getValue() instanceof mytools.ConvMain.Checkable){
				try{
					((mytools.ConvMain.Checkable)o.getValue()).checkValid((java.util.Map<String,java.util.Map<Integer,? extends Object>>)objs);
				}catch(Exception ex){
					logger.error("key="+o.getKey()+"�ļ�¼У��ʧ��,ԭ����"+ex.getMessage());
					ret=false;
				}
			} 
		}
		return ret;
	}
	<#if !defineOnly>
	
	@SuppressWarnings("unchecked")	
	public static java.util.Map<String,java.util.Map<Integer,? extends Object> > doConv(String inputdir,String outputdir,String outputdir2){
		java.util.Map<String,java.util.Map<Integer,? extends Object> > objs= new java.util.TreeMap<String,java.util.Map<Integer,? extends Object> >();
		com.thoughtworks.xstream.XStream xstream=new com.thoughtworks.xstream.XStream();
		try{
		<#list serverClassList as classname>
			objs.put("${classname}",${classname}.toXML(inputdir, outputdir, xstream));
		</#list>
		<#list clientClassList as classname>
			objs.put("${classname}",${classname}.toXML(inputdir, outputdir2, xstream));
		</#list>
		}catch(java.io.IOException ex){
			logger.error("io����",ex);
		}
		return objs;
	}
	
	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		if(args.length!=3) {
			usage();
			return ;
		}
		String inputdir=args[0];
		String outputdir=args[1];
		String outputdir2=args[2];

		if(!new java.io.File(inputdir).exists())
			throw new RuntimeException("Ŀ¼����"+inputdir+"������");
		if(!new java.io.File(outputdir).exists())
			throw new RuntimeException("Ŀ¼����"+outputdir+"������");
		if(!new java.io.File(outputdir2).exists())
			throw new RuntimeException("Ŀ¼����"+outputdir2+"������");	
		org.apache.log4j.xml.DOMConfigurator.configure("log4j.xml");	
		doCheck(doConv(inputdir,outputdir,outputdir2));
	}
	</#if>
}
