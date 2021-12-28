#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
  if (argc != 3){
    printf("Syntax: ./*executable_file_name* Test_file Result_file\n");
    return -1;
  }

  FILE *test_file=fopen(argv[1],"r");
  char* result_file = argv[2];
  int file_descriptors[2];

  while (!feof(test_file)){
    if (pipe(file_descriptors) == -1) {
      printf("Pipe error\n");
      return -1;
    }

    int id = fork();
    if (id == -1) {
      printf("Fork error\n");
      return -1;
    } else if (id == 0) {
      close (file_descriptors[1]);
      if (dup2(file_descriptors[0],fileno(stdin)) == -1) {
        printf("Dup2 error\n");
        return -1;
      }
      char* argv1[3] = {"child",result_file, (char *)NULL};
      if (execv("child",argv1) == -1)
        printf("Execl error\n");
    } else {
      close(file_descriptors[0]);
      float number;
      char end_of_line = ' ';
      while (end_of_line == ' '){
        fscanf(test_file,"%f",&number);
        if(write(file_descriptors[1],&number,sizeof(float)) == 0) {
          printf("Write error\n");
          return -1;
        }
        end_of_line = getc(test_file);
      }
      number =0;
      close(file_descriptors[1]);
    }
  }
  fclose(test_file);
  return 0;
}