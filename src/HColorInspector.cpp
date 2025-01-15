
#ifndef HColorInspector_IMPLEMENTATION
#define HColorInspector_IMPLEMENTATION

#include "HImage.cpp"

namespace HColorInspector
{
    struct ColorInspector
    {
        int x = 0;
        int y = 0;
        u_long prevColor = 0;
        int stepCounter = 0; // always gets incremented and then is reset when over the threashold.
        int sameCounter = 0; // only gets incremented when the color is the same on the frame. Is reset when the pixed changes.
        int sameThreshold = 0; 

        ColorInspector(int x, int y, int treshold)
        {
            this->x = x;
            this->y = y;
            this->sameThreshold = treshold;
        }

        bool Update()
        {
            u_long newColor;
            HImage::GetPixelColor(newColor, x, y);
            stepCounter++;
            if (stepCounter > sameThreshold) stepCounter = 0;
            if (newColor == prevColor)
            {
                sameCounter++;
            }
            else
            {
                sameCounter = 0;
                prevColor = newColor;
            }
            return sameCounter > sameThreshold;
        }

        void Reset()
        {
            prevColor = 0;
            sameCounter = 0;
            stepCounter = 0;
        }
    };
} // namespace ColorInspector

#endif