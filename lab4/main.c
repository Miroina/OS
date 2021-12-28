#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    if (argc != 3){
        printf("Syntax: ./*executable_file_name* Test_file Result_file\n");
        return -1;
    }

    FILE *test_file=fopen(argv[1],"r");
    if (test_file == NULL){
        printf("fopen main error\n");
        return -1;
    }

    char* result_file = argv[2];
    int size = 0;
    char c;
    char *input_string = (char *)calloc(1, sizeof(char));
    
    while (!feof(test_file)) {
        c = getc(test_file);
        input_string[size] = c;
        input_string = (char *)realloc(input_string,(++size + 1) * sizeof(char));
    }

    int file_descriptor = shm_open("lab4.back", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (file_descriptor == -1) {
        printf("shm_open main error\n");
        return -1;
    }

    if (ftruncate(file_descriptor, (off_t)size) == -1) {
        printf("ftruncate error\n");
        return -1;
    }

    caddr_t memory = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, file_descriptor, 0);
    if (memory == MAP_FAILED) {
        printf("mmap main error\n");
        return -1;
    }

    sprintf(memory,"%s",input_string);
    free(input_string);

    int identifier = fork();
    if (identifier == -1) {
        printf("fork error\n");
        return -1;
    } else if (identifier == 0) {
        munmap(memory,size);
        close(file_descriptor);

        char* argv1[3] = {"child",result_file,(char *)NULL};
        if (execv("child",argv1) == -1) {
            printf("execv error\n");
            return -1;
        }
    }
    return 0;
}