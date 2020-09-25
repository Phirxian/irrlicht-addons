#ifndef IRR_WINDOW
#define IRR_WINDOW

#include "datacomputation.h"
#include "flowmap.h"

class Window : public irr::IEventReceiver, public irr::video::IShaderConstantSetCallBack
{
    public:
        Window() noexcept;
        virtual ~Window() noexcept;

        virtual void OnSetConstants(irr::video::IMaterialRendererServices* services, irr::s32 userData) noexcept;

        virtual bool OnEvent(const irr::SEvent &ev) noexcept;

        virtual void run() noexcept;
    private:
        irr::video::E_MATERIAL_TYPE buildShader(irr::video::E_MATERIAL_TYPE);
        DataComputation *cmp;
        FlowMap *map;
    private:
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver* driver;
        irr::gui::IGUIEnvironment *guienv;
        irr::scene::ISceneManager *smgr;
        irr::scene::ISceneNode *water;
        irr::scene::ISceneNode *floor;
        irr::io::IFileSystem *filesys;
    private:
        bool cursor[2], restart[2];
        irr::core::line2di line[2];
        irr::core::dimension2df size;
        float scaling;
};

#endif
