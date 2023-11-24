#include <fmt/chrono.h>
#include <fmt/format.h>

#include "CLI/CLI.hpp"
#include "config.h"
#include <iostream>

#include "BMP.h"

auto main(int argc, char **argv) -> int
{
    std::string filename(DEFAULT_BMP_FILE);

    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.add_option("-f,--file", filename, fmt::format("Create a vector with the given size default: {}", filename));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}!\n", app.get_name());
    fmt::print("The filename to use {}\n", filename);

    BMP bmp;
    bmp.read(filename);


    const std::string ascii = " .:-=+*#%@";


    for (int i = 0; i < bmp.infoHeader.imageHeight; i++){
        for (int j = 0; j < bmp.infoHeader.imageWidth, j++){

            int index = static_cast<int>((bmp.imageData[i*j]/255))*(ascii.size()-1);
            fmt::print("{}",ascii[index]);

        }
        fmt::print("\n");
    }
    


    for (int i = 0; i < bmp.fileHeader.fileSize; ++i) {
        //pixel* currentPixel = reinterpret_cast<pixel*>(&bmp.imageData[i * sizeof(pixel)]);
        //std::cout << "Pixel " << i << ": R=" << (int)currentPixel->red << ", G=" << (int)currentPixel->green << ", B=" << (int)currentPixel->blue << std::endl;
        fmt::println("datenpunkt {}", bmp.imageData[i]);
    }

    return 0; /* exit gracefully*/
}
