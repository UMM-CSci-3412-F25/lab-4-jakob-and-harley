#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "file_disemvowel.h"

#define BUF_SIZE 1024

bool is_vowel(char vowel) {
  return (vowel == 'a' || vowel == 'A' || vowel == 'e' || vowel == 'E' || vowel == 'i' || vowel == 'I' || vowel == 'o' || vowel == 'O' || vowel == 'u' || vowel == 'U');
}

int copy_non_vowels(int num_chars, char* in_buf, char* out_buf) {
    /*
     * Copy all the non-vowels from in_buf to out_buf.
     * num_chars indicates how many characters are in in_buf,
     * and this function should return the number of non-vowels that
     * that were copied over.
     */

  int j = 0;
  for (int i=0; i<num_chars; i++) {
    if (!is_vowel(in_buf[i])) {
      out_buf[j]=in_buf[i];
      j++;
    }
  }

  return j;
}

void disemvowel(FILE* inputFile, FILE* outputFile) {
    /*
     * Copy all the non-vowels from inputFile to outputFile.
     * Create input and output buffers, and use fread() to repeatedly read
     * in a buffer of data, copy the non-vowels to the output buffer, and
     * use fwrite to write that out.
     */
    char in_buff[BUF_SIZE];
    char out_buff[BUF_SIZE];

    // call fread()
    size_t num_chars; // temp  = fread(in_buff, sizeof(char), BUF_SIZE, inputFile);
    
    while((num_chars = fread(in_buff, sizeof(char), BUF_SIZE, inputFile)) > 0 ){ // read in some lines of text, check that something came in
      
      // printf("read %ld units\n", num_chars);

      int num_consonants = copy_non_vowels(num_chars, in_buff, out_buff); // find num of consonants to copy over
      
      size_t written = 0; // keep track of consonants written

      // printf("finished copying non-vowels, moving to nested for loop\n");

      while(written < num_consonants){ // write consonants out
        // printf("inside nested while loop\n");
        written += fwrite(out_buff+written, sizeof(char), num_consonants - written, outputFile);
      }
    }
    
    return;

}

int main(int argc, char *argv[]) {
    // This sets these to `stdin` and `stdout` by default.
    // You then need to set them to user specified files when the user
    // provides files names as command line arguments.
    FILE *inputFile = stdin;
    FILE *outputFile = stdout;

    // printf("In main, set up default values\n");

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.
    if(argc >= 2){
      // inputFile = (FILE *) argv[2];
      inputFile = fopen(argv[1], "r");
      if (inputFile == NULL) {
        printf("ERROR\n");
        return 1;
      }
      // printf("set default value\n");
    }
      if(argc >= 3){
      //outputFile = (FILE *) argv[3];
      outputFile = fopen(argv[2], "w");
      if (outputFile == NULL) {
        printf("ERROR\n");
        return 1;
      }
    }

    disemvowel(inputFile, outputFile);

    fclose(outputFile);
    fclose(inputFile);

    return 0;
}