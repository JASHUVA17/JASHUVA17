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

int main(int argc,char * argv[])            			// Main function with arguments count and array of argument strings
{
    char version[3]={0};                    			// Initialize version array to hold version info
    FILE *fptr;                             			// File pointer for file operations
    if(argc == 1)                           			// Check if no arguments are provided
    {
        printf("Error : Please pass valid either -t,-T,-a,-A,-y,-c,-g,-h,-v and MP3 file name\n"); // Print error message for missing arguments
        return 0;
    }
    if(strcmp(argv[1] ,"--help") == 0)      			// Check if the first argument is "--help"
    {
        printf("Usage : mp3tag -[tTaAycg] ""value"" file1 mp3tg -v\n-t\tModifies a Title tag\n-T\tModifies a Track tag\n-a\tModifies an Artist tag\n-A\tModifies an Album tag\n-y\tModifies a Year tag\n-c\tModifies a Comment tag\n-g\tModifies a Genre tag\n-h\tDisplays this help info\n-v\tPrints Version info\n");	      // Print usage instructions
    }
    if(strcmp(argv[1],"-v") == 0)           			// Check if the first argument is "-v" for version info
    {
        if(argv[2] ==0)                     			// Check if the file name is provided
        {
            printf("Please pass file name\n"); 			// Print message to provide a file name
            return 0;                       
	}
        fptr = fopen(argv[2],"r");          			// Open the file in read mode
        char arr[4]={0};                    			// Initialize an array to hold file header info
        fread(arr,3,1,fptr);                			// Read the first 3 bytes of the file
        if(strcmp(arr,"ID3") != 0)          			// Check if the file is not an MP3 file
        {
            fprintf(stderr,"file is not a mp3 file name\n"); 	// Print error message for invalid file type
            printf("Please pass a mp3 file name\n"); 		// Print message to provide an MP3 file
            return 0;                       
	}
        fread(version,2,1,fptr);            			// Read the version info from the file
        if(version[0] == 3 && version[1] == 00) 		// Check if the version is 3.0
        {
            strcpy(version,"2");            			// Set version to 2 if it's 3.0
        }
       if (tag_reader(fptr,version)==e_success)     
	{
	    printf("Reading of tags were successfull\n");
	}
	else
	{
	    printf("Reading of tags were failure\n");
	}
	
        fclose(fptr);                       			// Close the file
    }
    if(strcmp(argv[1],"-e") == 0)           			// Check if the first argument is "-e" for editing tags
    {
        if(argv[4] == 0)                    			// Check if the MP3 file is provided
        {
            printf("please provide the mp3 file\n"); 		// Print message to provide the MP3 file
            return 0;                       
	}
        if(argv[2] == 0)                    			// Check if an option to edit is provided
        {
            printf("please pass any proper option to edit\n"); 	// Print message to provide a valid edit option
            return 0;                       
        }
        FILE *src = fopen(argv[4],"r");     			// Open the source MP3 file in read mode
        FILE *dest = fopen("temp.mp3","w"); 			// Open a temporary file in write mode
        char str[50],arr[5];                			// Initialize arrays to hold strings
        if(dest == NULL)                    			// Check if the destination file could not be opened
        {
            return 0;                       
        }
        strcpy(str,argv[3]);                			// Copy the new tag value to str
        if(strcmp(argv[2],"-t") == 0)       			// Check if the edit option is "-t" for title
        {
            strcpy(arr,"TIT2");             			// Set arr to "TIT2" for title tag
            printf("You choose title edit\n"); 			// Print message indicating title edit
        }
        else if(strcmp(argv[2], "-a") == 0) 			// Check if the edit option is "-a" for artist
        {
            strcpy(arr,"TPE1");             			// Set arr to "TPE1" for artist tag
            printf("You choose Artist edit\n"); 		// Print message indicating artist edit
        }
        else if(strcmp(argv[2], "-A") == 0) 			// Check if the edit option is "-A" for album
        {
            strcpy(arr,"TALB");             			// Set arr to "TALB" for album tag
            printf("You choose Album edit\n"); 			// Print message indicating album edit
        }
        else if(strcmp(argv[2], "-y") == 0) 			// Check if the edit option is "-y" for year
        {
            strcpy(arr,"TYER");             			// Set arr to "TYER" for year tag
            printf("You choose Year edit\n"); 			// Print message indicating year edit
        }
        else if(strcmp(argv[2],"-c") == 0)  			// Check if the edit option is "-c" for comment
        {
            strcpy(arr,"COMM");             			// Set arr to "COMM" for comment tag
            printf("You choose Composer edit\n"); 		// Print message indicating composer edit
        }
        else if(strcmp(argv[2], "-g") == 0) 			// Check if the edit option is "-g" for genre
        {
            strcpy(arr,"TCON");             			// Set arr to "TCON" for genre tag
            printf("You choose Language edit\n"); 		// Print message indicating genre edit
        }
        else                                
        {
            printf("Enter a valid input\n"); 			// Print message indicating invalid input
            return 0;                       
        }
        if(copy_remain(src,dest,arr,str)== e_success)	
	{
	    printf("Editing of tags were successful\n");
	}
	else
	{
	    printf("Editing of tags were failure\n");
	} 
    }
    return 0;
}
