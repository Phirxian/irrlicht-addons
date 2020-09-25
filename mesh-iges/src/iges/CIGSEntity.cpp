#include "CIGSEntity.h"

namespace irr
{
    namespace scene
    {
        void IgsEntity::updateIrrInfo()
        {
            // http://www.wiz-worx.com/iges5x/misc/de13.shtml
            switch(color)
            {
                /* index 0 actually represents an undefined color */
                case 0:
                    irrColor.set(255, rand()%255, rand()%255, rand()%255);
                break;
                case 1:
                    irrColor.set(255, 0, 0, 0);
                break;
                case 2:
                    irrColor.set(255, 255, 0, 0);
                break;
                case 3:
                    irrColor.set(255, 0, 255, 0);
                break;
                case 4:
                    irrColor.set(255, 0, 0, 255);
                break;
                case 5:
                    irrColor.set(255, 255, 255, 0);
                break;
                case 6:
                    irrColor.set(255, 255, 0, 255);
                break;
                case 7:
                    irrColor.set(255, 0, 255, 255);
                break;
                case 8:
                    irrColor.set(255, 255, 255, 255);
                break;
                default:
                    irrColor.set(255, 0, 0, 0);
                break;
            }
        }
    }
}
