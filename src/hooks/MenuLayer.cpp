#include <hooks/MenuLayer.hpp>

#ifdef WIN32
bool __fastcall Hooks::MenuLayer::init(CCLayer* self, int)
#endif
#ifdef ANDROID
    bool Hooks::MenuLayer::init(CCLayer* self, int)
#endif
{
    bool ret = init_O(self);

    auto root = self->getChildren();

    CCLabelBMFont* splash = CCLabelBMFont::create("BoolkaSDK!", "goldFont.fnt");

    auto winSize = CCDirector::sharedDirector()->getWinSize();
    self->addChild(splash, 2);
    splash->setPosition({winSize.width / 2 + 140, winSize.height / 2 + 90});

    return ret;
}