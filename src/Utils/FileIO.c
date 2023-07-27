#include "Utils/Utils.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "Utils/stb_image.h"

void* Utils_ReadFile(char *filePath) {
    char *buffer;

    FILE *fp = fopen(filePath, "rb");

    if (fp) {
        fseek(fp, 0, SEEK_END);
        long fileByteLength = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buffer = malloc(fileByteLength);
        fread(buffer, 1, fileByteLength, fp);

        fclose(fp);
        return buffer;
    }

    return NULL;
}

void* Utils_ReadFileTerminated(char *filePath) {
    char *buffer;

    FILE *fp = fopen(filePath, "rb");

    if (fp) {
        fseek(fp, 0, SEEK_END);
        long fileByteLength = ftell(fp);
        fseek(fp, 0, SEEK_SET);

        buffer = malloc(fileByteLength + 1);
        fread(buffer, 1, fileByteLength, fp);
        buffer[fileByteLength] = '\0';

        fclose(fp);
        return buffer;
    }

    return NULL;
}

uint32_t Utils_CRC32(const void *data, size_t data_length) {
    // initial value
    uint32_t crc = 0xFFFFFFFF;
    const uint32_t polynomial = 0x04C11DB7;
    
    for (size_t i = 0; i < data_length; i++) {
        crc ^= (((uint8_t*) data)[i]) << 24;

        // essentially using demorgans law to postpone the XOR with the next byte until we get there
        for (size_t j = 0; j < 8; j++) {
            if (crc & (1 << 31))
                crc = (crc << 1) ^ polynomial;
            else
                crc = (crc << 1);
        }
    }

    //invert at the end
    return ~crc;
}

Image Utils_LoadImage(const char *filePath) {
    Image image;
    unsigned char *data = stbi_load("container.jpg", &image.width, &image.height, &image.nrChannels, 0); 
    image.data = data;

    return image;
}