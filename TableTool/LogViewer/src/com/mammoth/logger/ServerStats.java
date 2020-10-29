package com.mammoth.logger;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ServerStats {
	private String encoding = "UTF-8";
	String file;
	public ServerStats(String file){
		this.file = file;
	}
	
	public void countTotal() throws Exception{
		int max = 0;
		int min = 999;
		BufferedReader reader = new BufferedReader(
				new InputStreamReader(new FileInputStream(file),encoding));
		int[] up1 = new int[24];
		int[] up2 = new int[24];
		int[] down1 = new int[24];
		int[] down2 = new int[24];
		int[] pp = new int[24];
		int[] count = new int[24];
		int[] res = new int[24];//����
		Pattern p = Pattern.compile("����(\\d+?)��\\[(\\d+?)k]/����(\\d+?)��\\[(\\d+?)k]��(\\d+?)���");
		String line = "";
		Matcher m;
		int t = 0;
		while((line = reader.readLine())!= null){
			String strs[] = line.split("-", 4);
			int time  = Integer.parseInt(strs[0].split(":")[0]);
			m = null;
			m = p.matcher(line);
			if(m.find()){
				up1[time] += Integer.decode(m.group(1));
				up2[time] += Integer.decode(m.group(2));
				down1[time] += Integer.decode(m.group(3));
				down2[time] += Integer.decode(m.group(4));
				t = Integer.decode(m.group(5));
				pp[time] += t;
				count[time]++;
				if(t > max){
					max = t;
				}
				if(t < min){
					min = t;
				}
			}
		}
		reader.close();
		
		StringBuilder sb = new StringBuilder();
		sb.append("Сʱ\t�ϴ�����\t�ϴ�����\t��������\t��������\tƽ��ÿ��ÿСʱ����\tƽ��ÿ������������\r\n");
		int tu1 = 0;
		int tu2 = 0;
		int du1 = 0;
		int du2 = 0;
		int dp = 0;//����
		int dc = 0;
		int tmp = 0;
		int allres = 0;
		for(int i=0;i<24;i++){
			sb.append(i).append("\t");
			sb.append(up1[i]).append("\t");
			sb.append(up2[i]).append('\t');
			sb.append(down1[i]).append('\t');
			sb.append(down2[i]).append('\t');
			if(count[i] == 0){
				tmp = (pp[i]/60);
//				sb.append(pp[i]/60).append("\r\n");
			} else {
				tmp = pp[i]/count[i];
//				sb.append(pp[i]/count[i]).append("\r\n");
			}

			tu1 += up1[i];
			tu2 += up2[i];
			du1 += down1[i];
			du2 += down2[i];
			if(pp[i] != 0){
				dp += tmp;
				dc++;
			}
			if(tmp > 0){
				res[i] = (up2[i] + down2[i]) / tmp;
			}
			sb.append(res[i] + "\t");	
			allres += res[i];
			sb.append(tmp).append("\r\n");
		}
//		System.out.println(sb);
		sb.append("����ͳ��\r\n");
		sb.append("�ϴ�����:" + tu1 + "��  ���ϴ�����:" + (tu2/1024) + "M\r\n");
		sb.append("��������:" + tu1 + "��  ����������:" + (du2/1024) + "M\r\n");
		sb.append("ƽ��ÿСʱ����������" + (dp/dc) + "��  ��ֵ:" + max + "  �͹�:" + min + "\r\n");
		sb.append("ƽ��ÿ��ÿСʱ������" + (allres/dc) + "k");
		String outputfile = file.replace("res", "output");
		PrintWriter writer = new PrintWriter(new OutputStreamWriter(new FileOutputStream(outputfile),"GBK"));
		writer.print(sb);
		writer.close();
		System.out.println(file + "����ͳ��");
		System.out.println("�ϴ�����:" + tu1 + "��  ���ϴ�����:" + (tu2/ 1024) + "M");
		System.out.println("��������:" + tu1 + "��  ����������:" + (du2 / 1024) + "M");
		System.out.println("ƽ��ÿСʱ����������" + (dp/dc) + "��  ��ֵ:" + max + "  �͹�:" + min);
		System.out.println("ƽ��ÿ��ÿСʱ������" + (allres/dc) + "k");
	}
//	
//	public int[] parse(String line){
//		int[] result = new int[4];
//		String strs[] = line.split("-", 4);
//		String[] times = strs[0].split(":");
//		result[0] = Integer.parseInt(times[0]);
//		result[1] = Integer.parseInt(times[1]);
////		log.setMessage(strs[3]);//message
////		ϵͳ����: ÿ���ӽ���0��[0k]/����0��[0k]��0�������
//
//		Matcher matcher = p.matcher(line);
//		return result;
//	}
	public static void main(String[] args) throws Exception{
		String[] ins = {
				"0302.log",
				"0303.log",
				"0304.log",
				"0305.log",
				"0306.log",
				"0307.log",
				"0308.log",
				"0309.log",
				"0310.log",
		};
		for(int i=0;i<ins.length;i++){
			ServerStats ss = new ServerStats("res/" + ins[i]);
			ss.countTotal();
		}
	}

}
