#ifdef GEODE_IS_WINDOWS

#include <windows.h>
#include <dwmapi.h>
#include <Geode/loader/Mod.hpp>

using namespace geode;
using namespace cocos2d;

void updateTitlebar(bool darkMode) {
    HWND hwnd = WindowFromDC(wglGetCurrentDC());
    BOOL dark = darkMode ? TRUE : FALSE;
    DwmSetWindowAttribute(hwnd, 20, &dark, sizeof(dark));
}

#include <Geode/modify/CCEGLView.hpp>
class $modify(CCEGLView) {

    void setupWindow(CCRect rect) {
        CCEGLView::setupWindow(rect);
        updateTitlebar(Mod::get()->getSettingValue<bool>("dark-mode"));
    }

};

$on_mod(Loaded) {
    listenForSettingChanges<bool>("dark-mode", [](bool darkMode) {
        updateTitlebar(darkMode);
    });
}

#endif