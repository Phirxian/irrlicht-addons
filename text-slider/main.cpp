/** Example 005 User Interface

This tutorial shows how to use the built in User Interface of
the Irrlicht Engine. It will give a brief overview and show
how to create and use windows, buttons, scroll bars, static
texts, and list boxes.

As always, we include the header files, and use the irrlicht
namespaces. We also store a pointer to the Irrlicht device,
a counter variable for changing the creation position of a window,
and a pointer to a listbox.
*/
#include <irrlicht.h>
#include "CGUITextSlider.h"
#include "driverChoice.h"

using namespace irr;

using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _MSC_VER
#pragma comment(lib, "Irrlicht.lib")
#endif

int main()
{
	IrrlichtDevice * device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(200, 90));

	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	video::IVideoDriver *driver = device->getVideoDriver();
	IGUIEnvironment *env = device->getGUIEnvironment();
    IGUISpriteBank *sprites = env->getSkin()->getSpriteBank();

	CGUITextSlider *test = new CGUITextSlider(env, env->getRootGUIElement(), {5, 5, 195, 20});
	test->addItem(L"item 1");
	test->addItem(L"item 2");
	test->addItem(L"item 3");
	test->addItem(L"item 4");
	test->setSelected(0);
	test->setButtonSize(15);
	test->getPrevButton()->setSpriteBank(sprites);
	test->getNextButton()->setSpriteBank(sprites);
  test->getNextButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_RIGHT), {255, 0, 0, 0});
  test->getPrevButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_LEFT), {255, 0, 0, 0});
	test->getStaticText()->setOverrideColor({255, 255, 255, 255});

	CGUITextSlider *test2 = new CGUITextSlider(env, env->getRootGUIElement(), {5, 35, 80, 85});
	test2->addItem(L"item 1");
	test2->addItem(L"item 2");
	test2->addItem(L"item 3");
	test2->addItem(L"item 4");
	test2->setSelected(0);
	test2->setMode(ETSM_VERTICAL);
	test2->setButtonSize(15);
	test2->getPrevButton()->setSpriteBank(sprites);
	test2->getNextButton()->setSpriteBank(sprites);
    test2->getNextButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_DOWN), {255, 0, 0, 0});
    test2->getPrevButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_UP), {255, 0, 0, 0});
	test2->getStaticText()->setOverrideColor({255, 255, 255, 255});

	CGUITextSlider *test3 = new CGUITextSlider(env, env->getRootGUIElement(), {115, 35, 195, 85});
	test3->addItem(L"item 1");
	test3->addItem(L"item 2");
	test3->addItem(L"item 3");
	test3->addItem(L"item 4");
	test3->setSelected(0);
	test3->setMode(ETSM_VERTICAL);
	test3->setButtonSize(15);
	test3->getPrevButton()->setSpriteBank(sprites);
	test3->getNextButton()->setSpriteBank(sprites);
  test3->getNextButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_DOWN), {255, 0, 0, 0});
  test3->getPrevButton()->setSprite(irr::gui::EGBS_BUTTON_UP, env->getSkin()->getIcon(irr::gui::EGDI_CURSOR_UP), {255, 0, 0, 0});
	test3->getStaticText()->setOverrideColor({255, 255, 255, 255});

	while(device->run())
	{
        if(device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,0,50,50));
            env->drawAll();
            driver->endScene();
        }
	}

	device->drop();

	return 0;
}

/*
**/
