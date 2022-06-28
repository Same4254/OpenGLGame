#include "Utils/Utils.h"

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

typedef struct {
	uint32_t width;
	uint32_t height;
	uint8_t bitDepth;
	uint8_t colorType;
	uint8_t compressionType;
	uint8_t filterMethod;
	uint8_t interlaceMethod;
} IHDR_Chunk;

float* Utils_ReadPNG_RGB(char *filePath) {
	void *fileContents = Utils_ReadFileTerminated(filePath);

	if(((uint64_t*) fileContents)[0] != 1196314761) {
		// Error
		printf("Parsing PNG as RGB failed. Magic number is incorrect: %s\n", filePath);
	}

	//Chunk headerChunk;
	
}
