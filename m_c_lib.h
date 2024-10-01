#ifndef M_C_LIB
#define M_C_LIB
/*
* Manuel's C lib - a header-only library for common c functions that aren't standard.
* 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

/*
 * Mstrdup - Duplicates the contents of a string into a new, heap-allocated block
 * @param ptr The string to duplicate
 * @return Null if malloc returns null, else a string (char*)
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

/*
 * Mread_line - Reads a line (aka up to a newline or EOF) from the given FILE pointer. Automatically allocates memory for the string. Replaces the EOF or newline
 *  with a null terminator.
 * @param fp The file pointer to read from.
 * @return A heap-allocated, null-terminated string 
 */ 
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

/* Concactenates all of the passed in strings by automatically allocating memory. 
 * @param str One or more strings to concactenate
 * @return A heap-allocated, null-terminated string.
 */
char* Mstrcat(const char* str, ...)
{
	va_list args;
	va_start(args, str);
	if (str == NULL)
	{
		return NULL;
	}
	size_t current_size = strlen(str);
	char *result = calloc(current_size, sizeof(char));

	memcpy(result, str, current_size);

	char *next_str = NULL;

	while ((next_str = va_arg(args, char*)) != NULL)
	{
		size_t size = strlen(next_str);
		result = realloc(result, current_size + size);
		memcpy(result + current_size, next_str, size);
		current_size += size;
	}

	result = realloc(result, current_size + 1);
	result[current_size] = 0;
	return result;
}

#endif
