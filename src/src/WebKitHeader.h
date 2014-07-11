
#ifndef WebKitHeader_h
#define WebKitHeader_h




#include "base/at_exit.h"
#include "base/base_paths.h"
#include "base/file_util.h"
#include "base/files/file_path.h"
#include "base/path_service.h"
#include "base/command_line.h"
#include "base/rand_util.h"
#include "base/bind.h"
#include "base/debug/trace_event.h"

#include "base/message_loop/message_loop.h"
#include "base/memory/weak_ptr.h"
#include "base/metrics/histogram.h"
#include "base/metrics/sparse_histogram.h"
#include "base/timer/timer.h"
#include "base/metrics/stats_counters.h"

#pragma comment(lib, "base.lib")

#include <url/url_util.h>
#pragma comment(lib, "url_lib.lib")

#include "../../web/WebKit.h"
#include "../../web/webview.h"
#include "../../web/WebFrame.h"
#include "../../web/webviewclient.h"
#include "../../web/WebFrameClient.h"
#include "../../web/WebRuntimeFeatures.h"

#include "../../platform/win/WebThemeEngine.h"
#include "../../platform/WebNonCopyable.h"
#include "../../platform/WebRect.h"
#include "../../platform/WebSize.h"

#pragma comment(lib, "webkit.lib")
#pragma comment(lib, "blink_platform.lib")
#pragma comment(lib, "blink_common.lib")

#include "base/i18n/icu_util.h"
#pragma comment(lib, "base_i18n.lib")

#include "net/base/data_url.h"
#include "net/base/mime_util.h"
#include "net/base/net_errors.h"
#pragma comment(lib, "net.lib")


#include "skia/ext/platform_canvas.h"
#include "third_party/skia/include/core/SkRect.h"
#pragma comment(lib, "skia.lib")

using namespace blink;

#endif // 
