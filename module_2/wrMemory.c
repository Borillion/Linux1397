#include <stdio.h>
#include <stdlib.h>

int main()
{
  char *input_buffer;
  char output_char;
  size_t size;

  FILE *fp, *fp1;

  printf("This program works with memory, a driver that copies a\n");
  printf("string from linux user space into a dynamically allocated\n");
  printf("section of memory withing the linux kernel space and back\n");
 
  // Open the memory device and write user input
  fp = fopen ("/dev/memory", "w");
  if(fp == NULL){
    perror("fopen(): ");
    return(-1);
  }
  //prompt for user input
  printf("Please enter a string to process: ");
  fflush(stdin);
  getline(&input_buffer, &size, stdin);
  printf("\nUser Input was:\n");
  printf("%s", input_buffer);
  fprintf(fp, "%s", input_buffer);
  fclose(fp);
 

  fp1 = fopen ("/dev/memory", "r");
  if(fp1 == NULL){
    perror("fopen(): ");
    return(-1);
  }
  printf("\nString retrieved from kernel memory space:\n");
  fflush(stdin);
  while ((output_char = fgetc(fp1)) != EOF) { 
    printf("%c",output_char); 
  }

  fclose(fp1);  
  
  return(0);
}

