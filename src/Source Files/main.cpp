#include <iostream>

int main() {
    FILE* file;
    file = fopen("file.txt", "wb");

    int numPixels = 0;
    int fileSize = 54 + numPixels * 4;

    fwrite("BM", sizeof("BM"), 1, file);
    fwrite(&fileSize, sizeof(fileSize), 1, file);


    fclose(file);
    return 0;
}
