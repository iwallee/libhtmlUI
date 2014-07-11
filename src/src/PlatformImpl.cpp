#include "PlatformImpl.h"



#include "base/message_loop/message_loop.h"
#include "base/metrics/stats_counters.h"
#include "base/debug/trace_event.h"
#include "base/metrics/histogram.h"
#include "base/metrics/sparse_histogram.h"
#include "base/rand_util.h"
#include "net/base/data_url.h"
#include "net/base/mime_util.h"



PlatformImpl::PlatformImpl()
    : main_loop_(base::MessageLoop::current()),
      shared_timer_func_(NULL),
      shared_timer_fire_time_(0.0),
      shared_timer_fire_time_was_set_while_suspended_(false),
      shared_timer_suspended_(0)
{

}

PlatformImpl::~PlatformImpl()
{
}
// May return null.
WebCookieJar* PlatformImpl::cookieJar()
{
    return 0;
}

// Must return non-null.
WebClipboard* PlatformImpl::clipboard()
{
    return 0;
}

// Must return non-null.
WebFileUtilities* PlatformImpl::fileUtilities()
{
    return 0;
}

// Must return non-null.
WebMimeRegistry* PlatformImpl::mimeRegistry()
{
    return 0;
}

// May return null if sandbox support is not necessary
WebSandboxSupport* PlatformImpl::sandboxSupport()
{
    return 0;
}

// May return null on some platforms.
WebThemeEngine* PlatformImpl::themeEngine()
{
    return &m_themeEngine;
}

WebFallbackThemeEngine* PlatformImpl::fallbackThemeEngine()
{
    return 0;
}

// May return null.
WebSpeechSynthesizer* PlatformImpl::createSpeechSynthesizer(WebSpeechSynthesizerClient*)
{
    return 0;
}


// Media --------------------------------------------------------------

// May return null.
WebContentDecryptionModule* PlatformImpl::createContentDecryptionModule(const WebString& keySystem)
{
    return 0;
}


// Audio --------------------------------------------------------------

double PlatformImpl::audioHardwareSampleRate()
{
    return 0;
}
size_t PlatformImpl::audioHardwareBufferSize()
{
    return 0;
}
unsigned PlatformImpl::audioHardwareOutputChannels()
{
    return 0;
}

// Creates a device for audio I/O.
// Pass in (numberOfInputChannels > 0) if live/local audio input is desired.
WebAudioDevice* PlatformImpl::createAudioDevice(size_t bufferSize, unsigned numberOfInputChannels, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*, const WebString& deviceId)
{
    return 0;
}

// FIXME: remove deprecated APIs once chromium switches over to new method.
WebAudioDevice* PlatformImpl::createAudioDevice(size_t bufferSize, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*)
{
    return 0;
}
WebAudioDevice* PlatformImpl::createAudioDevice(size_t bufferSize, unsigned numberOfInputChannels, unsigned numberOfChannels, double sampleRate, WebAudioDevice::RenderCallback*)
{
    return 0;
}


// MIDI ----------------------------------------------------------------

// Creates a platform dependent WebMIDIAccessor. MIDIAccessor under platform
// creates and owns it.
WebMIDIAccessor* PlatformImpl::createMIDIAccessor(WebMIDIAccessorClient*)
{
    return 0;
}


// Blob ----------------------------------------------------------------

// Must return non-null.
WebBlobRegistry* PlatformImpl::blobRegistry()
{
    return 0;
}


// Database ------------------------------------------------------------

// Opens a database file; dirHandle should be 0 if the caller does not need
// a handle to the directory containing this file
Platform::FileHandle PlatformImpl::databaseOpenFile(const WebString& vfsFileName, int desiredFlags)
{
    return base::kInvalidPlatformFileValue;
}

// Deletes a database file and returns the error code
int PlatformImpl::databaseDeleteFile(const WebString& vfsFileName, bool syncDir)
{
    return -1;
}

// Returns the attributes of the given database file
long PlatformImpl::databaseGetFileAttributes(const WebString& vfsFileName)
{
    return 0;
}

// Returns the size of the given database file
long long PlatformImpl::databaseGetFileSize(const WebString& vfsFileName)
{
    return 0;
}

// Returns the space available for the given origin
long long PlatformImpl::databaseGetSpaceAvailableForOrigin(const blink::WebString& originIdentifier)
{
    return 0;
}


// DOM Storage --------------------------------------------------

// Return a LocalStorage namespace
WebStorageNamespace* PlatformImpl::createLocalStorageNamespace()
{
    return 0;
}


// FileSystem ----------------------------------------------------------

// Must return non-null.
WebFileSystem* PlatformImpl::fileSystem()
{
    return 0;
}


// IDN conversion ------------------------------------------------------

WebString PlatformImpl::convertIDNToUnicode(const WebString& host, const WebString& languages)
{
    return host;
}


// IndexedDB ----------------------------------------------------------

// Must return non-null.
WebIDBFactory* PlatformImpl::idbFactory()
{
    return 0;
}


// Gamepad -------------------------------------------------------------

void PlatformImpl::sampleGamepads(WebGamepads& into)
{
    into.length = 0;
}


// History -------------------------------------------------------------

// Returns the hash for the given canonicalized URL for use in visited
// link coloring.
unsigned long long PlatformImpl::visitedLinkHash(
    const char* canonicalURL, size_t length)
{
    return 0;
}

// Returns whether the given link hash is in the user's history. The
// hash must have been generated by calling VisitedLinkHash().
bool PlatformImpl::isLinkVisited(unsigned long long linkHash)
{
    return false;
}


// Keygen --------------------------------------------------------------

// Handle the <keygen> tag for generating client certificates
// Returns a base64 encoded signed copy of a public key from a newly
// generated key pair and the supplied challenge string. keySizeindex
// specifies the strength of the key.
WebString PlatformImpl::signedPublicKeyAndChallengeString(unsigned keySizeIndex,
        const WebString& challenge,
        const WebURL& url)
{
    return WebString();
}


// Memory --------------------------------------------------------------

// Returns the current space allocated for the pagefile, in MB.
// That is committed size for Windows and memory size for POSIX
size_t PlatformImpl::memoryUsageMB()
{
    return 0;
}

// Same as above, but always returns actual value, without any caches.
size_t PlatformImpl::actualMemoryUsageMB()
{
    return 0;
}

// Return the physical memory of the current machine, in MB.
size_t PlatformImpl::physicalMemoryMB()
{
    return 0;
}

// Return the number of of processors of the current machine.
size_t PlatformImpl::numberOfProcessors()
{
    return 0;
}

// Returns private and shared usage, in bytes. Private bytes is the amount of
// memory currently allocated to this process that cannot be shared. Returns
// false on platform specific error conditions.
bool PlatformImpl::processMemorySizesInBytes(size_t* privateBytes, size_t* sharedBytes)
{
    return false;
}


// Requests private and shared usage, in bytes. Private bytes is the amount of
// memory currently allocated to this process that cannot be shared.
// The callback ownership is passed to the callee.
void PlatformImpl::requestProcessMemorySizes(ProcessMemorySizesCallback* requestCallback) { }

// Reports number of bytes used by memory allocator for internal needs.
// Returns true if the size has been reported, or false otherwise.
bool PlatformImpl::memoryAllocatorWasteInBytes(size_t*)
{
    return false;
}

// Allocates discardable memory. May return 0, even if the platform supports
// discardable memory. If nonzero, however, then the WebDiscardableMmeory is
// returned in an locked state. You may use its underlying data() member
// directly, taking care to unlock it when you are ready to let it become
// discardable.
WebDiscardableMemory* PlatformImpl::allocateAndLockDiscardableMemory(size_t bytes)
{
    return 0;
}

// A wrapper for tcmalloc's HeapProfilerStart();
void PlatformImpl::startHeapProfiling(const WebString& /*prefix*/) { }
// A wrapper for tcmalloc's HeapProfilerStop();
void PlatformImpl::stopHeapProfiling() { }
// A wrapper for tcmalloc's HeapProfilerDump()
void PlatformImpl::dumpHeapProfiling(const WebString& /*reason*/) { }
// A wrapper for tcmalloc's GetHeapProfile()
WebString PlatformImpl::getHeapProfile()
{
    return WebString();
}


// Returns the maximum amount of memory a decoded image should be allowed.
// See comments on ImageDecoder::m_maxDecodedBytes.
size_t PlatformImpl::maxDecodedImageBytes()
{
    return noDecodedImageByteLimit;
}


// Message Ports -------------------------------------------------------

// Creates a Message Port Channel. This can be called on any thread.
// The returned object should only be used on the thread it was created on.
WebMessagePortChannel* PlatformImpl::createMessagePortChannel()
{
    return 0;
}


// Network -------------------------------------------------------------

// Returns a new WebURLLoader instance.
WebURLLoader* PlatformImpl::createURLLoader()
{
    return 0;// new WebURLLoaderImpl(this);
}

// May return null.
WebPrescientNetworking* PlatformImpl::prescientNetworking()
{
    return 0;
}

// Returns a new WebSocketStreamHandle instance.
WebSocketStreamHandle* PlatformImpl::createSocketStreamHandle()
{
    return 0;
}

// Returns a new WebSocketHandle instance.
WebSocketHandle* PlatformImpl::createWebSocketHandle()
{
    return 0;
}

// Returns the User-Agent string that should be used for the given URL.
WebString PlatformImpl::userAgent(const WebURL&)
{
    return WebString();
}

// A suggestion to cache this metadata in association with this URL.
void PlatformImpl::cacheMetadata(const WebURL&, double responseTime, const char* data, size_t dataSize) { }

// Returns the decoded data url if url had a supported mimetype and parsing was successful.
WebData PlatformImpl::parseDataURL(const WebURL& url, WebString& mimetype, WebString& charset)
{
    std::string mime_type, char_set, data;
    if (net::DataURL::Parse(url, &mime_type, &char_set, &data)
            && net::IsSupportedMimeType(mime_type)) {
        mimetype = WebString::fromUTF8(mime_type);
        charset = WebString::fromUTF8(char_set);
        return data;
    }
    return WebData();
}

WebURLError PlatformImpl::cancelledError(const WebURL&) const
{
    return WebURLError();
}


// Plugins -------------------------------------------------------------

// If refresh is true, then cached information should not be used to
// satisfy this call.
void PlatformImpl::getPluginList(bool refresh, WebPluginListBuilder*) { }


// Public Suffix List --------------------------------------------------

// May return null on some platforms.
WebPublicSuffixList* PlatformImpl::publicSuffixList()
{
    return 0;
}


// Resources -----------------------------------------------------------

// Returns a localized string resource (with substitution parameters).
WebString PlatformImpl::queryLocalizedString(WebLocalizedString::Name)
{
    return WebString();
}
WebString PlatformImpl::queryLocalizedString(WebLocalizedString::Name, const WebString& parameter)
{
    return WebString();
}
WebString PlatformImpl::queryLocalizedString(WebLocalizedString::Name, const WebString& parameter1, const WebString& parameter2)
{
    return WebString();
}


// Threads -------------------------------------------------------

// Creates an embedder-defined thread.
WebThread* PlatformImpl::createThread(const char* name)
{
    return 0;
}

// Returns an interface to the current thread. This is owned by the
// embedder.
WebThread* PlatformImpl::currentThread()
{
    return 0;
}


// Profiling -----------------------------------------------------------

void PlatformImpl::decrementStatsCounter(const char* name)
{
    base::StatsCounter(name).Decrement();
}
void PlatformImpl::incrementStatsCounter(const char* name)
{
    base::StatsCounter(name).Increment();
}


// Resources -----------------------------------------------------------

// Returns a blob of data corresponding to the named resource.
WebData PlatformImpl::loadResource(const char* name)
{
    return WebData();
}

// Decodes the in-memory audio file data and returns the linear PCM audio data in the destinationBus.
// A sample-rate conversion to sampleRate will occur if the file data is at a different sample-rate.
// Returns true on success.
bool PlatformImpl::loadAudioResource(WebAudioBus* destinationBus, const char* audioFileData, size_t dataSize, double sampleRate)
{
    return false;
}


// Screen -------------------------------------------------------------

// Supplies the system monitor color profile.
void PlatformImpl::screenColorProfile(WebVector<char>* profile) { }


// Sudden Termination --------------------------------------------------

// Disable/Enable sudden termination.
void PlatformImpl::suddenTerminationChanged(bool enabled) { }


// System --------------------------------------------------------------

// Returns a value such as "en-US".
WebString PlatformImpl::defaultLocale()
{
    return WebString();
}

// Wall clock time in seconds since the epoch.
double PlatformImpl::currentTime()
{
    return 0;
}

// Monotonically increasing time in seconds from an arbitrary fixed point in the past.
// This function is expected to return at least millisecond-precision values. For this reason,
// it is recommended that the fixed point be no further in the past than the epoch.
double PlatformImpl::monotonicallyIncreasingTime()
{
    return base::TimeTicks::Now().ToInternalValue() /
           static_cast<double>(base::Time::kMicrosecondsPerSecond);
}

// WebKit clients must implement this funcion if they use cryptographic randomness.
void PlatformImpl::cryptographicallyRandomValues(unsigned char* buffer, size_t length)
{
    base::RandBytes(buffer, length);
}

// Delayed work is driven by a shared timer.

void PlatformImpl::setSharedTimerFiredFunction(SharedTimerFunction timerFunction)
{
    shared_timer_func_ = timerFunction;
}
void PlatformImpl::setSharedTimerFireInterval(double interval_seconds)
{
    shared_timer_fire_time_ = interval_seconds + monotonicallyIncreasingTime();
    if (shared_timer_suspended_) {
        shared_timer_fire_time_was_set_while_suspended_ = true;
        return;
    }

    // By converting between double and int64 representation, we run the risk
    // of losing precision due to rounding errors. Performing computations in
    // microseconds reduces this risk somewhat. But there still is the potential
    // of us computing a fire time for the timer that is shorter than what we
    // need.
    // As the event loop will check event deadlines prior to actually firing
    // them, there is a risk of needlessly rescheduling events and of
    // needlessly looping if sleep times are too short even by small amounts.
    // This results in measurable performance degradation unless we use ceil() to
    // always round up the sleep times.
    int64 interval = static_cast<int64>(
                         ceil(interval_seconds * base::Time::kMillisecondsPerSecond)
                         * base::Time::kMicrosecondsPerMillisecond);

    if (interval < 0)
        interval = 0;

    shared_timer_.Stop();
    // shared_timer_.Start(FROM_HERE, base::TimeDelta::FromMicroseconds(interval),
    //     this, &WebKitPlatformSupportImpl::DoTimeout);
    //OnStartSharedTimer(base::TimeDelta::FromMicroseconds(interval));
}
void PlatformImpl::stopSharedTimer()
{
    shared_timer_.Stop();
}

// Callable from a background WebKit thread.
void PlatformImpl::callOnMainThread(void(*func)(void*), void* context)
{
    main_loop_->PostTask(FROM_HERE, base::Bind(func, context));
}


// Vibration -----------------------------------------------------------

// Starts a vibration for the given duration in milliseconds. If there is currently an active
// vibration it will be cancelled before the new one is started.
void PlatformImpl::vibrate(unsigned time) { }

// Cancels the current vibration, if there is one.
void PlatformImpl::cancelVibration() { }


// Testing -------------------------------------------------------------

// Get a pointer to testing support interfaces. Will not be available in production builds.
WebUnitTestSupport* PlatformImpl::unitTestSupport()
{
    return 0;
}


// Tracing -------------------------------------------------------------

// Get a pointer to the enabled state of the given trace category. The
// embedder can dynamically change the enabled state as trace event
// recording is started and stopped by the application. Only long-lived
// literal strings should be given as the category name. The implementation
// expects the returned pointer to be held permanently in a local static. If
// the unsigned char is non-zero, tracing is enabled. If tracing is enabled,
// addTraceEvent is expected to be called by the trace event macros.
const unsigned char* PlatformImpl::getTraceCategoryEnabledFlag(const char* categoryName)
{
    static const unsigned char kEnabled = 0;
    return &kEnabled;
}


// Get a pointer to a global state of the given thread. An embedder is
// expected to update the global state as the state of the embedder changes.
// A sampling thread in the Chromium side reads the global state periodically
// and reflects the sampling profiled results into about:tracing.
Platform::TraceEventAPIAtomicWord* PlatformImpl::getTraceSamplingState(const unsigned bucketName)
{
    /* switch (bucketName) {
    case 0:
    return reinterpret_cast<long*>(&TRACE_EVENT_API_THREAD_BUCKET(0));
    case 1:
    return reinterpret_cast<long*>(&TRACE_EVENT_API_THREAD_BUCKET(1));
    case 2:
    return reinterpret_cast<long*>(&TRACE_EVENT_API_THREAD_BUCKET(2));
    default:
    NOTREACHED() << "Unknown thread bucket type.";
    }*/
    return NULL;
}


// Add a trace event to the platform tracing system. Depending on the actual
// enabled state, this event may be recorded or dropped.
// - phase specifies the type of event:
//   - BEGIN ('B'): Marks the beginning of a scoped event.
//   - END ('E'): Marks the end of a scoped event.
//   - COMPLETE ('X'): Marks the beginning of a scoped event, but doesn't
//     need a matching END event. Instead, at the end of the scope,
//     updateTraceEventDuration() must be called with the TraceEventHandle
//     returned from addTraceEvent().
//   - INSTANT ('I'): Standalone, instantaneous event.
//   - START ('S'): Marks the beginning of an asynchronous event (the end
//     event can occur in a different scope or thread). The id parameter is
//     used to match START/FINISH pairs.
//   - FINISH ('F'): Marks the end of an asynchronous event.
//   - COUNTER ('C'): Used to trace integer quantities that change over
//     time. The argument values are expected to be of type int.
//   - METADATA ('M'): Reserved for internal use.
// - categoryEnabled is the pointer returned by getTraceCategoryEnabledFlag.
// - name is the name of the event. Also used to match BEGIN/END and
//   START/FINISH pairs.
// - id optionally allows events of the same name to be distinguished from
//   each other. For example, to trace the consutruction and destruction of
//   objects, specify the pointer as the id parameter.
// - numArgs specifies the number of elements in argNames, argTypes, and
//   argValues.
// - argNames is the array of argument names. Use long-lived literal strings
//   or specify the COPY flag.
// - argTypes is the array of argument types:
//   - BOOL (1): bool
//   - UINT (2): unsigned long long
//   - INT (3): long long
//   - DOUBLE (4): double
//   - POINTER (5): void*
//   - STRING (6): char* (long-lived null-terminated char* string)
//   - COPY_STRING (7): char* (temporary null-terminated char* string)
// - argValues is the array of argument values. Each value is the unsigned
//   long long member of a union of all supported types.
// - thresholdBeginId optionally specifies the value returned by a previous
//   call to addTraceEvent with a BEGIN phase.
// - threshold is used on an END phase event in conjunction with the
//   thresholdBeginId of a prior BEGIN event. The threshold is the minimum
//   number of microseconds that must have passed since the BEGIN event. If
//   less than threshold microseconds has passed, the BEGIN/END pair is
//   dropped.
// - flags can be 0 or one or more of the following, ORed together:
//   - COPY (0x1): treat all strings (name, argNames and argValues of type
//     string) as temporary so that they will be copied by addTraceEvent.
//   - HAS_ID (0x2): use the id argument to uniquely identify the event for
//     matching with other events of the same name.
//   - MANGLE_ID (0x4): specify this flag if the id parameter is the value
//     of a pointer.
Platform::TraceEventHandle PlatformImpl::addTraceEvent(
    char phase,
    const unsigned char* categoryEnabledFlag,
    const char* name,
    unsigned long long id,
    int numArgs,
    const char** argNames,
    const unsigned char* argTypes,
    const unsigned long long* argValues,
    unsigned char flags)
{
    base::debug::TraceEventHandle handle = TRACE_EVENT_API_ADD_TRACE_EVENT(
            phase, categoryEnabledFlag, name, id,
            numArgs, argNames, argTypes, argValues, NULL, flags);
    blink::Platform::TraceEventHandle result;
    memcpy(&result, &handle, sizeof(result));
    return result;
}

// Set the duration field of a COMPLETE trace event.
void PlatformImpl::updateTraceEventDuration(const unsigned char* categoryEnabledFlag, const char* name, TraceEventHandle handle)
{
    base::debug::TraceEventHandle traceEventHandle;
    memcpy(&traceEventHandle, &handle, sizeof(handle));
    TRACE_EVENT_API_UPDATE_TRACE_EVENT_DURATION(
        categoryEnabledFlag, name, traceEventHandle);
}

// Callbacks for reporting histogram data.
// CustomCounts histogram has exponential bucket sizes, so that min=1, max=1000000, bucketCount=50 would do.
void PlatformImpl::histogramCustomCounts(const char* name, int sample, int min, int max, int bucketCount)
{
    // Copied from histogram macro, but without the static variable caching
    // the histogram because name is dynamic.
    base::HistogramBase* counter =
        base::Histogram::FactoryGet(name, min, max, bucketCount,
                                    base::HistogramBase::kUmaTargetedHistogramFlag);
    DCHECK_EQ(name, counter->histogram_name());
    counter->Add(sample);
}
// Enumeration histogram buckets are linear, boundaryValue should be larger than any possible sample value.
void PlatformImpl::histogramEnumeration(const char* name, int sample, int boundaryValue)
{
    // Copied from histogram macro, but without the static variable caching
    // the histogram because name is dynamic.
    base::HistogramBase* counter =
        base::LinearHistogram::FactoryGet(name, 1, boundaryValue,
                                          boundaryValue + 1, base::HistogramBase::kUmaTargetedHistogramFlag);
    DCHECK_EQ(name, counter->histogram_name());
    counter->Add(sample);
}
// Unlike enumeration histograms, sparse histograms only allocate memory for non-empty buckets.
void PlatformImpl::histogramSparse(const char* name, int sample)
{
    // For sparse histograms, we can use the macro, as it does not incorporate a
    // static.
    UMA_HISTOGRAM_SPARSE_SLOWLY(name, sample);
}


// GPU ----------------------------------------------------------------
//
// May return null if GPU is not supported.
// Returns newly allocated and initialized offscreen WebGraphicsContext3D instance.
WebGraphicsContext3D* PlatformImpl::createOffscreenGraphicsContext3D(const WebGraphicsContext3D::Attributes&)
{
    return 0;
}

// Returns a newly allocated and initialized offscreen context provider. The provider may return a null
// graphics context if GPU is not supported.
WebGraphicsContext3DProvider* PlatformImpl::createSharedOffscreenGraphicsContext3DProvider()
{
    return 0;
}

// Returns true if the platform is capable of producing an offscreen context suitable for accelerating 2d canvas.
// This will return false if the platform cannot promise that contexts will be preserved across operations like
// locking the screen or if the platform cannot provide a context with suitable performance characteristics.
//
// This value must be checked again after a context loss event as the platform's capabilities may have changed.
bool PlatformImpl::canAccelerate2dCanvas()
{
    return false;
}

bool PlatformImpl::isThreadedCompositingEnabled()
{
    return false;
}

WebCompositorSupport* PlatformImpl::compositorSupport()
{
    return 0;
}

WebFlingAnimator* PlatformImpl::createFlingAnimator()
{
    return 0;
}

// Creates a new fling animation curve instance for device |deviceSource|
// with |velocity| and already scrolled |cumulativeScroll| pixels.
WebGestureCurve* PlatformImpl::createFlingAnimationCurve(int deviceSource, const WebFloatPoint& velocity, const WebSize& cumulativeScroll)
{
    return 0;
}


// WebRTC ----------------------------------------------------------

// Creates an WebRTCPeerConnectionHandler for RTCPeerConnection.
// May return null if WebRTC functionality is not avaliable or out of resources.
WebRTCPeerConnectionHandler* PlatformImpl::createRTCPeerConnectionHandler(WebRTCPeerConnectionHandlerClient*)
{
    return 0;
}

// May return null if WebRTC functionality is not avaliable or out of resources.
WebMediaStreamCenter* PlatformImpl::createMediaStreamCenter(WebMediaStreamCenterClient*)
{
    return 0;
}


// WebWorker ----------------------------------------------------------

void PlatformImpl::didStartWorkerRunLoop(const WebWorkerRunLoop&) { }
void PlatformImpl::didStopWorkerRunLoop(const WebWorkerRunLoop&) { }


// WebCrypto ----------------------------------------------------------

WebCrypto* PlatformImpl::crypto()
{
    return 0;
}


// Device Motion / Orientation ----------------------------------------

// Sets a Listener to listen for device motion data updates.
// If null, the platform stops providing device motion data to the current listener.
void PlatformImpl::setDeviceMotionListener(blink::WebDeviceMotionListener*) { }

// Sets a Listener to listen for device orientation data updates.
// If null, the platform stops proving device orientation data to the current listener.
void PlatformImpl::setDeviceOrientationListener(blink::WebDeviceOrientationListener*) { }


// Quota -----------------------------------------------------------

// Queries the storage partition's storage usage and quota information.
// WebStorageQuotaCallbacks::didQueryStorageUsageAndQuota will be called
// with the current usage and quota information for the partition. When
// an error occurs WebStorageQuotaCallbacks::didFail is called with an
// error code.
// The callbacks object is deleted when the callback method is called
// and does not need to be (and should not be) deleted manually.
void PlatformImpl::queryStorageUsageAndQuota(
    const WebURL& storagePartition,
    WebStorageQuotaType,
    WebStorageQuotaCallbacks*) { }


// WebDatabase --------------------------------------------------------

WebDatabaseObserver* PlatformImpl::databaseObserver()
{
    return 0;
}

