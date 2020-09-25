#include <irrlicht/irrlicht.h>
#include <iostream>

#include "gameintro.h"

//constexpr static const char *movie = "68781528.ogg";
constexpr static const char *movie = "0001-0048.avi";

int main(void)
{

    irr::IrrlichtDevice * device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2du(900,400));
    irr::video::IVideoDriver * driver = device->getVideoDriver();

    device->getCursorControl()->setVisible(false);

    interne::graphic::GameIntro *intro = new interne::graphic::GameIntro(device,movie,true);
    intro->vi.setLoop(true);

    while(device->run() && intro)
    {

        driver->beginScene(true, true, irr::video::SColor(0,0,0,0));
        if(intro->draw())
        {
            driver->endScene();
            break;
        }
        driver->endScene();
    }

    if(intro) delete intro;
    intro = 0;

    return 0;
}
