#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file_disemvowel.h"


// char *disemvowel(char *str) {
//   int non_vowels = 0;
//   int length = strlen(str);
//   for (int i=0; i<length; i++) {
//     if (!is_vowel(str[i])) {
//       non_vowels++;
//     }
//   }
//   char *result = (char*) calloc(non_vowels+1, sizeof(char));
//   int j = 0;
//   for (int i=0; i<length; i++) {
//     if (!is_vowel(str[i])) {
//       if (result != NULL) {
//         result[j] = str[i];
//       }
//       j++;
//     }
//   }
//   if (result != NULL) {
//     result[non_vowels] = '\0';
//   }
  
//   return result;
// }

#include <stdio.h>
#include <stdbool.h>

#define BUF_SIZE 1024

bool is_vowel(char vowel) {
  return (
    vowel == 'a' || vowel == 'A' ||
    vowel == 'e' || vowel == 'E' ||
    vowel == 'i' || vowel == 'I' ||
    vowel == 'o' || vowel == 'O' ||
    vowel == 'u' || vowel == 'U'
  );
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

    
    while((num_chars = fread(in_buff, sizeof(char), BUF_SIZE, inputFile)) > 0 ){ // read in some lines of text, chack that something came in
      int num_consonants = copy_non_vowels(num_chars, in_buff, out_buff); // find num of consonants to copy over
      
      size_t written = 0; // keep track of consonants written
      while(written < num_consonants){ // write consonants out
        fwrite(out_buff+written, sizeof(char), num_consonants - written, outputFile);
        written++ ; // to out_buff or outputFile;
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

    // Code that processes the command line arguments
    // and sets up inputFile and outputFile.
    if(argc >= 2){
      inputFile = (FILE *) argv[2];
    }
    if(argc >= 3){
      outputFile = (FILE *) argv[3];
    }
    
    disemvowel(inputFile, outputFile);

    return 0;
}