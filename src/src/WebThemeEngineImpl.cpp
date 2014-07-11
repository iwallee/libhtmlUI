

#include "WebThemeEngineImpl.h"


#include "../../platform/WebCommon.h"
#include "WebThemeControlImpl.h"
#include "third_party/skia/include/core/SkRect.h"
#include "../../platform/WebRect.h"

// Although all this code is generic, we include these headers
// to pull in the Windows #defines for the parts and states of
// the controls.
#include <vsstyle.h>
#include <windows.h>

using namespace blink;


namespace
{

// We define this for clarity, although there really should be a DFCS_NORMAL in winuser.h.
    const int dfcsNormal = 0x0000;

    SkIRect webRectToSkIRect(const WebRect& webRect)
    {
        SkIRect irect;
        irect.set(webRect.x, webRect.y, webRect.x + webRect.width - 1, webRect.y + webRect.height - 1);
        return irect;
    }

    void drawControl(WebCanvas* canvas, const WebRect& rect, WebThemeControlImpl::Type ctype, WebThemeControlImpl::State cstate)
    {
        WebThemeControlImpl control(canvas, webRectToSkIRect(rect), ctype, cstate);
        control.draw();
    }

    void drawTextField(WebCanvas* canvas, const WebRect& rect, WebThemeControlImpl::Type ctype, WebThemeControlImpl::State cstate, bool drawEdges, bool fillContentArea, WebColor color)
    {
        WebThemeControlImpl control(canvas, webRectToSkIRect(rect), ctype, cstate);
        control.drawTextField(drawEdges, fillContentArea, color);
    }

    void drawProgressBar(WebCanvas* canvas, WebThemeControlImpl::Type ctype, WebThemeControlImpl::State cstate, const WebRect& barRect, const WebRect& fillRect)
    {
        WebThemeControlImpl control(canvas, webRectToSkIRect(barRect), ctype, cstate);
        control.drawProgressBar(webRectToSkIRect(fillRect));
    }

}
WebThemeEngineImpl::WebThemeEngineImpl()
{

}
WebThemeEngineImpl::~WebThemeEngineImpl()
{

}
void WebThemeEngineImpl::paintButton(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    if (part == BP_CHECKBOX) {
        switch (state) {
        case CBS_UNCHECKEDNORMAL:
            BLINK_ASSERT(classicState == dfcsNormal);
            ctype = WebThemeControlImpl::UncheckedBoxType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case CBS_UNCHECKEDHOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_HOT));
            ctype = WebThemeControlImpl::UncheckedBoxType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case CBS_UNCHECKEDPRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_PUSHED));
            ctype = WebThemeControlImpl::UncheckedBoxType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case CBS_UNCHECKEDDISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::UncheckedBoxType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case CBS_CHECKEDNORMAL:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_CHECKED));
            ctype = WebThemeControlImpl::CheckedBoxType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case CBS_CHECKEDHOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_CHECKED | DFCS_HOT));
            ctype = WebThemeControlImpl::CheckedBoxType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case CBS_CHECKEDPRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_CHECKED | DFCS_PUSHED));
            ctype = WebThemeControlImpl::CheckedBoxType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case CBS_CHECKEDDISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_CHECKED | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::CheckedBoxType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case CBS_MIXEDNORMAL:
            // Classic theme can't represent mixed state checkbox. We assume
            // it's equivalent to unchecked.
            BLINK_ASSERT(classicState == DFCS_BUTTONCHECK);
            ctype = WebThemeControlImpl::IndeterminateCheckboxType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case CBS_MIXEDHOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_HOT));
            ctype = WebThemeControlImpl::IndeterminateCheckboxType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case CBS_MIXEDPRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_PUSHED));
            ctype = WebThemeControlImpl::IndeterminateCheckboxType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case CBS_MIXEDDISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONCHECK | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::IndeterminateCheckboxType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else if (BP_RADIOBUTTON == part) {
        switch (state) {
        case RBS_UNCHECKEDNORMAL:
            BLINK_ASSERT(classicState == DFCS_BUTTONRADIO);
            ctype = WebThemeControlImpl::UncheckedRadioType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case RBS_UNCHECKEDHOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_HOT));
            ctype = WebThemeControlImpl::UncheckedRadioType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case RBS_UNCHECKEDPRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_PUSHED));
            ctype = WebThemeControlImpl::UncheckedRadioType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case RBS_UNCHECKEDDISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::UncheckedRadioType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case RBS_CHECKEDNORMAL:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_CHECKED));
            ctype = WebThemeControlImpl::CheckedRadioType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case RBS_CHECKEDHOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_CHECKED | DFCS_HOT));
            ctype = WebThemeControlImpl::CheckedRadioType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case RBS_CHECKEDPRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_CHECKED | DFCS_PUSHED));
            ctype = WebThemeControlImpl::CheckedRadioType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case RBS_CHECKEDDISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONRADIO | DFCS_CHECKED | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::CheckedRadioType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else if (BP_PUSHBUTTON == part) {
        switch (state) {
        case PBS_NORMAL:
            BLINK_ASSERT(classicState == DFCS_BUTTONPUSH);
            ctype = WebThemeControlImpl::PushButtonType;
            cstate = WebThemeControlImpl::NormalState;
            break;

        case PBS_HOT:
            BLINK_ASSERT(classicState == (DFCS_BUTTONPUSH | DFCS_HOT));
            ctype = WebThemeControlImpl::PushButtonType;
            cstate = WebThemeControlImpl::HotState;
            break;

        case PBS_PRESSED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONPUSH | DFCS_PUSHED));
            ctype = WebThemeControlImpl::PushButtonType;
            cstate = WebThemeControlImpl::PressedState;
            break;

        case PBS_DISABLED:
            BLINK_ASSERT(classicState == (DFCS_BUTTONPUSH | DFCS_INACTIVE));
            ctype = WebThemeControlImpl::PushButtonType;
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case PBS_DEFAULTED:
            BLINK_ASSERT(classicState == DFCS_BUTTONPUSH);
            ctype = WebThemeControlImpl::PushButtonType;
            cstate = WebThemeControlImpl::FocusedState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else if (BP_COMMANDLINKGLYPH == part){

    } else
        BLINK_ASSERT_NOT_REACHED();

    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintMenuList(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    if (CP_DROPDOWNBUTTON == part) {
        ctype = WebThemeControlImpl::DropDownButtonType;
        switch (state) {
        case CBXS_NORMAL:
            BLINK_ASSERT(classicState == DFCS_MENUARROW);
            cstate = WebThemeControlImpl::NormalState;
            break;

        case CBXS_HOT:
            BLINK_ASSERT(classicState == (DFCS_MENUARROW | DFCS_HOT));
            cstate = WebThemeControlImpl::HoverState;
            break;

        case CBXS_PRESSED:
            BLINK_ASSERT(classicState == (DFCS_MENUARROW | DFCS_PUSHED));
            cstate = WebThemeControlImpl::PressedState;
            break;

        case CBXS_DISABLED:
            BLINK_ASSERT(classicState == (DFCS_MENUARROW | DFCS_INACTIVE));
            cstate = WebThemeControlImpl::DisabledState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else
        BLINK_ASSERT_NOT_REACHED();

    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintScrollbarArrow(WebCanvas* canvas, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    switch (state) {
    case ABS_UPNORMAL:
        BLINK_ASSERT(classicState == DFCS_SCROLLUP);
        ctype = WebThemeControlImpl::UpArrowType;
        cstate = WebThemeControlImpl::NormalState;
        break;

    case ABS_DOWNNORMAL:
        BLINK_ASSERT(classicState == DFCS_SCROLLDOWN);
        ctype = WebThemeControlImpl::DownArrowType;
        cstate = WebThemeControlImpl::NormalState;
        break;

    case ABS_LEFTNORMAL:
        BLINK_ASSERT(classicState == DFCS_SCROLLLEFT);
        ctype = WebThemeControlImpl::LeftArrowType;
        cstate = WebThemeControlImpl::NormalState;
        break;

    case ABS_RIGHTNORMAL:
        BLINK_ASSERT(classicState == DFCS_SCROLLRIGHT);
        ctype = WebThemeControlImpl::RightArrowType;
        cstate = WebThemeControlImpl::NormalState;
        break;

    case ABS_UPHOT:
        BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_HOT));
        ctype = WebThemeControlImpl::UpArrowType;
        cstate = WebThemeControlImpl::HotState;
        break;

    case ABS_DOWNHOT:
        BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_HOT));
        ctype = WebThemeControlImpl::DownArrowType;
        cstate = WebThemeControlImpl::HotState;
        break;

    case ABS_LEFTHOT:
        BLINK_ASSERT(classicState == (DFCS_SCROLLLEFT | DFCS_HOT));
        ctype = WebThemeControlImpl::LeftArrowType;
        cstate = WebThemeControlImpl::HotState;
        break;

    case ABS_RIGHTHOT:
        BLINK_ASSERT(classicState == (DFCS_SCROLLRIGHT | DFCS_HOT));
        ctype = WebThemeControlImpl::RightArrowType;
        cstate = WebThemeControlImpl::HotState;
        break;

    case ABS_UPHOVER:
        BLINK_ASSERT(classicState == DFCS_SCROLLUP);
        ctype = WebThemeControlImpl::UpArrowType;
        cstate = WebThemeControlImpl::HoverState;
        break;

    case ABS_DOWNHOVER:
        BLINK_ASSERT(classicState == DFCS_SCROLLDOWN);
        ctype = WebThemeControlImpl::DownArrowType;
        cstate = WebThemeControlImpl::HoverState;
        break;

    case ABS_LEFTHOVER:
        BLINK_ASSERT(classicState == DFCS_SCROLLLEFT);
        ctype = WebThemeControlImpl::LeftArrowType;
        cstate = WebThemeControlImpl::HoverState;
        break;

    case ABS_RIGHTHOVER:
        BLINK_ASSERT(classicState == DFCS_SCROLLRIGHT);
        ctype = WebThemeControlImpl::RightArrowType;
        cstate = WebThemeControlImpl::HoverState;
        break;

    case ABS_UPPRESSED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_PUSHED | DFCS_FLAT));
        ctype = WebThemeControlImpl::UpArrowType;
        cstate = WebThemeControlImpl::PressedState;
        break;

    case ABS_DOWNPRESSED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_PUSHED | DFCS_FLAT));
        ctype = WebThemeControlImpl::DownArrowType;
        cstate = WebThemeControlImpl::PressedState;
        break;

    case ABS_LEFTPRESSED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLLEFT | DFCS_PUSHED | DFCS_FLAT));
        ctype = WebThemeControlImpl::LeftArrowType;
        cstate = WebThemeControlImpl::PressedState;
        break;

    case ABS_RIGHTPRESSED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLRIGHT | DFCS_PUSHED | DFCS_FLAT));
        ctype = WebThemeControlImpl::RightArrowType;
        cstate = WebThemeControlImpl::PressedState;
        break;

    case ABS_UPDISABLED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_INACTIVE));
        ctype = WebThemeControlImpl::UpArrowType;
        cstate = WebThemeControlImpl::DisabledState;
        break;

    case ABS_DOWNDISABLED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_INACTIVE));
        ctype = WebThemeControlImpl::DownArrowType;
        cstate = WebThemeControlImpl::DisabledState;
        break;

    case ABS_LEFTDISABLED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLLEFT | DFCS_INACTIVE));
        ctype = WebThemeControlImpl::LeftArrowType;
        cstate = WebThemeControlImpl::DisabledState;
        break;

    case ABS_RIGHTDISABLED:
        BLINK_ASSERT(classicState == (DFCS_SCROLLRIGHT | DFCS_INACTIVE));
        ctype = WebThemeControlImpl::RightArrowType;
        cstate = WebThemeControlImpl::DisabledState;
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintScrollbarThumb(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    switch (part) {
    case SBP_THUMBBTNHORZ:
        ctype = WebThemeControlImpl::HorizontalScrollThumbType;
        break;

    case SBP_THUMBBTNVERT:
        ctype = WebThemeControlImpl::VerticalScrollThumbType;
        break;

    case SBP_GRIPPERHORZ:
        ctype = WebThemeControlImpl::HorizontalScrollGripType;
        break;

    case SBP_GRIPPERVERT:
        ctype = WebThemeControlImpl::VerticalScrollGripType;
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    switch (state) {
    case SCRBS_NORMAL:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::NormalState;
        break;

    case SCRBS_HOT:
        BLINK_ASSERT(classicState == DFCS_HOT);
        cstate = WebThemeControlImpl::HotState;
        break;

    case SCRBS_HOVER:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::HoverState;
        break;

    case SCRBS_PRESSED:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::PressedState;
        break;

    case SCRBS_DISABLED:
        BLINK_ASSERT_NOT_REACHED(); // This should never happen in practice.
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintScrollbarTrack(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect, const WebRect& alignRect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    switch (part) {
    case SBP_UPPERTRACKHORZ:
        ctype = WebThemeControlImpl::HorizontalScrollTrackBackType;
        break;

    case SBP_LOWERTRACKHORZ:
        ctype = WebThemeControlImpl::HorizontalScrollTrackForwardType;
        break;

    case SBP_UPPERTRACKVERT:
        ctype = WebThemeControlImpl::VerticalScrollTrackBackType;
        break;

    case SBP_LOWERTRACKVERT:
        ctype = WebThemeControlImpl::VerticalScrollTrackForwardType;
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    switch (state) {
    case SCRBS_NORMAL:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::NormalState;
        break;

    case SCRBS_HOT:
        BLINK_ASSERT_NOT_REACHED(); // This should never happen in practice.
        break;

    case SCRBS_HOVER:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::HoverState;
        break;

    case SCRBS_PRESSED:
        BLINK_ASSERT_NOT_REACHED(); // This should never happen in practice.
        break;

    case SCRBS_DISABLED:
        BLINK_ASSERT(classicState == DFCS_INACTIVE);
        cstate = WebThemeControlImpl::DisabledState;
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintSpinButton(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    if (part == SPNP_UP) {
        ctype = WebThemeControlImpl::UpArrowType;
        switch (state) {
        case UPS_NORMAL:
            BLINK_ASSERT(classicState == DFCS_SCROLLUP);
            cstate = WebThemeControlImpl::NormalState;
            break;
        case UPS_DISABLED:
            BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_INACTIVE));
            cstate = WebThemeControlImpl::DisabledState;
            break;
        case UPS_PRESSED:
            BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_PUSHED));
            cstate = WebThemeControlImpl::PressedState;
            break;
        case UPS_HOT:
            BLINK_ASSERT(classicState == (DFCS_SCROLLUP | DFCS_HOT));
            cstate = WebThemeControlImpl::HoverState;
            break;
        default:
            BLINK_ASSERT_NOT_REACHED();
        }
    } else if (part == SPNP_DOWN) {
        ctype = WebThemeControlImpl::DownArrowType;
        switch (state) {
        case DNS_NORMAL:
            BLINK_ASSERT(classicState == DFCS_SCROLLDOWN);
            cstate = WebThemeControlImpl::NormalState;
            break;
        case DNS_DISABLED:
            BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_INACTIVE));
            cstate = WebThemeControlImpl::DisabledState;
            break;
        case DNS_PRESSED:
            BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_PUSHED));
            cstate = WebThemeControlImpl::PressedState;
            break;
        case DNS_HOT:
            BLINK_ASSERT(classicState == (DFCS_SCROLLDOWN | DFCS_HOT));
            cstate = WebThemeControlImpl::HoverState;
            break;
        default:
            BLINK_ASSERT_NOT_REACHED();
        }
    } else
        BLINK_ASSERT_NOT_REACHED();
    drawControl(canvas, rect, ctype, cstate);
}

void WebThemeEngineImpl::paintTextField(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect, WebColor color, bool fillContentArea, bool drawEdges)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    BLINK_ASSERT(EP_EDITTEXT == part);
    ctype = WebThemeControlImpl::TextFieldType;

    switch (state) {
    case ETS_NORMAL:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::NormalState;
        break;

    case ETS_HOT:
        BLINK_ASSERT(classicState == DFCS_HOT);
        cstate = WebThemeControlImpl::HotState;
        break;

    case ETS_DISABLED:
        BLINK_ASSERT(classicState == DFCS_INACTIVE);
        cstate = WebThemeControlImpl::DisabledState;
        break;

    case ETS_SELECTED:
        BLINK_ASSERT(classicState == DFCS_PUSHED);
        cstate = WebThemeControlImpl::PressedState;
        break;

    case ETS_FOCUSED:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::FocusedState;
        break;

    case ETS_READONLY:
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::ReadOnlyState;
        break;

    default:
        BLINK_ASSERT_NOT_REACHED();
        break;
    }

    drawTextField(canvas, rect, ctype, cstate, drawEdges, fillContentArea, color);
}

void WebThemeEngineImpl::paintTrackbar(WebCanvas* canvas, int part, int state, int classicState, const WebRect& rect)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::UnknownType;
    WebThemeControlImpl::State cstate = WebThemeControlImpl::UnknownState;

    if (TKP_THUMBBOTTOM == part) {
        ctype = WebThemeControlImpl::HorizontalSliderThumbType;
        switch (state) {
        case TUS_NORMAL:
            BLINK_ASSERT(classicState == dfcsNormal);
            cstate = WebThemeControlImpl::NormalState;
            break;

        case TUS_HOT:
            BLINK_ASSERT(classicState == DFCS_HOT);
            cstate = WebThemeControlImpl::HotState;
            break;

        case TUS_DISABLED:
            BLINK_ASSERT(classicState == DFCS_INACTIVE);
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case TUS_PRESSED:
            BLINK_ASSERT(classicState == DFCS_PUSHED);
            cstate = WebThemeControlImpl::PressedState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else if (TKP_THUMBVERT == part) {
        ctype = WebThemeControlImpl::VerticalSliderThumbType;
        switch (state) {
        case TUS_NORMAL:
            BLINK_ASSERT(classicState == dfcsNormal);
            cstate = WebThemeControlImpl::NormalState;
            break;

        case TUS_HOT:
            BLINK_ASSERT(classicState == DFCS_HOT);
            cstate = WebThemeControlImpl::HotState;
            break;

        case TUS_DISABLED:
            BLINK_ASSERT(classicState == DFCS_INACTIVE);
            cstate = WebThemeControlImpl::DisabledState;
            break;

        case TUS_PRESSED:
            BLINK_ASSERT(classicState == DFCS_PUSHED);
            cstate = WebThemeControlImpl::PressedState;
            break;

        default:
            BLINK_ASSERT_NOT_REACHED();
            break;
        }
    } else if (TKP_TRACK == part) {
        ctype = WebThemeControlImpl::HorizontalSliderTrackType;
        BLINK_ASSERT(state == TRS_NORMAL);
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::NormalState;
    } else if (TKP_TRACKVERT == part) {
        ctype = WebThemeControlImpl::VerticalSliderTrackType;
        BLINK_ASSERT(state == TRVS_NORMAL);
        BLINK_ASSERT(classicState == dfcsNormal);
        cstate = WebThemeControlImpl::NormalState;
    } else
        BLINK_ASSERT_NOT_REACHED();

    drawControl(canvas, rect, ctype, cstate);
}


void WebThemeEngineImpl::paintProgressBar(blink::WebCanvas* canvas, const blink::WebRect& barRect, const blink::WebRect& valueRect, bool determinate, double)
{
    WebThemeControlImpl::Type ctype = WebThemeControlImpl::ProgressBarType;
    WebThemeControlImpl::State cstate = determinate ? WebThemeControlImpl::NormalState : WebThemeControlImpl::IndeterminateState;
    drawProgressBar(canvas, ctype, cstate, barRect, valueRect);
}


blink::WebSize WebThemeEngineImpl::getSize(int part)
{
    return blink::WebSize();
}

