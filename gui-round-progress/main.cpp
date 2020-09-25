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
#include "CGUIRoundProgress.h"
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
	IrrlichtDevice * device = createDevice(video::EDT_OPENGL, core::dimension2d<u32>(155, 80));

	device->setWindowCaption(L"Irrlicht Engine - User Interface Demo");
	device->setResizable(true);

	video::IVideoDriver* driver = device->getVideoDriver();
	IGUIEnvironment* env = device->getGUIEnvironment();

	IGUISkin* skin = env->getSkin();
	IGUIFont* font = env->getFont("fonthaettenschweiler.bmp");
	skin->setFont(font, EGDF_DEFAULT);

	/**********************************************/

	CGUIRoundProgress *test = new CGUIRoundProgress(env, env->getRootGUIElement(), {5, 5, 75, 75});
	test->setBackgroundTexture(driver->getTexture("round-progress-bg.png"));
	test->setForegroundTexture(driver->getTexture("round-progress-fg.png"));
    test->setRotation(-90.f);
    test->setProgress(0.66f);

	auto txt = env->addStaticText(L"66", {5, 5, 65, 65}, false, true, test);
	txt->setOverrideColor({255, 255, 255, 255});
	txt->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	txt->setDrawBorder(false);

	/**********************************************/

	CGUIRoundProgress *test2 = new CGUIRoundProgress(env, env->getRootGUIElement(), {80, 5, 150, 75});
	test2->setBackgroundTexture(driver->getTexture("flat-progress-bg.png"));
	test2->setForegroundTexture(driver->getTexture("flat-progress-fg.png"));
    test2->setRotation(-90.f);
    test2->setProgress(0.66f);

	auto txt2 = env->addStaticText(L"66", {5, 5, 65, 65}, false, true, test2);
	txt2->setOverrideColor({255, 255, 255, 255});
	txt2->setTextAlignment(EGUIA_CENTER, EGUIA_CENTER);
	txt2->setDrawBorder(false);

	/**********************************************/

	while(device->run())
	{
        if(device->isWindowActive())
        {
            driver->beginScene(true, true, SColor(0,0,50,50));
            env->drawAll();
            driver->endScene();

            {
                int progress = device->getTimer()->getTime()%2000;

                if(progress >= 1000)
                    progress = 2000-progress;

                irr::core::stringw tmp(progress/10);
                test->setProgress(progress/1000.f);
                test->setRotation(device->getTimer()->getTime()/10.f);
                txt->setText(tmp.c_str());

                test2->setProgress(progress/1000.f);
                test2->setRotation(device->getTimer()->getTime()/10.f);
                txt2->setText(tmp.c_str());
            }
        }
	}

	device->drop();

	return 0;
}

/*
**/
