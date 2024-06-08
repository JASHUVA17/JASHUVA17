#include "header.h"

#define SWAP(num) \
{\
    unsigned char * str = (unsigned char *) &num; \
    for(int i=0;i<2;i++) \
    { \
	char temp =str[i]; \
	str[i] = str[4-i-1]; \
	str[4-i-1] = temp; \
    } \
}

char arr[4]={0},Title[100]={0},Artist[100]={0},Album[100]={0},Music[100]={0},Genre[100]={0},Year[4]={0},version[3]={0}; // Initialize arrays to store tag information
Status tag_reader(FILE *fptr,char *version)  		// Function to read MP3 tags, takes a file pointer and version string
{
    fseek(fptr,10,SEEK_SET);                 		// Move the file pointer 10 bytes from the start
    for(int i=0;i<6;i++)                     		// Loop to read 6 different tags
    {
        fread(arr,4,1,fptr);                 		// Read 4 bytes to determine the tag type
        int size=0;                          		// Initialize size variable to store tag size
        fread(&size,4,1,fptr);               		// Read the size of the tag
        SWAP(size);                          		// Swap byte order of size for correct interpretation
        fseek(fptr,3,SEEK_CUR);              		// Skip 3 bytes (flags and encoding)
        if(strncmp(arr,"TIT2",4) == 0)       		// Check if the tag is a Title tag
        {
            fread(Title,size-1,1,fptr);      		// Read the Title tag data
        }
        else  if(strncmp(arr,"TYER",4) == 0) 		// Check if the tag is a Year tag
        {
            fread(Year,size-1,1,fptr);       		// Read the Year tag data
        }
        else if(strncmp(arr,"TALB",4) == 0)  		// Check if the tag is an Album tag
        {
            fread(Album,size-1,1,fptr);      		// Read the Album tag data
        }
        else if(strncmp(arr,"TPE1",4) == 0)  		// Check if the tag is an Artist tag
        {
            fread(Artist,size-1,1,fptr);     		// Read the Artist tag data
        }
        else  if(strncmp(arr,"TCON",4) == 0) 		// Check if the tag is a Genre tag
        {
            fread(Genre,size-1,1,fptr);      		// Read the Genre tag data
        }
        else  if(strncmp(arr,"COMM",4) == 0) 		// Check if the tag is a Comment tag
        {
            fread(Music,size-1,1,fptr);      		// Read the Comment tag data
        }
    }
    printf("..........................................................\n"); 	// Print a separator
    printf("MP3 Tag Reader and Editor for ID3 v%s\n",version); 			// Print the version of the MP3 tag reader
    Year[4] ='\0';                        					// Null-terminate the Year string
    printf("..........................................................\n"); 	// Print a separator
    printf("Title\t :\t %s\nArtist\t :\t %s\nAlbum\t :\t %s\nYear\t :\t %s\nMusic\t :\t%s\nGenre\t :\t %s\n",Title,Artist,Album,Year,Music,Genre); 								// Print tag information
    return e_success;
}
Status copy_remain(FILE *src, FILE *dest, char *user_tag, char *user_string) 	// Function to copy remaining tags and edit one, takes source and destination file pointers, tag and string
{
    int size,sample_size;                 		// Initialize variables for size and sample size
    char str[150];                        		// Buffer to hold tag data
    fread(str,10,1,src);                  		// Read the first 10 bytes of the source file
    fwrite(str,10,1,dest);                		// Write the first 10 bytes to the destination file
    for(int i=0;i<6;i++)                  		// Loop to read and write 6 tags
    {
        fread(str,4,1,src);               		// Read the tag type from the source file
        fwrite(str,4,1,dest);             		// Write the tag type to the destination file
        if(strncmp(str,user_tag,4) == 0)  		// Check if the current tag matches the user tag
        {
            size = strlen(user_string);   		// Get the length of the user's new tag string
            int temp = size;              		// Temporary variable to store size
            size++;                       		// Increment size to account for null terminator
            SWAP(size);                   		// Swap byte order of size
            fwrite(&size,4,1,dest);       		// Write the size to the destination file
            fread(&sample_size,4,1,src);  		// Read the original tag size from the source file
            fread(str,3,1,src);           		// Read the next 3 bytes from the source file
            fwrite(str,3,1,dest);         		// Write the 3 bytes to the destination file
            fwrite(user_string,temp,1,dest); 		// Write the new tag string to the destination file
            SWAP(sample_size);            		// Swap byte order of the original sample size
            fseek(src,sample_size-1,SEEK_CUR); 		// Skip the original tag data in the source file
        }
        else
        {
            fread(str,4,1,src);           		// Read the original tag size from the source file
            fwrite(str,4,1,dest);         		// Write the original tag size to the destination file
            fseek(src,-4,SEEK_CUR);       		// Move the file pointer back by 4 bytes
            fread(&sample_size,4,1,src);  		// Read the original sample size
            SWAP(sample_size);            		// Swap byte order of the sample size
            fread(str,3,1,src);           		// Read the next 3 bytes from the source file
            fwrite(str,3,1,dest);         		// Write the 3 bytes to the destination file
            fread(str,sample_size-1,1,src); 		// Read the original tag data from the source file
            str[sample_size-1] = '\0';    		// Null-terminate the tag data
            fwrite(str,sample_size-1,1,dest); 		// Write the original tag data to the destination file
        }
    }
} 
