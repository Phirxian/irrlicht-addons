#ifndef IRR_WINDOW
#define IRR_WINDOW

#include <irrlicht.h>

namespace irr
{
    namespace scene
    {
        class CGridSceneNode;
    }
}

class Window : public irr::IEventReceiver
{
    public:
        Window() noexcept;
        virtual ~Window() noexcept;

        virtual bool OnEvent(const irr::SEvent &ev) noexcept;

        virtual void run() noexcept;
    private:
        bool renderAabbox;
    private:
        irr::IrrlichtDevice *device;
        irr::video::IVideoDriver* driver;
        irr::gui::IGUIEnvironment *guienv;
        irr::scene::ISceneManager *smgr;
        irr::io::IFileSystem *filesys;

        irr::gui::IGUIFileOpenDialog *file;
        irr::scene::CGridSceneNode *gridSceneNode;

        irr::scene::IMesh *Igs[4];
        irr::scene::IAnimatedMesh *loaded;

        irr::video::SMaterial mat[5];
};

#endif
