#include "zip_api_wdm.h"
#include "error_wdm.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <zlib.h>

bool compressFileToZip(const char* source, const char* dest) {
    std::ifstream inFile(source, std::ios::binary);
    std::ofstream outFile(dest, std::ios::binary);
    

    if (!inFile || !outFile) {
        std::cerr << "File open error!" << std::endl;
        return false;
    }

    std::vector<char> buffer((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    uint32_t sourceLen = buffer.size();
    uint32_t destLen = sourceLen;
    // std::vector<Bytef> compressedData(destLen);

    // int result = compress(compressedData.data(), (ulong*)&destLen, reinterpret_cast<Bytef*>(buffer.data()), sourceLen);
    // if (result != Z_OK) {
    //     std::cerr << "Compression error: " << result << std::endl;
    //     return false;
    // }

    // Write ZIP file header
    outFile.write("PK\3\4", 4); // Local file header signature
    outFile.put(10); outFile.put(0); // Version needed to extract
    outFile.put(0); outFile.put(0); // General purpose bit flag
    outFile.put(0); outFile.put(0); // Compression method (deflate)
    outFile.put(0); outFile.put(0); // File last modification time
    outFile.put(0); outFile.put(0); // File last modification date
    uint32_t crc32Val = 0x9236DA01;
    outFile.write(reinterpret_cast<char*>(&crc32Val), 4);// crc32校验码
    outFile.write(reinterpret_cast<char*>(&destLen), 4); // 18 Compressed size
    outFile.write(reinterpret_cast<char*>(&sourceLen), 4); // 22 Uncompressed size
    char fileName[] = "input.txt";
    outFile.put(uint32_t(sizeof(fileName) - 1)); outFile.put(0); // 26 File name length
    outFile.put(0); outFile.put(0); // Extra field length

    // Write 文件名
    outFile.write(reinterpret_cast<char*>(fileName), sizeof(fileName) - 1);
    // Write compressed data
    outFile.write(reinterpret_cast<char*>(buffer.data()), destLen);

    // Write ZIP file footer
    outFile.write("PK\1\2", 4); // Central directory file header signature
    outFile.put(0); outFile.put(0); // Version made by
    outFile.put(10); outFile.put(0); // Version needed to extract
    outFile.put(0); outFile.put(0); // General purpose bit flag
    outFile.put(8); outFile.put(0); // Compression method (deflate)
    outFile.put(0); outFile.put(0); // File last modification time
    outFile.put(0); outFile.put(0); // File last modification date
    outFile.write(reinterpret_cast<char*>(&destLen), 4); // Compressed size
    outFile.write(reinterpret_cast<char*>(&sourceLen), 4); // Uncompressed size
    outFile.put(uint32_t(sizeof(fileName) - 1)); outFile.put(0); // File name length
    outFile.put(0); outFile.put(0); // Extra field length
    outFile.put(0); outFile.put(0); // File comment length
    outFile.put(0); outFile.put(0); // Disk number start
    outFile.put(0); outFile.put(0); // Internal file attributes
    outFile.put(0); outFile.put(0); // External file attributes
    outFile.put(0); outFile.put(0); // Relative offset of local header
    outFile.write(reinterpret_cast<char*>(fileName), sizeof(fileName) - 1);

    outFile.write("PK\5\6", 4); // 0 End of central directory signature
    outFile.put(0); outFile.put(0); // 4 Number of this disk
    outFile.put(0); outFile.put(0); // 6 Disk where central directory starts
    outFile.put(1); outFile.put(0); // 8 Number of central directory records on this disk
    outFile.put(1); outFile.put(0); // 10 Total number of central directory records
    uint32_t centSize = 46 + sizeof(fileName) - 1; // Size of central directory
    outFile.write(reinterpret_cast<char*>(&centSize), 4); // 12 Size of central directory
    uint32_t offset = 30 + sizeof(fileName) - 1 + destLen; // Offset
    outFile.write(reinterpret_cast<char*>(&offset), 4); // 16 Offset of start of central directory
    outFile.put(0); outFile.put(0); // 20 Comment length

    return true;
}

void ZipTest()
{
    const char* sourceFile = "./testfile/input.txt";
    const char* destFile = "./testfile/output.zip";

    if (compressFileToZip(sourceFile, destFile)) {
        std::cout << "File compressed to ZIP successfully!" << std::endl;
    } else {
        std::cerr << "File compression to ZIP failed!" << std::endl;
    }
    return;
}