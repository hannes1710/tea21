#include "BMP.h"
#include <iostream>
#include <fstream>
#include <fmt/format.h>

template<typename T>
static void read_value(std::fstream& file, T* value){
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

void BMPFILEHEADER::print(){
    fmt::println("Signatur: {}{}", signature[0], signature[1]);
    fmt::println("fileSize: {}", fileSize);
    fmt::println("reserved: {}", reserved);
    fmt::println("dataOffset: {}", dataOffset);    
}

void BMPINFOHEADER::print(){
    fmt::println("headerSize: {}", headerSize);    
    fmt::println("imageWidth: {}", imageWidth);    
    fmt::println("imageHeight: {}", imageHeight);    
    fmt::println("colorPlanes: {}", colorPlanes);    
    fmt::println("bitsPerPixel: {}", bitsPerPixel);    
    fmt::println("compression: {}", compression);    
    fmt::println("imageSize: {}", imageSize);    
    fmt::println("pixelsPerMeterX: {}", pixelsPerMeterX);    
    fmt::println("pixelsPerMeterY: {}", pixelsPerMeterY);    
    fmt::println("colorsUsed: {}", colorsUsed);    
    fmt::println("colorsImportant: {}", colorsImportant);    

}

bool BMP::read(const std::string& filename) {
    
    std::fstream file(filename, std::ios::binary | std::ios::in);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;
    }


    read_value(file, &fileHeader.signature);
    read_value(file, &fileHeader.fileSize);
    read_value(file, &fileHeader.reserved);
    read_value(file, &fileHeader.dataOffset);
    read_value(file, &infoHeader.headerSize);
    read_value(file, &infoHeader.imageWidth);
    read_value(file, &infoHeader.imageHeight);
    read_value(file, &infoHeader.colorPlanes);
    read_value(file, &infoHeader.bitsPerPixel);
    read_value(file, &infoHeader.compression);
    read_value(file, &infoHeader.imageSize);
    read_value(file, &infoHeader.pixelsPerMeterX);
    read_value(file, &infoHeader.pixelsPerMeterY);
    read_value(file, &infoHeader.colorsUsed);
    read_value(file, &infoHeader.colorsImportant);
    fileHeader.print();
    infoHeader.print();

    // Read image data
    imageData.resize(infoHeader.imageSize);
    file.seekg(fileHeader.dataOffset, std::ios::beg);
    file.read(reinterpret_cast<char*>(imageData.data()), infoHeader.imageSize);

    std::vector<pixel> rgbVector;  // Hier werden die RGB-Tripel gespeichert

    for (int i = 0; i < infoHeader.imageSize; i += 3) {
        pixel currentPixel;

        // Annahme: Die Reihenfolge der Farbkomponenten im imageData ist R, G, B.
        currentPixel.red = imageData[i];
        currentPixel.green = imageData[i + 1];
        currentPixel.blue = imageData[i + 2];

        rgbVector.push_back(currentPixel);
    }


    file.close();
    return true;
}















bool BMP::write(const std::string& filename) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return false;
    }

    // Write file header and info header
    file.write(reinterpret_cast<char*>(&fileHeader), sizeof(BMPFILEHEADER));
    file.write(reinterpret_cast<char*>(&infoHeader), sizeof(BMPINFOHEADER));

    // Write image data
    file.write(reinterpret_cast<char*>(imageData.data()), infoHeader.imageSize);

    file.close();
    return true;
}



