
#include "WebViewClientImpl.h"


WebViewClientImpl::WebViewClientImpl()
{

}
WebViewClientImpl::~WebViewClientImpl()
{

}
//////////////////////////////////////////////////////////////////////////
// Called when a region of the WebWidget needs to be re-painted.
void WebViewClientImpl::didInvalidateRect(const WebRect&) { }

// Called when a region of the WebWidget, given by clipRect, should be
// scrolled by the specified dx and dy amounts.
void WebViewClientImpl::didScrollRect(int dx, int dy, const WebRect& clipRect) { }

// Called when the Widget has changed size as a result of an auto-resize.
void WebViewClientImpl::didAutoResize(const WebSize& newSize) { }

// Called when the compositor is enabled or disabled. The parameter to
// didActivateCompositor() is meaningless.
// FIXME: Remove parameter from didActivateCompositor().
void WebViewClientImpl::didActivateCompositor(int deprecated) { }
void WebViewClientImpl::didDeactivateCompositor() { }

// Attempt to initialize compositing for this widget. If this is successful,
// layerTreeView() will return a valid WebLayerTreeView.
void WebViewClientImpl::initializeLayerTreeView() { }

// Return a compositing view used for this widget. This is owned by the
// WebWidgetClient.
WebLayerTreeView* WebViewClientImpl::layerTreeView()
{
    return 0;
}

// Sometimes the WebWidget enters a state where it will generate a sequence
// of invalidations that should not, by themselves, trigger the compositor
// to schedule a new frame. This call indicates to the embedder that it
// should suppress compositor scheduling temporarily.
void WebViewClientImpl::suppressCompositorScheduling(bool enable) { }

// Indicates to the embedder that the compositor is about to begin a
// frame. This is primarily to signal to flow control mechanisms that a
// frame is beginning, not to perform actual painting work.
void WebViewClientImpl::willBeginCompositorFrame() { }

// Indicates to the embedder that the WebWidget is ready for additional
// input.
void WebViewClientImpl::didBecomeReadyForAdditionalInput() { }

// Called for compositing mode when a frame commit operation has finished.
void WebViewClientImpl::didCommitCompositorFrame() { }

// Called for compositing mode when the draw commands for a WebKit-side
// frame have been issued.
void WebViewClientImpl::didCommitAndDrawCompositorFrame() { }

// Called for compositing mode when swapbuffers has been posted in the GPU
// process.
void WebViewClientImpl::didCompleteSwapBuffers() { }

// Called when a call to WebWidget::animate is required
void WebViewClientImpl::scheduleAnimation() { }

// Called to query the state of the rendering back-end. Should return true
// when scheduleAnimation (or possibly some other cause for another frame)
// was called, but before WebWidget::animate actually does a frame.
bool WebViewClientImpl::isCompositorFramePending() const
{
    return false;
}

// Called when the widget acquires or loses focus, respectively.
void WebViewClientImpl::didFocus() { }
void WebViewClientImpl::didBlur() { }

// Called when the cursor for the widget changes.
void WebViewClientImpl::didChangeCursor(const WebCursorInfo&) { }

// Called when the widget should be closed.  WebWidget::close() should
// be called asynchronously as a result of this notification.
void WebViewClientImpl::closeWidgetSoon() { }

// Called to show the widget according to the given policy.
void WebViewClientImpl::show(WebNavigationPolicy) { }

// Called to block execution of the current thread until the widget is
// closed.
void WebViewClientImpl::runModal() { }

// Called to enter/exit fullscreen mode. If enterFullScreen returns true,
// then WebWidget::{will,Did}EnterFullScreen should bound resizing the
// WebWidget into fullscreen mode. Similarly, when exitFullScreen is
// called, WebWidget::{will,Did}ExitFullScreen should bound resizing the
// WebWidget out of fullscreen mode.
bool WebViewClientImpl::enterFullScreen()
{
    return false;
}
void WebViewClientImpl::exitFullScreen() { }

// Called to get/set the position of the widget in screen coordinates.
WebRect WebViewClientImpl::windowRect()
{
    return WebRect();
}
void WebViewClientImpl::setWindowRect(const WebRect&) { }

// Called when a tooltip should be shown at the current cursor position.
void WebViewClientImpl::setToolTipText(const WebString&, WebTextDirection hint) { }

// Called to get the position of the resizer rect in window coordinates.
WebRect WebViewClientImpl::windowResizerRect()
{
    return WebRect();
}

// Called to get the position of the root window containing the widget
// in screen coordinates.
WebRect WebViewClientImpl::rootWindowRect()
{
    return WebRect();
}

// Called to query information about the screen where this widget is
// displayed.
WebScreenInfo WebViewClientImpl::screenInfo()
{
    return WebScreenInfo();
}

// Called to get the scale factor of the display.
float WebViewClientImpl::deviceScaleFactor()
{
    return 1;
}

// When this method gets called, WebWidgetClient implementation should
// reset the input method by cancelling any ongoing composition.
void WebViewClientImpl::resetInputMethod() { }

// Requests to lock the mouse cursor. If true is returned, the success
// result will be asynchronously returned via a single call to
// WebWidget::didAcquirePointerLock() or
// WebWidget::didNotAcquirePointerLock().
// If false, the request has been denied synchronously.
bool WebViewClientImpl::requestPointerLock()
{
    return false;
}

// Cause the pointer lock to be released. This may be called at any time,
// including when a lock is pending but not yet acquired.
// WebWidget::didLosePointerLock() is called when unlock is complete.
void WebViewClientImpl::requestPointerUnlock() { }

// Returns true iff the pointer is locked to this widget.
bool WebViewClientImpl::isPointerLocked()
{
    return false;
}

// Called when a gesture event is handled.
void WebViewClientImpl::didHandleGestureEvent(const WebGestureEvent& event, bool eventCancelled) { }

// Called to update if touch events should be sent.
void WebViewClientImpl::hasTouchEventHandlers(bool) { }

// Called during WebWidget::HandleInputEvent for a TouchStart event to inform the embedder
// of the touch actions that are permitted for this touch.
void WebViewClientImpl::setTouchAction(WebTouchAction touchAction) { }
//////////////////////////////////////////////////////////////////////////
WebView* WebViewClientImpl::createView(WebFrame* creator,
                                       const WebURLRequest& request,
                                       const WebWindowFeatures& features,
                                       const WebString& name,
                                       WebNavigationPolicy policy,
                                       bool suppressOpener)
{
    return 0;
}

// Create a new WebPopupMenu.  In the second form, the client is
// responsible for rendering the contents of the popup menu.
WebWidget* WebViewClientImpl::createPopupMenu(WebPopupType)
{
    return 0;
}
WebWidget* WebViewClientImpl::createPopupMenu(const WebPopupMenuInfo&)
{
    return 0;
}
WebExternalPopupMenu* WebViewClientImpl::createExternalPopupMenu(
    const WebPopupMenuInfo&, WebExternalPopupMenuClient*)
{
    return 0;
}

// Create a session storage namespace object associated with this WebView.
WebStorageNamespace* WebViewClientImpl::createSessionStorageNamespace()
{
    return 0;
}


// Misc ----------------------------------------------------------------

// Whether or not we should report a detailed message for the given source.
bool WebViewClientImpl::shouldReportDetailedMessageForSource(const WebString& source)
{
    return false;
}

// A new message was added to the console.
void WebViewClientImpl::didAddMessageToConsole(
    const WebConsoleMessage&, const WebString& sourceName, unsigned sourceLine, const WebString& stackTrace) { }

// Called when script in the page calls window.print().  If frame is
// non-null, then it selects a particular frame, including its
// children, to print.  Otherwise, the main frame and its children
// should be printed.
void WebViewClientImpl::printPage(WebFrame*) { }

// Called to retrieve the provider of desktop notifications.
WebNotificationPresenter* WebViewClientImpl::notificationPresenter()
{
    return 0;
}

// This method enumerates all the files in the path. It returns immediately
// and asynchronously invokes the WebFileChooserCompletion with all the
// files in the directory. Returns false if the WebFileChooserCompletion
// will never be called.
bool WebViewClientImpl::enumerateChosenDirectory(const WebString& path, WebFileChooserCompletion*)
{
    return false;
}

// Creates the main WebFrame for the specified WebHelperPlugin.
// Called by WebHelperPlugin to provide the WebFrameClient interface for the WebFrame.
void WebViewClientImpl::initializeHelperPluginWebFrame(WebHelperPlugin*) { }

// Navigational --------------------------------------------------------

// These notifications bracket any loading that occurs in the WebView.
void WebViewClientImpl::didStartLoading() { }
void WebViewClientImpl::didStopLoading() { }

// Notification that some progress was made loading the current page.
// loadProgress is a value between 0 (nothing loaded) and 1.0 (frame fully
// loaded).
void WebViewClientImpl::didChangeLoadProgress(WebFrame*, double loadProgress) { }

// Editing -------------------------------------------------------------

// These methods allow the client to intercept and overrule editing
// operations.
void WebViewClientImpl::didCancelCompositionOnSelectionChange() { }
void WebViewClientImpl::didChangeSelection(bool isSelectionEmpty) { }
void WebViewClientImpl::didChangeContents() { }
void WebViewClientImpl::didExecuteCommand(const WebString& commandName) { }

// This method is called in response to WebView's handleInputEvent()
// when the default action for the current keyboard event is not
// suppressed by the page, to give the embedder a chance to handle
// the keyboard event specially.
//
// Returns true if the keyboard event was handled by the embedder,
// indicating that the default action should be suppressed.
bool WebViewClientImpl::handleCurrentKeyboardEvent()
{
    return false;
}

// Dialogs -------------------------------------------------------------

// This method opens the color chooser and returns a new WebColorChooser
// instance. If there is a WebColorChooser already from the last time this
// was called, it ends the color chooser by calling endChooser, and replaces
// it with the new one. The given list of suggestions can be used to show a
// simple interface with a limited set of choices.

// FIXME: Should be removed when the chromium side change lands.
WebColorChooser* WebViewClientImpl::createColorChooser(WebColorChooserClient*,
        const WebColor&)
{
    return 0;
}

WebColorChooser* WebViewClientImpl::createColorChooser(
    WebColorChooserClient*,
    const WebColor&,
    const WebVector<WebColorSuggestion>&)
{
    return 0;
}

// This method returns immediately after showing the dialog. When the
// dialog is closed, it should call the WebFileChooserCompletion to
// pass the results of the dialog. Returns false if
// WebFileChooseCompletion will never be called.
bool WebViewClientImpl::runFileChooser(const WebFileChooserParams&,
                                       WebFileChooserCompletion*)
{
    return false;
}

// Ask users to choose date/time for the specified parameters. When a user
// chooses a value, an implementation of this function should call
// WebDateTimeChooserCompletion::didChooseValue or didCancelChooser. If the
// implementation opened date/time chooser UI successfully, it should return
// true. This function is used only if ExternalDateTimeChooser is used.
bool WebViewClientImpl::openDateTimeChooser(const WebDateTimeChooserParams&, WebDateTimeChooserCompletion*)
{
    return false;
}

// Show a notification popup for the specified form vaidation messages
// besides the anchor rectangle. An implementation of this function should
// not hide the popup until hideValidationMessage call.
void WebViewClientImpl::showValidationMessage(const WebRect& anchorInRootView, const WebString& mainText, const WebString& supplementalText, WebTextDirection hint) { }

// Hide notifation popup for form validation messages.
void WebViewClientImpl::hideValidationMessage() { }

// Move the existing notifation popup to the new anchor position.
void WebViewClientImpl::moveValidationMessage(const WebRect& anchorInRootView) { }

// Displays a modal alert dialog containing the given message.  Returns
// once the user dismisses the dialog.
void WebViewClientImpl::runModalAlertDialog(
    WebFrame*, const WebString& message) { }

// Displays a modal confirmation dialog with the given message as
// description and OK/Cancel choices.  Returns true if the user selects
// 'OK' or false otherwise.
bool WebViewClientImpl::runModalConfirmDialog(
    WebFrame*, const WebString& message)
{
    return false;
}

// Displays a modal input dialog with the given message as description
// and OK/Cancel choices.  The input field is pre-filled with
// defaultValue.  Returns true if the user selects 'OK' or false
// otherwise.  Upon returning true, actualValue contains the value of
// the input field.
bool WebViewClientImpl::runModalPromptDialog(
    WebFrame*, const WebString& message, const WebString& defaultValue,
    WebString* actualValue)
{
    return false;
}

// Displays a modal confirmation dialog containing the given message as
// description and OK/Cancel choices, where 'OK' means that it is okay
// to proceed with closing the view.  Returns true if the user selects
// 'OK' or false otherwise.
bool WebViewClientImpl::runModalBeforeUnloadDialog(
    WebFrame*, const WebString& message)
{
    return true;
}


// UI ------------------------------------------------------------------

// Called when script modifies window.status
void WebViewClientImpl::setStatusText(const WebString&) { }

// Called when hovering over an anchor with the given URL.
void WebViewClientImpl::setMouseOverURL(const WebURL&) { }

// Called when keyboard focus switches to an anchor with the given URL.
void WebViewClientImpl::setKeyboardFocusURL(const WebURL&) { }

// Shows a context menu with commands relevant to a specific element on
// the given frame. Additional context data is supplied.
void WebViewClientImpl::showContextMenu(WebFrame*, const WebContextMenuData&) { }

// Called when the data attached to the currently displayed context menu is
// invalidated. The context menu may be closed if possible.
void WebViewClientImpl::clearContextMenu() { }

// Called when a drag-n-drop operation should begin.
void WebViewClientImpl::startDragging(WebFrame*, const WebDragData&, WebDragOperationsMask, const WebImage&, const WebPoint& dragImageOffset) { }

// Called to determine if drag-n-drop operations may initiate a page
// navigation.
bool WebViewClientImpl::acceptsLoadDrops()
{
    return true;
}

// Take focus away from the WebView by focusing an adjacent UI element
// in the containing window.
void WebViewClientImpl::focusNext() { }
void WebViewClientImpl::focusPrevious() { }

// Called when a new node gets focused.
void WebViewClientImpl::focusedNodeChanged(const WebNode&) { }

void WebViewClientImpl::numberOfWheelEventHandlersChanged(unsigned) { }

// Indicates two things:
//   1) This view may have a new layout now.
//   2) Calling layout() is a no-op.
// After calling WebWidget::layout(), expect to get this notification
// unless the view did not need a layout.
void WebViewClientImpl::didUpdateLayout() { }

// Return true to swallow the input event if the embedder will start a disambiguation popup
bool WebViewClientImpl::didTapMultipleTargets(const WebGestureEvent&, const WebVector<WebRect>& targetRects)
{
    return false;
}

// Returns comma separated list of accept languages.
WebString WebViewClientImpl::acceptLanguages()
{
    return WebString();
}

// Session history -----------------------------------------------------

// Tells the embedder to navigate back or forward in session history by
// the given offset (relative to the current position in session
// history).
void WebViewClientImpl::navigateBackForwardSoon(int offset) { }

// Returns the number of history items before/after the current
// history item.
int WebViewClientImpl::historyBackListCount()
{
    return 0;
}
int WebViewClientImpl::historyForwardListCount()
{
    return 0;
}


// Accessibility -------------------------------------------------------

// Notifies embedder about an accessibility event.
void WebViewClientImpl::postAccessibilityEvent(const WebAXObject&, WebAXEvent) { }

// Developer tools -----------------------------------------------------

// Called to notify the client that the inspector's settings were
// changed and should be saved.  See WebView::inspectorSettings.
void WebViewClientImpl::didUpdateInspectorSettings() { }

void WebViewClientImpl::didUpdateInspectorSetting(const WebString& key, const WebString& value) { }

// Geolocation ---------------------------------------------------------

// Access the embedder API for (client-based) geolocation client .
WebGeolocationClient* WebViewClientImpl::geolocationClient()
{
    return 0;
}
// Access the embedder API for (non-client-based) geolocation services.
WebGeolocationService* WebViewClientImpl::geolocationService()
{
    return 0;
}

// Speech --------------------------------------------------------------

// Access the embedder API for speech input services.
WebSpeechInputController* WebViewClientImpl::speechInputController(
    WebSpeechInputListener*)
{
    return 0;
}

// Access the embedder API for speech recognition services.
WebSpeechRecognizer* WebViewClientImpl::speechRecognizer()
{
    return 0;
}

// Zoom ----------------------------------------------------------------

// Informs the browser that the zoom levels for this frame have changed from
// the default values.
void WebViewClientImpl::zoomLimitsChanged(double minimumLevel, double maximumLevel) { }

// Informs the browser that the zoom level has changed as a result of an
// action that wasn't initiated by the client.
void WebViewClientImpl::zoomLevelChanged() { }

// Registers a new URL handler for the given protocol.
void WebViewClientImpl::registerProtocolHandler(const WebString& scheme,
        const WebString& baseUrl,
        const WebString& url,
        const WebString& title) { }

// Visibility -----------------------------------------------------------

// Returns the current visibility of the WebView.
WebPageVisibilityState WebViewClientImpl::visibilityState() const
{
    return WebPageVisibilityStateVisible;
}

// Media Streams -------------------------------------------------------

WebUserMediaClient* WebViewClientImpl::userMediaClient()
{
    return 0;
}

// Web MIDI -------------------------------------------------------------

WebMIDIClient* WebViewClientImpl::webMIDIClient()
{
    return 0;
}


// Content detection ----------------------------------------------------

// Retrieves detectable content (e.g., email addresses, phone numbers)
// around a hit test result. The embedder should use platform-specific
// content detectors to analyze the region around the hit test result.
WebContentDetectionResult WebViewClientImpl::detectContentAround(const WebHitTestResult&)
{
    return WebContentDetectionResult();
}

// Schedules a new content intent with the provided url.
void WebViewClientImpl::scheduleContentIntent(const WebURL&) { }

// Cancels any previously scheduled content intents that have not yet launched.
void WebViewClientImpl::cancelScheduledContentIntents() { }

// Draggable regions ----------------------------------------------------

// Informs the browser that the draggable regions have been updated.
void WebViewClientImpl::draggableRegionsChanged() { }

