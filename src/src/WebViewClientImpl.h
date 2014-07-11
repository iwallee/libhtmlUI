#ifndef WebViewClientImpl_h
#define WebViewClientImpl_h

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "base/memory/weak_ptr.h"

#include "../../web/webviewclient.h"

using namespace blink;

class WebViewClientImpl
    : public blink::WebViewClient
    , public base::SupportsWeakPtr<WebViewClientImpl>
{
public:
    WebViewClientImpl();
    ~WebViewClientImpl();
    //////////////////////////////////////////////////////////////////////////
    // Called when a region of the WebWidget needs to be re-painted.
    virtual void didInvalidateRect(const WebRect&) ;

    // Called when a region of the WebWidget, given by clipRect, should be
    // scrolled by the specified dx and dy amounts.
    virtual void didScrollRect(int dx, int dy, const WebRect& clipRect) ;

    // Called when the Widget has changed size as a result of an auto-resize.
    virtual void didAutoResize(const WebSize& newSize) ;

    // Called when the compositor is enabled or disabled. The parameter to
    // didActivateCompositor() is meaningless.
    // FIXME: Remove parameter from didActivateCompositor().
    virtual void didActivateCompositor(int deprecated) ;
    virtual void didDeactivateCompositor() ;

    // Attempt to initialize compositing for this widget. If this is successful,
    // layerTreeView() will return a valid WebLayerTreeView.
    virtual void initializeLayerTreeView() ;

    // Return a compositing view used for this widget. This is owned by the
    // WebWidgetClient.
    virtual WebLayerTreeView* layerTreeView() ;

    // Sometimes the WebWidget enters a state where it will generate a sequence
    // of invalidations that should not, by themselves, trigger the compositor
    // to schedule a new frame. This call indicates to the embedder that it
    // should suppress compositor scheduling temporarily.
    virtual void suppressCompositorScheduling(bool enable) ;

    // Indicates to the embedder that the compositor is about to begin a
    // frame. This is primarily to signal to flow control mechanisms that a
    // frame is beginning, not to perform actual painting work.
    virtual void willBeginCompositorFrame() ;

    // Indicates to the embedder that the WebWidget is ready for additional
    // input.
    virtual void didBecomeReadyForAdditionalInput() ;

    // Called for compositing mode when a frame commit operation has finished.
    virtual void didCommitCompositorFrame() ;

    // Called for compositing mode when the draw commands for a WebKit-side
    // frame have been issued.
    virtual void didCommitAndDrawCompositorFrame() ;

    // Called for compositing mode when swapbuffers has been posted in the GPU
    // process.
    virtual void didCompleteSwapBuffers() ;

    // Called when a call to WebWidget::animate is required
    virtual void scheduleAnimation() ;

    // Called to query the state of the rendering back-end. Should return true
    // when scheduleAnimation (or possibly some other cause for another frame)
    // was called, but before WebWidget::animate actually does a frame.
    virtual bool isCompositorFramePending() const ;

    // Called when the widget acquires or loses focus, respectively.
    virtual void didFocus() ;
    virtual void didBlur() ;

    // Called when the cursor for the widget changes.
    virtual void didChangeCursor(const WebCursorInfo&) ;

    // Called when the widget should be closed.  WebWidget::close() should
    // be called asynchronously as a result of this notification.
    virtual void closeWidgetSoon() ;

    // Called to show the widget according to the given policy.
    virtual void show(WebNavigationPolicy) ;

    // Called to block execution of the current thread until the widget is
    // closed.
    virtual void runModal() ;

    // Called to enter/exit fullscreen mode. If enterFullScreen returns true,
    // then WebWidget::{will,Did}EnterFullScreen should bound resizing the
    // WebWidget into fullscreen mode. Similarly, when exitFullScreen is
    // called, WebWidget::{will,Did}ExitFullScreen should bound resizing the
    // WebWidget out of fullscreen mode.
    virtual bool enterFullScreen() ;
    virtual void exitFullScreen() ;

    // Called to get/set the position of the widget in screen coordinates.
    virtual WebRect windowRect() ;
    virtual void setWindowRect(const WebRect&) ;

    // Called when a tooltip should be shown at the current cursor position.
    virtual void setToolTipText(const WebString&, WebTextDirection hint) ;

    // Called to get the position of the resizer rect in window coordinates.
    virtual WebRect windowResizerRect() ;

    // Called to get the position of the root window containing the widget
    // in screen coordinates.
    virtual WebRect rootWindowRect() ;

    // Called to query information about the screen where this widget is
    // displayed.
    virtual WebScreenInfo screenInfo();

    // Called to get the scale factor of the display.
    virtual float deviceScaleFactor();

    // When this method gets called, WebWidgetClient implementation should
    // reset the input method by cancelling any ongoing composition.
    virtual void resetInputMethod() ;

    // Requests to lock the mouse cursor. If true is returned, the success
    // result will be asynchronously returned via a single call to
    // WebWidget::didAcquirePointerLock() or
    // WebWidget::didNotAcquirePointerLock().
    // If false, the request has been denied synchronously.
    virtual bool requestPointerLock() ;

    // Cause the pointer lock to be released. This may be called at any time,
    // including when a lock is pending but not yet acquired.
    // WebWidget::didLosePointerLock() is called when unlock is complete.
    virtual void requestPointerUnlock() ;

    // Returns true iff the pointer is locked to this widget.
    virtual bool isPointerLocked() ;

    // Called when a gesture event is handled.
    virtual void didHandleGestureEvent(const WebGestureEvent& event, bool eventCancelled) ;

    // Called to update if touch events should be sent.
    virtual void hasTouchEventHandlers(bool) ;

    // Called during WebWidget::HandleInputEvent for a TouchStart event to inform the embedder
    // of the touch actions that are permitted for this touch.
    virtual void setTouchAction(WebTouchAction touchAction) ;
    //////////////////////////////////////////////////////////////////////////
    virtual WebView* createView(WebFrame* creator,
                                const WebURLRequest& request,
                                const WebWindowFeatures& features,
                                const WebString& name,
                                WebNavigationPolicy policy,
                                bool suppressOpener);

    // Create a new WebPopupMenu.  In the second form, the client is
    // responsible for rendering the contents of the popup menu.
    virtual WebWidget* createPopupMenu(WebPopupType) ;
    virtual WebWidget* createPopupMenu(const WebPopupMenuInfo&) ;
    virtual WebExternalPopupMenu* createExternalPopupMenu(
        const WebPopupMenuInfo&, WebExternalPopupMenuClient*);

    // Create a session storage namespace object associated with this WebView.
    virtual WebStorageNamespace* createSessionStorageNamespace() ;


    // Misc ----------------------------------------------------------------

    // Whether or not we should report a detailed message for the given source.
    virtual bool shouldReportDetailedMessageForSource(const WebString& source) ;

    // A new message was added to the console.
    virtual void didAddMessageToConsole(
        const WebConsoleMessage&, const WebString& sourceName, unsigned sourceLine, const WebString& stackTrace) ;

    // Called when script in the page calls window.print().  If frame is
    // non-null, then it selects a particular frame, including its
    // children, to print.  Otherwise, the main frame and its children
    // should be printed.
    virtual void printPage(WebFrame*) ;

    // Called to retrieve the provider of desktop notifications.
    virtual WebNotificationPresenter* notificationPresenter() ;

    // This method enumerates all the files in the path. It returns immediately
    // and asynchronously invokes the WebFileChooserCompletion with all the
    // files in the directory. Returns false if the WebFileChooserCompletion
    // will never be called.
    virtual bool enumerateChosenDirectory(const WebString& path, WebFileChooserCompletion*) ;

    // Creates the main WebFrame for the specified WebHelperPlugin.
    // Called by WebHelperPlugin to provide the WebFrameClient interface for the WebFrame.
    virtual void initializeHelperPluginWebFrame(WebHelperPlugin*) ;

    // Navigational --------------------------------------------------------

    // These notifications bracket any loading that occurs in the WebView.
    virtual void didStartLoading() ;
    virtual void didStopLoading() ;

    // Notification that some progress was made loading the current page.
    // loadProgress is a value between 0 (nothing loaded) and 1.0 (frame fully
    // loaded).
    virtual void didChangeLoadProgress(WebFrame*, double loadProgress) ;

    // Editing -------------------------------------------------------------

    // These methods allow the client to intercept and overrule editing
    // operations.
    virtual void didCancelCompositionOnSelectionChange() ;
    virtual void didChangeSelection(bool isSelectionEmpty) ;
    virtual void didChangeContents() ;
    virtual void didExecuteCommand(const WebString& commandName) ;

    // This method is called in response to WebView's handleInputEvent()
    // when the default action for the current keyboard event is not
    // suppressed by the page, to give the embedder a chance to handle
    // the keyboard event specially.
    //
    // Returns true if the keyboard event was handled by the embedder,
    // indicating that the default action should be suppressed.
    virtual bool handleCurrentKeyboardEvent() ;

    // Dialogs -------------------------------------------------------------

    // This method opens the color chooser and returns a new WebColorChooser
    // instance. If there is a WebColorChooser already from the last time this
    // was called, it ends the color chooser by calling endChooser, and replaces
    // it with the new one. The given list of suggestions can be used to show a
    // simple interface with a limited set of choices.

    // FIXME: Should be removed when the chromium side change lands.
    virtual WebColorChooser* createColorChooser(WebColorChooserClient*,
            const WebColor&);

    virtual WebColorChooser* createColorChooser(
        WebColorChooserClient*,
        const WebColor&,
        const WebVector<WebColorSuggestion>&);

    // This method returns immediately after showing the dialog. When the
    // dialog is closed, it should call the WebFileChooserCompletion to
    // pass the results of the dialog. Returns false if
    // WebFileChooseCompletion will never be called.
    virtual bool runFileChooser(const WebFileChooserParams&,
                                WebFileChooserCompletion*);

    // Ask users to choose date/time for the specified parameters. When a user
    // chooses a value, an implementation of this function should call
    // WebDateTimeChooserCompletion::didChooseValue or didCancelChooser. If the
    // implementation opened date/time chooser UI successfully, it should return
    // true. This function is used only if ExternalDateTimeChooser is used.
    virtual bool openDateTimeChooser(const WebDateTimeChooserParams&, WebDateTimeChooserCompletion*) ;

    // Show a notification popup for the specified form vaidation messages
    // besides the anchor rectangle. An implementation of this function should
    // not hide the popup until hideValidationMessage call.
    virtual void showValidationMessage(const WebRect& anchorInRootView, const WebString& mainText, const WebString& supplementalText, WebTextDirection hint) ;

    // Hide notifation popup for form validation messages.
    virtual void hideValidationMessage() ;

    // Move the existing notifation popup to the new anchor position.
    virtual void moveValidationMessage(const WebRect& anchorInRootView) ;

    // Displays a modal alert dialog containing the given message.  Returns
    // once the user dismisses the dialog.
    virtual void runModalAlertDialog(
        WebFrame*, const WebString& message) ;

    // Displays a modal confirmation dialog with the given message as
    // description and OK/Cancel choices.  Returns true if the user selects
    // 'OK' or false otherwise.
    virtual bool runModalConfirmDialog(
        WebFrame*, const WebString& message);

    // Displays a modal input dialog with the given message as description
    // and OK/Cancel choices.  The input field is pre-filled with
    // defaultValue.  Returns true if the user selects 'OK' or false
    // otherwise.  Upon returning true, actualValue contains the value of
    // the input field.
    virtual bool runModalPromptDialog(
        WebFrame*, const WebString& message, const WebString& defaultValue,
        WebString* actualValue);

    // Displays a modal confirmation dialog containing the given message as
    // description and OK/Cancel choices, where 'OK' means that it is okay
    // to proceed with closing the view.  Returns true if the user selects
    // 'OK' or false otherwise.
    virtual bool runModalBeforeUnloadDialog(
        WebFrame*, const WebString& message);


    // UI ------------------------------------------------------------------

    // Called when script modifies window.status
    virtual void setStatusText(const WebString&) ;

    // Called when hovering over an anchor with the given URL.
    virtual void setMouseOverURL(const WebURL&) ;

    // Called when keyboard focus switches to an anchor with the given URL.
    virtual void setKeyboardFocusURL(const WebURL&) ;

    // Shows a context menu with commands relevant to a specific element on
    // the given frame. Additional context data is supplied.
    virtual void showContextMenu(WebFrame*, const WebContextMenuData&) ;

    // Called when the data attached to the currently displayed context menu is
    // invalidated. The context menu may be closed if possible.
    virtual void clearContextMenu() ;

    // Called when a drag-n-drop operation should begin.
    virtual void startDragging(WebFrame*, const WebDragData&, WebDragOperationsMask, const WebImage&, const WebPoint& dragImageOffset) ;

    // Called to determine if drag-n-drop operations may initiate a page
    // navigation.
    virtual bool acceptsLoadDrops() ;

    // Take focus away from the WebView by focusing an adjacent UI element
    // in the containing window.
    virtual void focusNext() ;
    virtual void focusPrevious() ;

    // Called when a new node gets focused.
    virtual void focusedNodeChanged(const WebNode&) ;

    virtual void numberOfWheelEventHandlersChanged(unsigned) ;

    // Indicates two things:
    //   1) This view may have a new layout now.
    //   2) Calling layout() is a no-op.
    // After calling WebWidget::layout(), expect to get this notification
    // unless the view did not need a layout.
    virtual void didUpdateLayout() ;

    // Return true to swallow the input event if the embedder will start a disambiguation popup
    virtual bool didTapMultipleTargets(const WebGestureEvent&, const WebVector<WebRect>& targetRects) ;

    // Returns comma separated list of accept languages.
    virtual WebString acceptLanguages() ;

    // Session history -----------------------------------------------------

    // Tells the embedder to navigate back or forward in session history by
    // the given offset (relative to the current position in session
    // history).
    virtual void navigateBackForwardSoon(int offset) ;

    // Returns the number of history items before/after the current
    // history item.
    virtual int historyBackListCount() ;
    virtual int historyForwardListCount() ;


    // Accessibility -------------------------------------------------------

    // Notifies embedder about an accessibility event.
    virtual void postAccessibilityEvent(const WebAXObject&, WebAXEvent) ;

    // Developer tools -----------------------------------------------------

    // Called to notify the client that the inspector's settings were
    // changed and should be saved.  See WebView::inspectorSettings.
    virtual void didUpdateInspectorSettings() ;

    virtual void didUpdateInspectorSetting(const WebString& key, const WebString& value) ;

    // Geolocation ---------------------------------------------------------

    // Access the embedder API for (client-based) geolocation client .
    virtual WebGeolocationClient* geolocationClient() ;
    // Access the embedder API for (non-client-based) geolocation services.
    virtual WebGeolocationService* geolocationService() ;

    // Speech --------------------------------------------------------------

    // Access the embedder API for speech input services.
    virtual WebSpeechInputController* speechInputController(
        WebSpeechInputListener*);

    // Access the embedder API for speech recognition services.
    virtual WebSpeechRecognizer* speechRecognizer() ;

    // Zoom ----------------------------------------------------------------

    // Informs the browser that the zoom levels for this frame have changed from
    // the default values.
    virtual void zoomLimitsChanged(double minimumLevel, double maximumLevel) ;

    // Informs the browser that the zoom level has changed as a result of an
    // action that wasn't initiated by the client.
    virtual void zoomLevelChanged() ;

    // Registers a new URL handler for the given protocol.
    virtual void registerProtocolHandler(const WebString& scheme,
                                         const WebString& baseUrl,
                                         const WebString& url,
                                         const WebString& title) ;

    // Visibility -----------------------------------------------------------

    // Returns the current visibility of the WebView.
    virtual WebPageVisibilityState visibilityState() const;

    // Media Streams -------------------------------------------------------

    virtual WebUserMediaClient* userMediaClient() ;

    // Web MIDI -------------------------------------------------------------

    virtual WebMIDIClient* webMIDIClient() ;


    // Content detection ----------------------------------------------------

    // Retrieves detectable content (e.g., email addresses, phone numbers)
    // around a hit test result. The embedder should use platform-specific
    // content detectors to analyze the region around the hit test result.
    virtual WebContentDetectionResult detectContentAround(const WebHitTestResult&);

    // Schedules a new content intent with the provided url.
    virtual void scheduleContentIntent(const WebURL&) ;

    // Cancels any previously scheduled content intents that have not yet launched.
    virtual void cancelScheduledContentIntents() ;

    // Draggable regions ----------------------------------------------------

    // Informs the browser that the draggable regions have been updated.
    virtual void draggableRegionsChanged() ;

private:

};



#endif // 
