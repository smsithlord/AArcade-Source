#ifndef C_AWESOMIUM_BROWSER_INSTANCE_H
#define C_AWESOMIUM_BROWSER_INSTANCE_H

//#include "..\..\public\steam\isteamhtmlsurface.h"
#include "c_awesomiumjshandlers.h"
#include "../../public/steam/steam_api.h"
#include "c_embeddedinstance.h"
#include <string>
#include "vgui_controls/Controls.h"
#include <Awesomium/WebCore.h>
#include <Awesomium/STLHelpers.h>
#include <Awesomium/BitmapSurface.h>
#include <vector>

class C_AwesomiumBrowserInstance : public C_EmbeddedInstance
{
public:
	C_AwesomiumBrowserInstance();
	~C_AwesomiumBrowserInstance();

	void SelfDestruct();

	void Init(std::string id = "", std::string url = "", bool alpha = false);

	std::string GetId() { return m_id; }
	void Update();

	void ResizeFrameFromRGB565(const void* pSrc, void* pDst, unsigned int sourceWidth, unsigned int sourceHeight, size_t sourcePitch, unsigned int sourceDepth, unsigned int destWidth, unsigned int destHeight, size_t destPitch, unsigned int destDepth);
	void ResizeFrameFromRGB1555(const void* pSrc, void* pDst, unsigned int sourceWidth, unsigned int sourceHeight, size_t sourcePitch, unsigned int sourceDepth, unsigned int destWidth, unsigned int destHeight, size_t destPitch, unsigned int destDepth);
	void ResizeFrameFromXRGB8888(const void* pSrc, void* pDst, unsigned int sourceWidth, unsigned int sourceHeight, size_t sourcePitch, unsigned int sourceDepth, unsigned int destWidth, unsigned int destHeight, size_t destPitch, unsigned int destDepth);
	void CopyLastFrame(unsigned char* dest, unsigned int width, unsigned int height, size_t pitch, unsigned int depth);

	void OnProxyBind(C_BaseEntity* pBaseEntity);
	void Render();
	void RegenerateTextureBits(ITexture *pTexture, IVTFTexture *pVTFTexture, Rect_t *pSubRect);

	void OnMouseMove(float x, float y);
	void OnMousePressed(vgui::MouseCode code);
	void OnMouseReleased(vgui::MouseCode code);

	void DispatchJavaScriptMethod(std::string objectName, std::string objectMethod, std::vector<std::string> methodArguments);
	void DispatchJavaScriptMethodCalls();
	//void DispatchJavaScriptEventMessages(std::string objectName, std::string objectMethod, std::vector<JSEventMessage_t*> eventArgs);
	//void DispatchJavaScriptMethod(std::string objectName, std::string objectMethod, std::vector<std::string> methodArguments);
	//void DispatchJavaScriptMethodBatch(C_WebTab* pWebTab, std::vector<MethodBatch_t*> batch);

	// hud webtab only
	void SetHudTitle(std::string title);
	void AddHudLoadingMessage(std::string type, std::string text, std::string title = "", std::string id = "", std::string min = "", std::string max = "", std::string current = "", std::string callbackMethod = "");
	//std::vector<JavaScriptMethodCall_t*> GetJavaScriptMethodCalls() { return m_javaScriptMethodCalls; }

	// accessors
	ITexture* GetTexture() { return m_pTexture; }
	int GetLastRenderedFrame() { return m_iLastRenderedFrame; }
	std::string GetInitialURL() { return m_initialURL; }
	Awesomium::WebView* GetWebView() { return m_pWebView; }
	std::vector<JavaScriptMethodCall_t*> GetJavaScriptMethodCalls() { return m_javaScriptMethodCalls; }
	int GetState() { return m_iState; }
	C_InputListener* GetInputListener();

	// mutators	
	//void SetState(int val) { m_iState = val; }
	void SetState(int state) { m_iState = state; }
	void SetWebView(Awesomium::WebView* pWebView) { m_pWebView = pWebView; }

private:
	std::vector<JavaScriptMethodCall_t*> m_javaScriptMethodCalls;

	int m_iState;
	void* m_pLastFrameData;
	bool m_bReadyForNextFrame;
	bool m_bCopyingFrame;
	bool m_bReadyToCopyFrame;
	ITexture* m_pTexture;
	int m_iLastRenderedFrame;
	HHTMLBrowser m_unBrowserHandle;
	std::string m_id;
	std::string m_initialURL;
	bool m_bAlpha;
	void* m_pPostData;
	bool m_bIsDirty;
	Awesomium::WebView* m_pWebView;
};

#endif