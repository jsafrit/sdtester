#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define BUFF_SIZE 512
void next_source( const char * pattern, char * fn )
{
    static DIR *dir=NULL;
    struct dirent *ent;

    if (dir == NULL)
    {
        //dir = opendir (".\\root\\");
        dir = opendir (".");
        if (dir == NULL)
        {
            /* could not open directory */
            perror ("could not open directory");
            return;
        }
    }
    /* grab all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL)
    {
        //printf ("%s\n", ent->d_name);
        // Does this file match the pattern
        if (strncmp(pattern, ent->d_name, 2) != 0)
            continue;
        strcpy(fn, ent->d_name);
        return;
        break;
    }
    rewinddir(dir);
    //closedir (dir);
    *fn = '\0';
}


int main()
{
    const char source_root_fn[] = "S0";
    const char dest_root_fn[] = "D0";
    const unsigned int max_copies = 99;    // Max allowed is 9999

    char source_fn[13];
    char dest_fn[13];

    FILE *src_fh, *dst_fh;
    char buffer[BUFF_SIZE];

    int i,j,nrbuff,nwbuff;


    chdir(".\\root\\");

    next_source(source_root_fn ,source_fn);
    do
    {
        printf("Source Filename: %s\t", source_fn);
        src_fh = fopen(source_fn, "rb");

        // create destination root filename
        strcpy(dest_fn,source_fn);
        strncpy(dest_fn, dest_root_fn, 2);
        printf("Dest Root Filename: %s\n", dest_fn);

        for (i=1; i<=max_copies; i++)
        {
            char counter[5];
            sprintf(counter, "%04d", i);
            for (j=0; j<4; j++)
                dest_fn[j+4] = counter[j];
            printf("Dest Filename: %s\n", dest_fn);
            // copy the file here
            dst_fh = fopen( dest_fn, "wb" );
            while ( (nrbuff = fread(buffer, 1, BUFF_SIZE, src_fh), nrbuff >0 ) )
            {
                nwbuff = fwrite(buffer, 1, nrbuff, dst_fh);
                if (nwbuff != nrbuff)
                    printf("Write ERROR!\n");
            }
            fclose(dst_fh);
            rewind(src_fh);
        }
        next_source(source_root_fn ,source_fn);

    } while (strlen(source_fn) > 0);

    return 0;
}
