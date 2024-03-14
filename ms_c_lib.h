#ifndef MS_C_LIB
#define MS_C_LIB
/*
* M(anuel)'s C lib - a header-only library for common c functions that aren't standard.
* 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * Mstrdup - Duplicates the contents of a string into a new, heap-allocated block
 * @param ptr The string to duplicate
 * @return Null if malloc returns null, else a string (char*)
 *
 */
char* Mstrdup(char* ptr) {
  char* str;
  size_t size = strlen(ptr) + 1; // add one to get the null terminator

  str = malloc(size);
  if (str) {
    memcpy(str, ptr, size);
  }
  return str;
}

char *Mread_line(FILE* fp)
{
  // credit to https://brennan.io/2015/01/16/write-a-shell-in-c/
  int bufsize = 256;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  int c;

  if (!buffer) {
    return NULL;
  }

  while (1) {
    // Read a character
    c = getc(fp);

    // If we hit EOF, replace it with a null character and return.
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    // If we have exceeded the buffer, reallocate.
    if (position >= bufsize) {
      bufsize *= 2;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        return NULL;
      }
    }
  }
}


#endif
