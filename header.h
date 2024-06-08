#ifndef HEADER                      			// If HEADER is not defined, proceed with the following code
#define HEADER                      			// Define HEADER to prevent multiple inclusions of this header file

#include<stdio.h>                   			// Include the standard I/O library for file operations
#include<string.h>                  			// Include the string library for string manipulation functions

typedef enum {                      			// Define an enumeration for status codes
    e_failure,                      			// Enumeration value for failure status
    e_success,                      			// Enumeration value for success status
} Status;                           			// Name the enumeration type as Status

Status tag_reader(FILE *fptr,char *version); 		// Declare the tag_reader function that reads MP3 tags
Status copy_remain(FILE *src, FILE *dest, char *user_tag, char *user_string); // Declare the copy_remain function that copies and edits MP3 tags
#endif                              			// End of the conditional inclusion
