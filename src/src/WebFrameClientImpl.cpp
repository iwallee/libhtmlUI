
#include "WebFrameClientImpl.h"

// May return null.
WebPlugin* WebFrameClientImpl::createPlugin(WebFrame*, const WebPluginParams&)
{
    return 0;
}

// May return null.
WebMediaPlayer* WebFrameClientImpl::createMediaPlayer(WebFrame*, const WebURL&, WebMediaPlayerClient*)
{
    return 0;
}

// May return null.
WebApplicationCacheHost* WebFrameClientImpl::createApplicationCacheHost(WebFrame*, WebApplicationCacheHostClient*)
{
    return 0;
}

// May return null. Takes ownership of the client.
WebServiceWorkerProvider* WebFrameClientImpl::createServiceWorkerProvider(WebFrame*, WebServiceWorkerProviderClient*)
{
    return 0;
}

// May return null.
WebWorkerPermissionClientProxy* WebFrameClientImpl::createWorkerPermissionClientProxy(WebFrame*)
{
    return 0;
}


// Services ------------------------------------------------------------

// A frame specific cookie jar.  May return null, in which case
// WebKitPlatformSupport::cookieJar() will be called to access cookies.
WebCookieJar* WebFrameClientImpl::cookieJar(WebFrame*)
{
    return 0;
}


// General notifications -----------------------------------------------

// Indicates that another page has accessed the DOM of the initial empty
// document of a main frame. After this, it is no longer safe to show a
// pending navigation's URL, because a URL spoof is possible.
void WebFrameClientImpl::didAccessInitialDocument(WebFrame*) { }

// A child frame was created in this frame. This is called when the frame
// is created and initialized. Takes the name of the new frame, the parent
// frame and returns a new WebFrame. The WebFrame is considered in-use
// until frameDetached() is called on it.
WebFrame* WebFrameClientImpl::createChildFrame(WebFrame* parent, const WebString& frameName)
{
    return 0;
}
// FIXME: Remove when all embedders use createChildFrame().
void WebFrameClientImpl::didCreateFrame(WebFrame* parent, WebFrame* child) { }

// This frame set its opener to null, disowning it.
// See http://html.spec.whatwg.org/#dom-opener.
void WebFrameClientImpl::didDisownOpener(WebFrame*) { }

// This frame has been detached from the view, but has not been closed yet.
void WebFrameClientImpl::frameDetached(WebFrame*) { }

// This frame is about to be closed. This is called after frameDetached,
// when the document is being unloaded, due to new one committing.
void WebFrameClientImpl::willClose(WebFrame*) { }

// This frame's name has changed.
void WebFrameClientImpl::didChangeName(WebFrame*, const WebString&) { }

// Called when a watched CSS selector matches or stops matching.
void WebFrameClientImpl::didMatchCSS(WebFrame*, const WebVector<WebString>& newlyMatchingSelectors, const WebVector<WebString>& stoppedMatchingSelectors) { }

// Load commands -------------------------------------------------------

// The client should handle the navigation externally.
void WebFrameClientImpl::loadURLExternally(
    WebFrame*, const WebURLRequest&, WebNavigationPolicy) { }
void WebFrameClientImpl::loadURLExternally(
    WebFrame*, const WebURLRequest&, WebNavigationPolicy, const WebString& downloadName) { }


// Navigational queries ------------------------------------------------

// The client may choose to alter the navigation policy.  Otherwise,
// defaultPolicy should just be returned.
WebNavigationPolicy WebFrameClientImpl::decidePolicyForNavigation(
    WebFrame*, WebDataSource::ExtraData*, const WebURLRequest&, WebNavigationType,
    WebNavigationPolicy defaultPolicy, bool isRedirect)
{
    return defaultPolicy;
}


// Navigational notifications ------------------------------------------

// A form submission has been requested, but the page's submit event handler
// hasn't yet had a chance to run (and possibly alter/interrupt the submit.)
void WebFrameClientImpl::willSendSubmitEvent(WebFrame*, const WebFormElement&) { }

// A form submission is about to occur.
void WebFrameClientImpl::willSubmitForm(WebFrame*, const WebFormElement&) { }

// A datasource has been created for a new navigation.  The given
// datasource will become the provisional datasource for the frame.
void WebFrameClientImpl::didCreateDataSource(WebFrame*, WebDataSource*) { }

// A new provisional load has been started.
void WebFrameClientImpl::didStartProvisionalLoad(WebFrame*) { }

// The provisional load was redirected via a HTTP 3xx response.
void WebFrameClientImpl::didReceiveServerRedirectForProvisionalLoad(WebFrame*) { }

// The provisional load failed.
void WebFrameClientImpl::didFailProvisionalLoad(WebFrame*, const WebURLError&) { }

// The provisional datasource is now committed.  The first part of the
// response body has been received, and the encoding of the response
// body is known.
void WebFrameClientImpl::didCommitProvisionalLoad(WebFrame*, bool isNewNavigation) { }

// The window object for the frame has been cleared of any extra
// properties that may have been set by script from the previously
// loaded document.
void WebFrameClientImpl::didClearWindowObject(WebFrame*) { }

// The document element has been created.
void WebFrameClientImpl::didCreateDocumentElement(WebFrame*) { }

// The page title is available.
void WebFrameClientImpl::didReceiveTitle(WebFrame* frame, const WebString& title, WebTextDirection direction) { }

// The icon for the page have changed.
void WebFrameClientImpl::didChangeIcon(WebFrame*, WebIconURL::Type) { }

// The frame's document finished loading.
void WebFrameClientImpl::didFinishDocumentLoad(WebFrame*) {
}

// The 'load' event was dispatched.
void WebFrameClientImpl::didHandleOnloadEvents(WebFrame*) { }

// The frame's document or one of its subresources failed to load.
void WebFrameClientImpl::didFailLoad(WebFrame*, const WebURLError&) { }

// The frame's document and all of its subresources succeeded to load.
void WebFrameClientImpl::didFinishLoad(WebFrame*) { }

// The navigation resulted in no change to the documents within the page.
// For example, the navigation may have just resulted in scrolling to a
// named anchor or a PopState event may have been dispatched.
void WebFrameClientImpl::didNavigateWithinPage(WebFrame*, bool isNewNavigation) { }

// Called upon update to scroll position, document state, and other
// non-navigational events related to the data held by WebHistoryItem.
// WARNING: This method may be called very frequently.
void WebFrameClientImpl::didUpdateCurrentHistoryItem(WebFrame*) { }


// Low-level resource notifications ------------------------------------

// An element will request a resource.
void WebFrameClientImpl::willRequestResource(WebFrame*, const WebCachedURLRequest&) { }

// The request is after preconnect is triggered.
void WebFrameClientImpl::willRequestAfterPreconnect(WebFrame*, WebURLRequest&) { }

// A request is about to be sent out, and the client may modify it.  Request
// is writable, and changes to the URL, for example, will change the request
// made.  If this request is the result of a redirect, then redirectResponse
// will be non-null and contain the response that triggered the redirect.
void WebFrameClientImpl::willSendRequest(
    WebFrame*, unsigned identifier, WebURLRequest&,
    const WebURLResponse& redirectResponse) { }

// Response headers have been received for the resource request given
// by identifier.
void WebFrameClientImpl::didReceiveResponse(
    WebFrame*, unsigned identifier, const WebURLResponse&) { }

void WebFrameClientImpl::didChangeResourcePriority(
    WebFrame*, unsigned identifier, const blink::WebURLRequest::Priority&) { }

// The resource request given by identifier succeeded.
void WebFrameClientImpl::didFinishResourceLoad(
    WebFrame*, unsigned identifier) { }

// The specified request was satified from WebCore's memory cache.
void WebFrameClientImpl::didLoadResourceFromMemoryCache(
    WebFrame*, const WebURLRequest&, const WebURLResponse&) { }

// This frame has displayed inactive content (such as an image) from an
// insecure source.  Inactive content cannot spread to other frames.
void WebFrameClientImpl::didDisplayInsecureContent(WebFrame*) { }

// The indicated security origin has run active content (such as a
// script) from an insecure source.  Note that the insecure content can
// spread to other frames in the same origin.
void WebFrameClientImpl::didRunInsecureContent(WebFrame*, const WebSecurityOrigin&, const WebURL& insecureURL) { }

// A reflected XSS was encountered in the page and suppressed.
void WebFrameClientImpl::didDetectXSS(WebFrame*, const WebURL&, bool didBlockEntirePage) { }

// A PingLoader was created, and a request dispatched to a URL.
void WebFrameClientImpl::didDispatchPingLoader(WebFrame*, const WebURL&) { }

// The loaders in this frame have been stopped.
void WebFrameClientImpl::didAbortLoading(WebFrame*) { }

// Script notifications ------------------------------------------------

// Script in the page tried to allocate too much memory.
void WebFrameClientImpl::didExhaustMemoryAvailableForScript(WebFrame*) { }

// Notifies that a new script context has been created for this frame.
// This is similar to didClearWindowObject but only called once per
// frame context.
void WebFrameClientImpl::didCreateScriptContext(WebFrame*, v8::Handle<v8::Context>, int extensionGroup, int worldId) { }

// WebKit is about to release its reference to a v8 context for a frame.
void WebFrameClientImpl::willReleaseScriptContext(WebFrame*, v8::Handle<v8::Context>, int worldId) { }

// Geometry notifications ----------------------------------------------

// The frame's document finished the initial non-empty layout of a page.
void WebFrameClientImpl::didFirstVisuallyNonEmptyLayout(WebFrame*) { }

// The size of the content area changed.
void WebFrameClientImpl::didChangeContentsSize(WebFrame*, const WebSize&) { }

// The main frame scrolled.
void WebFrameClientImpl::didChangeScrollOffset(WebFrame*) { }

// If the frame is loading an HTML document, this will be called to
// notify that the <body> will be attached soon.
void WebFrameClientImpl::willInsertBody(WebFrame*) { }

// Find-in-page notifications ------------------------------------------

// Notifies how many matches have been found so far, for a given
// identifier.  |finalUpdate| specifies whether this is the last update
// (all frames have completed scoping).
void WebFrameClientImpl::reportFindInPageMatchCount(
    int identifier, int count, bool finalUpdate) { }

// Notifies what tick-mark rect is currently selected.   The given
// identifier lets the client know which request this message belongs
// to, so that it can choose to ignore the message if it has moved on
// to other things.  The selection rect is expected to have coordinates
// relative to the top left corner of the web page area and represent
// where on the screen the selection rect is currently located.
void WebFrameClientImpl::reportFindInPageSelection(
    int identifier, int activeMatchOrdinal, const WebRect& selection) { }

// Quota ---------------------------------------------------------

// Requests a new quota size for the origin's storage.
// |newQuotaInBytes| indicates how much storage space (in bytes) the
// caller expects to need.
// WebStorageQuotaCallbacks::didGrantStorageQuota will be called when
// a new quota is granted. WebStorageQuotaCallbacks::didFail
// is called with an error code otherwise.
// Note that the requesting quota size may not always be granted and
// a smaller amount of quota than requested might be returned.
// The callbacks object is deleted when the callback method is called
// and does not need to be (and should not be) deleted manually.
void WebFrameClientImpl::requestStorageQuota(
    WebFrame*, WebStorageQuotaType,
    unsigned long long newQuotaInBytes,
    WebStorageQuotaCallbacks*) { }

// WebSocket -----------------------------------------------------

// A WebSocket object is going to open new stream connection.
void WebFrameClientImpl::willOpenSocketStream(WebSocketStreamHandle*) { }

// MediaStream -----------------------------------------------------

// A new WebRTCPeerConnectionHandler is created.
void WebFrameClientImpl::willStartUsingPeerConnectionHandler(WebFrame*, WebRTCPeerConnectionHandler*) { }

// Messages ------------------------------------------------------

// Notifies the embedder that a postMessage was issued on this frame, and
// gives the embedder a chance to handle it instead of WebKit. Returns true
// if the embedder handled it.
bool WebFrameClientImpl::willCheckAndDispatchMessageEvent(
    WebFrame* sourceFrame,
    WebFrame* targetFrame,
    WebSecurityOrigin target,
    WebDOMMessageEvent event)
{
    return false;
}

// Asks the embedder if a specific user agent should be used for the given
// URL. Non-empty strings indicate an override should be used. Otherwise,
// Platform::current()->userAgent() will be called to provide one.
WebString WebFrameClientImpl::userAgentOverride(WebFrame*, const WebURL& url)
{
    return WebString();
}

// Asks the embedder what value the network stack will send for the DNT
// header. An empty string indicates that no DNT header will be send.
WebString WebFrameClientImpl::doNotTrackValue(WebFrame*)
{
    return WebString();
}

// WebGL ------------------------------------------------------

// Asks the embedder whether WebGL is allowed for the given WebFrame.
// This call is placed here instead of WebPermissionClient because this
// class is implemented in content/, and putting it here avoids adding
// more public content/ APIs.
bool WebFrameClientImpl::allowWebGL(WebFrame*, bool defaultValue)
{
    return defaultValue;
}

// Notifies the client that a WebGL context was lost on this page with the
// given reason (one of the GL_ARB_robustness status codes; see
// Extensions3D.h in WebCore/platform/graphics).
void WebFrameClientImpl::didLoseWebGLContext(WebFrame*, int) { }
