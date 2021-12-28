#include <stdio.h>
#include <unistd.h>

int main(int argc,char* argv[]){
  FILE *file=fopen(argv[1],"a");
  if (file==NULL){
    printf("fopen error\n");
    return -1;
  }

  float result=0;
  float number;
  while (read(fileno(stdin),&number,sizeof(float)) > 0)
    result += number;
  
  fprintf(file,"%f\n",result);
  fclose(file);
  return 0;
}