#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "lib/zstd.h"
#include "common.h"

const char* PATH = "e:\\txt.zst";

int decompress(char *input_buffer, size_t input_buffer_size) {
    size_t decompressed_size;
    size_t zstd_ret;
    char *output_buffer;
    
    // output buffer
    decompressed_size = ZSTD_getDecompressedSize(input_buffer, input_buffer_size);
    output_buffer = (char*) malloc(decompressed_size);

    // decompress
    int t1 = clock();
    zstd_ret = ZSTD_decompress(output_buffer, decompressed_size,
                               input_buffer, input_buffer_size);
    int t2 = clock();

    printf("time: %d\n", t2-t1);
    
    free(output_buffer);
    return 0;
}


int main(int argc, const char** argv)
{
    char *input_buffer;
    size_t input_buffer_size;

    // read file
    input_buffer = (char*) mallocAndLoadFile_orDie(PATH, &input_buffer_size);
    printf("read %zd bytes.\n", input_buffer_size);

    // decompress
    decompress(input_buffer, input_buffer_size);

    free(input_buffer);
}
