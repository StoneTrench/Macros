#ifndef HImage_IMPLEMENTATION
#define HImage_IMPLEMENTATION

#include <string>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <vector>
#include "libs/base64.cpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "libs/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "libs/stb_image.h"

namespace HImage
{
    enum FORMATS
    {
        PNG,
        BMP,
        JPG,
    };
    struct Image
    {
        uint8_t *data = nullptr; // Pointer to the image data
        size_t data_length = 0;  // Total length of the image data
        int width = 0;           // Image width in pixels
        int height = 0;          // Image height in pixels
        uint8_t channels = 0;    // Number of channels (e.g., 3 for RGB, 4 for RGBA)
    };

    void FreeImage(Image &image)
    {
        delete[] image.data;
        image.data = nullptr;
        image.data_length = 0;
        image.width = 0;
        image.height = 0;
        image.channels = 0;
    }
    void AssignImage(Image &image, int width, int height, uint8_t channels)
    {
        FreeImage(image);
        image.data_length = width * height * channels;
        image.data = new uint8_t[image.data_length];
        image.width = width;
        image.height = height;
        image.channels = channels;
    }
    bool ReadImage(std::string filepath, Image &image)
    {
        int w, h, c;
        stbi_uc *data = stbi_load(filepath.c_str(), &w, &h, &c, 0);
        if (!data)
            return false;

        size_t size = static_cast<size_t>(w) * static_cast<size_t>(h) * static_cast<size_t>(c);

        image.channels = c;
        image.height = h;
        image.width = w;
        image.data = data;
        image.data_length = size;

        return true;
    }
    void WriteImage(std::string filepath, Image &image, FORMATS format)
    {
        int w = image.width;
        int h = image.height;
        int c = image.channels;
        uint8_t *d = image.data;

        switch (format)
        {
        case PNG:
            stbi_write_png(filepath.c_str(), w, h, c, d, w * c);
            break;
        case JPG:
            stbi_write_jpg(filepath.c_str(), w, h, c, d, 90);
            break;
        case BMP:
            stbi_write_bmp(filepath.c_str(), w, h, c, d);
            break;

        default:
            throw "Invalid format!";
        }
    }
    bool ReadBase64(std::string uri, Image &image)
    {
        std::vector<u_char> binary_data = base64::base64_decode(uri);

        int w, h, c;
        stbi_uc *data = stbi_load_from_memory(binary_data.data(), binary_data.size(), &w, &h, &c, 0);
        if (!data)
            return false;

        size_t size = static_cast<size_t>(w) * static_cast<size_t>(h) * static_cast<size_t>(c);

        image.channels = c;
        image.height = h;
        image.width = w;
        image.data = data;
        image.data_length = size;

        return true;
    }
    void CaptureScreen(Image &image)
    {
        // Get screen width and height
        int screenWidth = GetSystemMetrics(SM_CXSCREEN);
        int screenHeight = GetSystemMetrics(SM_CYSCREEN);

        // Create a device context (DC) for screen
        HDC hScreenDC = GetDC(NULL);
        HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

        // Create a bitmap to store the screen content
        HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);
        SelectObject(hMemoryDC, hBitmap);

        // Copy screen content into the bitmap
        BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);

        AssignImage(image, screenWidth, screenHeight, 4);

        GetBitmapBits(hBitmap, image.data_length, image.data);

        for (size_t i = 0; i < image.data_length; i += image.channels)
            std::swap(image.data[i], image.data[i + 2]); // Swap Blue <-> Red

        // Clean up
        DeleteObject(hBitmap);
        DeleteDC(hMemoryDC);
        ReleaseDC(NULL, hScreenDC);
    }
    void CompareImages(
        int &bestX,
        int &bestY,
        int &bestScore,
        Image &screen,
        Image &reference,
        int sparseness,
        int threshold)
    {
        bestScore = MAXINT;
        bestX = -1;
        bestY = -1;

        int size = reference.width * reference.height;

        uint8_t minChannel = std::min(screen.channels, reference.channels);

        // Compare pixels in a sliding window
        for (int y = 0; y <= screen.height - reference.height; ++y)
        {
            for (int x = 0; x <= screen.width - reference.width; ++x)
            {
                double diff = 0;
                for (int j = 0; j < reference.height; j += sparseness)
                {
                    for (int i = 0; i < reference.width; i += sparseness)
                    {
                        int screenIdx = ((y + j) * screen.width + (x + i)) * screen.channels;
                        int refIdx = (j * reference.width + i) * reference.channels;

                        // Compare RGBA values and calculate difference
                        for (int c = 0; c < minChannel; ++c)
                        {
                            int diffValue = screen.data[screenIdx + c] - reference.data[refIdx + c];
                            diff += diffValue * diffValue; // Squared difference for comparison
                        }
                    }
                }

                diff /= size;
                if (diff < bestScore)
                {
                    bestScore = diff;
                    bestX = x;
                    bestY = y;
                    if (diff < threshold)
                    {
                        return;
                    }
                }
            }
        }
    }
    void CropImage(Image &result, Image &image, int dx, int dy, int dw, int dh)
    {

        // Allocate memory for the cropped image
        AssignImage(result, dw, dh, image.channels);

        // Copy pixels from the original image to the cropped image
        for (int i = 0; i < dh; ++i)
        {
            for (int j = 0; j < dw; ++j)
            {
                // Calculate the position in the original image
                int origIndex = ((dy + i) * image.width + (dx + j)) * result.channels;
                int croppedIndex = (i * dw + j) * result.channels;

                // Copy pixel data
                for (int c = 0; c < result.channels; ++c)
                {
                    result.data[croppedIndex + c] = image.data[origIndex + c];
                }
            }
        }
    }

    void GetPixelColor(u_long &color, int x, int y)
    {
        HDC dc = GetDC(NULL);
        color = GetPixel(dc, x, y);
        ReleaseDC(NULL, dc);
    }
    void ConvertColor_ulong_rgba(uint8_t &r, uint8_t &g, uint8_t &b, uint8_t &a, unsigned long color)
    {
        // Extracting RGBA components from the unsigned long color
        a = (color >> 24) & 0xFF; // Extract the alpha byte (most significant byte)
        r = (color >> 16) & 0xFF; // Extract the red byte
        g = (color >> 8) & 0xFF;  // Extract the green byte
        b = color & 0xFF;         // Extract the blue byte (least significant byte)
    }
    void ConvertColor_rgba_ulong(unsigned long &color, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        // Combine RGBA components into a single unsigned long (0xAARRGGBB format)
        color = (static_cast<unsigned long>(a) << 24) |
                (static_cast<unsigned long>(r) << 16) |
                (static_cast<unsigned long>(g) << 8) |
                static_cast<unsigned long>(b);
    }
}

#endif