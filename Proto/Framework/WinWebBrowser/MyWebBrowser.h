/** gaoyong change for pcmt
�����ʹ��
*/
#pragma once
#include "olecontainer.h"
#include "cocos2d.h"

class CMyWebBrowser :public COleContainer
{
public:
	CMyWebBrowser(void);
	virtual ~CMyWebBrowser(void);

	bool initWindow(HWND hParent);
	HWND GetHWND(){return m_hWnd;};//�̳е���Ӧ��ʵ���������,����WebBrowser,��������һ��HWND����WebBrowser

	//�ⲿ����
public:
	IWebBrowser2*      GetWebBrowser2();
	IHTMLDocument2*    GetHTMLDocument2();
	IHTMLDocument3*    GetHTMLDocument3();
	IHTMLWindow2*      GetHTMLWindow2();
	IHTMLEventObj*     GetHTMLEventObject();


	BOOL       SetWebRect(LPRECT lprc);
	BOOL       OpenWebBrowser();
	BOOL       showWebBrowser(VARIANT* pVarUrl,cocos2d::CCRect rc);
	void       showWebBrowser();
	void	   hideWebBrowser();


	std::string	getUrl(){return m_strUrl;}
	IDispatch * GetJScript();
	BOOL CallJScript(wchar_t * func, VARIANT * vtParams, int cNumberOfParam, VARIANT * vtResult);

	bool updateUrl();

private:
	BSTR*						_realurl;

	HWND m_hWnd;
	IWebBrowser2*               _pWB2;
	IHTMLDocument2*             _pHtmlDoc2;
	IHTMLDocument3*             _pHtmlDoc3;
	IHTMLWindow2*               _pHtmlWnd2;
	IHTMLEventObj*              _pHtmlEvent;
};

typedef void (*ONCLOSE)();

/*CC_DLL*/ 
class CMyWebBrowserEX :public COleContainer
{
public:
	CMyWebBrowserEX();
	~CMyWebBrowserEX();
	virtual HWND GetHWND(){return m_hWnd;};//�̳е���Ӧ��ʵ���������,����WebBrowser,��������һ��HWND����WebBrowser
	//���޳�ֵ��ʱ���ⲿ��ҳ��ʹ�ã���Ϊ�Ǿ�̬�ģ����������ط���ò�Ҫʹ��
	//��showWebBrowser(VARIANT* pVarUrl)��initWindow()ͬ��ʹ��
	static CMyWebBrowserEX** getWebviewInstanceEX();
	//����Ϸ�����޹ص�webview����ֵʹ��
	virtual bool initWindow();

	void	setNeedClose(bool close)	{m_bNeedClose = close;}
	bool	getNeedClose()				{return m_bNeedClose;}
	BOOL    SetWebRect(LPRECT lprc);
	BOOL    OpenWebBrowser();
	//ȫ����ʾ��webvew��������ʾ��ֵ
	BOOL    showWebBrowser(VARIANT* pVarUrl,cocos2d::CCRect rc);
	void	hideWebBrowser();

	IWebBrowser2*      GetWebBrowser2();
	IHTMLDocument2*    GetHTMLDocument2();
	IHTMLDocument3*    GetHTMLDocument3();
	IHTMLWindow2*      GetHTMLWindow2();
	IHTMLEventObj*     GetHTMLEventObject();

	void setTranslateAccelerator(UINT message, WPARAM wParam, LPARAM lParam);
	void setTranslateAccelerator(MSG& msg);
	std::string			getUrl(){return m_strUrl;}
	void setShowScroll(bool bshow)	{ m_bShowScroll = bshow; }
	IDispatch * GetJScript();
	BOOL CallJScript(wchar_t * func, VARIANT * vtParams, int cNumberOfParam, VARIANT * vtResult);

	ONCLOSE m_onClose;
private:

	HWND m_hWnd;

	IWebBrowser2*               _pWB2;
	IHTMLDocument2*             _pHtmlDoc2;
	IHTMLDocument3*             _pHtmlDoc3;
	IHTMLWindow2*               _pHtmlWnd2;
	IHTMLEventObj*              _pHtmlEvent;

	bool						m_bNeedClose;
};
/* end */
