#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char* argv[]) {
    FILE *file = fopen(argv[1],"a");
    if (file == NULL){
        printf("fopen error\n");
        return -1;
    }

    int file_descriptor = shm_open("lab4.back", O_RDONLY, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (file_descriptor == -1) {
        printf("shm_open error\n");
        return -1;
    }

    struct stat status_buffer;
    fstat(file_descriptor,&status_buffer);
    int size = status_buffer.st_size;

    caddr_t memory = mmap(NULL, size, PROT_READ, MAP_SHARED, file_descriptor, 0);
    if (memory == MAP_FAILED) {
        printf("mmap error\n");
        return -1;
    }
    
    float result = 0;
    char* number = (char *)calloc(1, sizeof(char));
    int count = 0;

    for (int i=0; i<size; i++) {
        if (memory[i] == ' ') {
            result += atof(number);
            free(number);
            number = (char *)calloc(1, sizeof(char));
            count = 0;
        }
        if ((memory[i] == '\0') || (memory[i] == '\n')) { 
            if (count != 0) {
                result += atof(number);
                fprintf (file, "%f\n",result);
            }
            free(number);
            number = (char *)calloc(1, sizeof(char));
            count = 0;
            result = 0;
        }
        if ((memory[i] == '0') || (memory[i] == '1') || (memory[i] == '2') || (memory[i] == '3') || 
            (memory[i] == '4') || (memory[i] == '5') || (memory[i] == '6') || (memory[i] == '7') || (memory[i] == '8') || 
            (memory[i] == '9') || (memory[i] == '.') || (memory[i] == '-')) {
            number[count] = memory[i];
            number = (char *)realloc(number,(++count + 1) * sizeof(char));
        }
    }

    free(number);
    fclose(file);
    return 0;
}