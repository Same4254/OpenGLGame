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