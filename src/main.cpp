#include <iostream>
#include <libzap.h>
#include <savedds.h>
#include <stb_image_write.h>

//#define USE_PNG

std::string strip_extension(const std::string &filename)
{
    size_t lastIndex = filename.find_last_of('.');
    return filename.substr(0, lastIndex);
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: zap2dds" << " <input_file> [output_file]" << std::endl;
        return 1;
    }

    std::string input_file = argv[1];
#ifdef USE_PNG
    std::string output_file = argc > 2 ? argv[2] : strip_extension(input_file) + ".png";
#else
    std::string output_file = argc > 2 ? argv[2] : strip_extension(input_file) + ".dds";
#endif

    unsigned char* data = nullptr;
    size_t size = 0;

    int width = 0;
    int height = 0;

    zap_error_t err = zap_load(input_file.c_str(), ZAP_COLOR_FORMAT_RGBA32, &data, &size, &width, &height);
    if(err != ZAP_ERROR_NONE)
    {
        std::cerr << "Failed to load file: " << input_file << std::endl;
        return 1;
    }

    if (data)
    {
#ifdef USE_PNG
        stbi_write_png(output_file.c_str(), width, height, 4, data, width * 4);
#else
        savedds(output_file.c_str(), data, width, height, 32);
#endif
        zap_free(data);

        std::cout << "Saved to: " << output_file << std::endl;
    }
    else
    {
        std::cerr << "Failed to load file: " << input_file << std::endl;
        return 1;
    }
    return 0;
}
