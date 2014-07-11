
#ifndef WebThemeEngineImpl_h
#define WebThemeEngineImpl_h

#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "../../platform/WebNonCopyable.h"
#include "../../platform/win/WebThemeEngine.h"
using namespace blink;

class WebThemeEngineImpl 
    : public blink::WebThemeEngine
    , public blink::WebNonCopyable
{
public:
    WebThemeEngineImpl();
    virtual ~WebThemeEngineImpl();

    // WebThemeEngine methods:
    virtual void paintButton(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&);

    virtual void paintMenuList(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&);

    virtual void paintScrollbarArrow(
        blink::WebCanvas*, int state, int classicState,
        const blink::WebRect&);

    virtual void paintScrollbarThumb(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&);

    virtual void paintScrollbarTrack(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&, const blink::WebRect& alignRect);

    virtual void paintSpinButton(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&);

    virtual void paintTextField(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&, blink::WebColor, bool fillContentArea,
        bool drawEdges);

    virtual void paintTrackbar(
        blink::WebCanvas*, int part, int state, int classicState,
        const blink::WebRect&);

    virtual void paintProgressBar(
        blink::WebCanvas*, const blink::WebRect& barRect,
        const blink::WebRect& valueRect,
        bool determinate, double time);

    virtual blink::WebSize getSize(int part);
};


#endif // 
