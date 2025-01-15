
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
        int sameCounter = 0;
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
        }
    };
} // namespace ColorInspector

#endif