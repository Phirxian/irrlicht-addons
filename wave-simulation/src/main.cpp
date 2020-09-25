#include "window.h"

/* original source
    void ComputeVerticalDerivative()
    {
        for(int ix=6;ix<iwidth-6;ix++)
        {
            for(int iy=6;iy<iheight-6;iy++)
            {
                int index = ix + iwidth*iy;
                float vd = 0;

                for(int iix=-6;iix<=6;iix++)
                {
                    for(int iiy=-6;iiy<=6;iiy++)
                    {
                        int iindex = ix+iix + iwidth*(iy+iiy);
                        vd += kernel[iix+6][iiy+6] * height[iindex];
                    }
                }

                vertical_derivative[index] = vd;
            }
        }
    }

    void Propagate()
    {
        for( int i=0;i<size;i++ )
            height[i] *= obstruction[i];

        ComputeVerticalDerivative();

        float adt = alpha*dt;
        float adt2 = 1.0/(1.0+adt);

        for( int i=0;i<size;i++ )
        {
            float temp = height[i];
            height[i] = height[i]*(2.0-adt)-
                        previous_height[i]-
                        gravity*vertical_derivative[i];
            height[i] *= adt2;
            height[i] += source[i];
            height[i] *= obstruction[i];
            previous_height[i] = temp;
            // reset source each step
            source[i] = 0;
        }
    }
*/

int main()
{
    Window viewer;
    viewer.run();
    return 0;
}
