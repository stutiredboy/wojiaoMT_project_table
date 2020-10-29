package com.mammoth.logger;

import java.util.ArrayList;
import java.util.Calendar;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.mammoth.logger.gui.LogShell;
import com.mammoth.logger.gui.SearchDialog;

public class SearchCondition {
	public int startHour = 0;
	public int startMinute = 0;
	public int endHour = 23;
	public int endMinute = 59;
	public boolean infoSelect = true;
	public boolean debugSelect = true;
	public boolean warnSelect = true;
	public boolean errorSelect = true;
	public boolean fatalSelect = true;
	
	public String className = "";
	public String keyWord = "";
	public String[] keywords;
	
    private Calendar selectStartTime=Calendar.getInstance();
    private Calendar selectEndTime=Calendar.getInstance();
    private Calendar logTime=Calendar.getInstance();
	public SearchCondition(){
	}

	private boolean needSearchLevel = false;
	private boolean needSearchTime = false;
	private boolean needSearchClass = false;
	private boolean needSearchKeyword = false;
	
	public void rebuild(){
		needSearchLevel = (anyLevel() == false);
		needSearchTime = (anyTime() == false);
		needSearchClass = (anyClass() == false);
		needSearchKeyword = (noKeyword() == false);
	}
	
	private boolean haveKeyWords(Log log){
                String tempMessage=log.getMessage().toLowerCase();
                return this.isSearchSuccess(keywords,tempMessage);
	}
	public boolean match(Log log){
		if(needSearchLevel){
			if(!matchLevel(log)){
				return false;
			}
		}
		if(needSearchTime){
			if(!matchTime(log.getTime())){
				return false;
			}
		}
		if(needSearchClass){
            String tempClassName=className.toLowerCase();
            String tempSource=log.getSource().toLowerCase();
            if(tempSource.indexOf(tempClassName)==-1)
                return false;
		}
		
		if(needSearchKeyword){
			if(!haveKeyWords(log)){
				return false;
			}
		}
		return true;
	}
	
	public boolean matchLevel(Log log){
		int level = log.getLogLevel();
		switch(level){
		case Log.LEVEL_INFO:
			return infoSelect;
		case Log.LEVEL_DEBUG:
			return debugSelect;
		case Log.LEVEL_ERROR:
			return errorSelect;
		case Log.LEVEL_WARN:
			return warnSelect;
		case Log.LEVEL_FATAL:
			return fatalSelect;
		}
		return false;
	}
	
	public boolean matchTime(String time){
		if(time == null){
			return true;
		}
		if(time.length() < 5){
			return false;
		}
        String tempTime[]=time.split(":");
		int hh =0;
		int mm = 0;
        boolean isConvers=true;//ת���Ƿ�ɹ�
        try {
            hh=Integer.parseInt(tempTime[0]);
            mm=Integer.parseInt(tempTime[1]);
        } catch (NumberFormatException e) {
            isConvers=false;
        }
        if(isConvers==false)
            return false;
        selectStartTime.set(Calendar.HOUR_OF_DAY,this.getStartHour());
        selectStartTime.set(Calendar.MINUTE,this.getStartMinute());
        selectEndTime.set(Calendar.HOUR_OF_DAY,this.getEndHour());
        selectEndTime.set(Calendar.MINUTE,this.getEndMinute());
        logTime.set(Calendar.HOUR_OF_DAY,hh);
        logTime.set(Calendar.MINUTE,mm);
        if (logTime.getTimeInMillis() > selectEndTime.getTimeInMillis()) {
            LogShell.isSearchStop = true;
            return false;
        }
        if (logTime.getTimeInMillis() >= selectStartTime.getTimeInMillis()
                && logTime.getTimeInMillis() <= selectEndTime.getTimeInMillis()) {
            return true;
        }
        return false;
	}
	
	public boolean anyTime(){
		if(startHour == 0 && startMinute == 0){
			if(endHour == 23 && endMinute == 59){
				return true;
			}
		}
		return false;
	}
	
	public boolean anyLevel(){
		return infoSelect && debugSelect && warnSelect && errorSelect && fatalSelect;
	}
	
	public boolean anyClass(){
		return className.length() <= 0;
	}
	
	public boolean noKeyword(){
		return keyWord.length() <= 0;
	}
	
	public String getClassName() {
		return className;
	}
	public void setClassName(String className) {
		this.className = className;
	}
	public boolean isDebugSelect() {
		return debugSelect;
	}
	public void setDebugSelect(boolean debugSelect) {
		this.debugSelect = debugSelect;
	}
	public int getEndHour() {
		return endHour;
	}
	public void setEndHour(int endHour) {
		this.endHour = endHour;
	}
	public int getEndMinute() {
		return endMinute;
	}
	public void setEndMinute(int endMinute) {
		this.endMinute = endMinute;
	}
	public boolean isErrorSelect() {
		return errorSelect;
	}
	public void setErrorSelect(boolean errorSelect) {
		this.errorSelect = errorSelect;
	}
	public boolean isFatalSelect() {
		return fatalSelect;
	}
	public void setFatalSelect(boolean fatalSelect) {
		this.fatalSelect = fatalSelect;
	}
	public boolean isInfoSelect() {
		return infoSelect;
	}
	public void setInfoSelect(boolean infoSelect) {
		this.infoSelect = infoSelect;
	}
	public String getKeyWord() {
		return keyWord;
	}
	public void setKeyWord(String keyWord) {
		this.keyWord = keyWord;
        keywords=this.parseString(keyWord);
	}
	public int getStartHour() {
		return startHour;
	}
	public void setStartHour(int startHour) {
		this.startHour = startHour;
	}
	public int getStartMinute() {
		return startMinute;
	}
	public void setStartMinute(int startMinute) {
		this.startMinute = startMinute;
	}
	public boolean isWarnSelect() {
		return warnSelect;
	}
	public void setWarnSelect(boolean warnSelect) {
		this.warnSelect = warnSelect;
	}
    public String[] parseString(String s) {
        int start = 0, end = 0;
        ArrayList<String> tempList = new ArrayList<String>();
        String str = "";
        if (s.startsWith("&") || s.startsWith("|")) {
            System.out.println("�Ƿ����ʽ��");
            return new String[] {};
        }
        for (int index = 0; index < s.length();) {
            char temp = s.charAt(index), tempNext = s.charAt(index + 1);
            if (temp == '!') {//�ԣ���ʼ������
                if (tempNext == '\"') {// �����������ţ�Ѱ����һ������
                    end = s.indexOf("\"", tempNext + 1);
                    if (end == -1) {// �ѵ��ַ�ĩβ
                        if (start == 0)
                            str = s.substring(start + 1);
                        else
                            str = s.substring(start, start)
                                    + s.substring(start + 1);
                        break;
                    } else {
                        if (start == 0)
                            str = s.substring(start + 1, end);
                        else
                            str = s.substring(start, start) + s.substring(start + 1, end);
                    }
                    index = end + 1;
                    start=index;
                } else {// û������Ѱ����һ��������ʶ��
                    int i = 0;
                    for (i = index + 1; i < s.length(); i++) {
                        if (s.charAt(i) == '!' || s.charAt(i) == '&'|| s.charAt(i) == '|') {
                            break;
                        }
                    }
                    // ���˱�ʾ�Ѿ��ҵ���һ��������ʶ����δ�ҵ�
                    end = i;
                    index = end;
                        str = s.substring(start, end);
                }
                start=index;
                tempList.add(str);
            } else if (temp == '&') {//�ԣ���ʼ������
                if (tempNext == '\"') {// �����������ţ�Ѱ����һ������
                    end = s.indexOf("\"", tempNext + 1);
                    if (end == -1) {// �ѵ��ַ�ĩβ
                        if (start == 0)
                            str = s.substring(start + 1);
                        else
                            str = s.substring(start , start) + s.substring(start + 1);
                        break;
                    } else {
                        if (start == 0)
                            str = s.substring(start + 1, end);
                        else
                            str = s.substring(start, start)+ s.substring(start + 1, end);
                    }
                    index = end + 1;
                    start=index;
                } else {// û������Ѱ����һ��������ʶ��
                    int i = 0;
                    for (i = index + 1; i < s.length(); i++) {
                        if (s.charAt(i) == '!' || s.charAt(i) == '&'
                                || s.charAt(i) == '|') {
                           
                            break;
                        }
                    }
                    // ���˱�ʾ�Ѿ��ҵ���һ��������ʶ����δ�ҵ�
                    end = i;
                    index = end;
                    if (start == 0)
                        str = s.substring(start + 1, end);
                    else
                        str = s.substring(start, end);
                }
                tempList.add(str);
                start=index;
            } else if (temp == '|') {//�ԣ���ʼ������
                if (tempNext == '\"') {// �����������ţ�Ѱ����һ������
                    end = s.indexOf("\"", tempNext + 1);
                    if (end == -1) {// �ѵ��ַ�ĩβ
                        if (start == 0)
                            str = s.substring(start + 1);
                        else
                            str = s.substring(start, start) + s.substring(start + 1);
                        break;
                    } else {
                        if (start == 0)
                            str = s.substring(start + 1, end);
                        else
                            str = s.substring(start, start)+ s.substring(start + 1, end);
                    }
                    index = end + 1;
                    start=index;
                } else {// û������Ѱ����һ��������ʶ��
                    int i = 0;
                    for (i = index + 1; i < s.length(); i++) {
                        if (s.charAt(i) == '!' || s.charAt(i) == '&'|| s.charAt(i) == '|') {
                            break;
                        }
                    }
                    // ���˱�ʾ�Ѿ��ҵ���һ��������ʶ����δ�ҵ�
                    end=i;
                    index = end;
                    if (start == 0)
                        str = s.substring(start + 1, end);
                    else
                        str = s.substring(start, end);
                }
                start=index;
                tempList.add(str);
            } else if (temp == '\"') {//��"��ʼ
                end = s.indexOf('\"', start+1);
                if (end == -1) {
                    str = s.substring(start+1);
                    tempList.add(str);
                    break;

                } else {
                    str = s.substring(start+1, end);
                    index = end + 1;
                }
                start=index;
                tempList.add(str);
            } else {
                int i = 0;
                for (i = index + 1; i < s.length(); i++) {
                    if (s.charAt(i) == '!' || s.charAt(i) == '&'|| s.charAt(i) == '|') {
                        break;
                    }
                }
                // ���˱�ʾ�Ѿ��ҵ���һ��������ʶ����δ�ҵ�
                end = i;
                index = end;
                str = s.substring(start, end);
                start=index;
                tempList.add(str);
            }
        }
        String [] tempStr=new String[tempList.size()];
        tempList.toArray(tempStr);
        return tempStr;
    }
    /**
     * @author lzg
     * @param aKeyWords
     * @param message
     * @return
     * ����aKeyWords��������Message�����ж�
     */
    public boolean isSearchSuccess(String[] aKeyWords,String message) {
        boolean isHave = true;
        for (int index = 0; index < aKeyWords.length; index++) {
            String temp = aKeyWords[index].toLowerCase();
            char option = 0;
            String value = "";
            if (temp.startsWith("&") || temp.startsWith("!")|| temp.startsWith("|")) {
                option = temp.charAt(0);
                value = temp.substring(1);
            } else {
                option = 0;
                value = temp;
            }
            switch (option) {
            case '&':
                if (message.indexOf(value) == -1) {// �������ʧ�ܣ���Ҫ��������Ƿ��л�����������м����жϣ�û���򷵻�
                    int i=0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i] .charAt(0) == '|')// �л����������Լ����ж�
                            break;
                    }
                    if(i==aKeyWords.length)
                        isHave = false;
                }
                else
                {//�������ȫ�ǻ�������ж���Ϊ��
                    int i=0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i] .charAt(0) != '|')// �л����������Լ����ж�
                            break;
                        
                    }
                    if(i==aKeyWords.length)//֤������ȫ�ǻ�
                        return true;
                }
                break;
            case '!':
                if (message.indexOf(value) >= 0) {// �ǵ�����ʧ�ܣ���Ҫ��������Ƿ��л�����������м����жϣ�û���򷵻�
                    int i =0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i] .charAt(0) == '|')// �л����������Լ����ж�
                            break;
                    }
                    if(i==aKeyWords.length)
                        isHave = false;
                }
                else
                {//�����ɹ����������ȫ�ǻ�������ж�Ϊ��
                    int i=0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i].charAt(0) != '|')// �л����������Լ����ж�
                            break;
                        
                    }
                    if(i==aKeyWords.length)//֤������ȫ�ǻ�
                        return true;
                }
                break;
            case '|':
                if (message.indexOf(value) >= 0) {// ��ʾ�������㣬���Է���
                    isHave = true;
                    index = aKeyWords.length;
                }
                else
                {
                    if(index+1==aKeyWords.length)//���һ��������������
                        isHave=false;
                }
                break;
            case 0:
                if (message.indexOf(value) == -1) {
                    int i=0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i] .charAt(0) == '|')// �л����������Լ����ж�
                            break;;
                    }
                    if(i==aKeyWords.length)
                    isHave = false;
                }
                else
                {//�����ɹ����������ȫ�ǻ�������ж�Ϊ��
                    int i=0;
                    for (i = index + 1; i < aKeyWords.length; i++) {
                        if (aKeyWords[i].charAt(0) != '|')// �л����������Լ����ж�
                            break;
                        
                    }
                    if(i==aKeyWords.length)//֤������ȫ�ǻ�
                        return true;
                }
                break;
            }
            if (isHave == false)
                return false;
            //���ؼ�
        }
        return true;
    }
}
