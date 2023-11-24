#ifndef WORKSPACES_TEA21_EXERCISE_004_MY_BMP_H
#define WORKSPACES_TEA21_EXERCISE_004_MY_BMP_H

#include <string>
#include <vector>

struct BMPFILEHEADER {
    uint8_t signature[2]; // "BM" for BMP files
    uint32_t fileSize = 0;  // Size of the BMP file
    uint32_t reserved = 0; 
    uint32_t dataOffset = 0; // Starting address of the byte where the bitmap data can be found
    void print();
};

struct BMPINFOHEADER {
    uint32_t headerSize;      // Size of this header (40 bytes)
    int32_t  imageWidth;      // Width of the bitmap in pixels
    int32_t  imageHeight;     // Height of the bitmap in pixels
    uint16_t colorPlanes;     // Number of color planes (must be 1)
    uint16_t bitsPerPixel;    // Number of bits per pixel (usually 24 for RGB)
    uint32_t compression;     // Compression method being used
    uint32_t imageSize;       // Size of the raw bitmap data
    int32_t  pixelsPerMeterX; // Horizontal resolution (pixels per meter)
    int32_t  pixelsPerMeterY; // Vertical resolution (pixels per meter)
    uint32_t colorsUsed;       // Number of colors in the palette
    uint32_t colorsImportant;  // Number of important colors
    void print();
};

struct pixel {
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t grey () {
        return((pixel::red + pixel::blue + pixel::green)/3);
    }
};

struct BMP {
    bool read(const std::string&  filename);
    bool write(const std::string&  filename);

    BMPFILEHEADER fileHeader;
    BMPINFOHEADER infoHeader;
    std::vector<uint8_t> imageData;
};

#endif