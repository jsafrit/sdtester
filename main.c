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

void make_dest_filename( unsigned int count, char * dest_fn)
{
    char counter[4] = {'0','0','0','0'};
    unsigned int j;

    if (count > 9999)
        return;

    counter[0] = (count / 1000) + '0';
    count = count % 1000;
    counter[1] = (count / 100) + '0';
    count = count % 100;
    counter[2] = (count / 10) + '0';
    count = count % 10;
    counter[3] = (count) + '0';

    for (j=0; j<4; j++)
        dest_fn[j+4] = counter[j];
    printf("Dest Filename: %s\n", dest_fn);
}


void make_copy( FILE * src_fh, unsigned int cnt, char * dest_fn )
{
    FILE *dst_fh;
    char buffer[BUFF_SIZE];
    unsigned int nrbuff,nwbuff;

    make_dest_filename(cnt, dest_fn);
    rewind(src_fh);
    dst_fh = fopen( dest_fn, "wb" );
    while ( (nrbuff = fread(buffer, 1, BUFF_SIZE, src_fh), nrbuff >0 ) )
    {
        nwbuff = fwrite(buffer, 1, nrbuff, dst_fh);
        if (nwbuff != nrbuff)
            printf("Write ERROR!\n");
    }
    fclose(dst_fh);
}


int main()
{
    const char source_root_fn[] = "S0";
    const char dest_root_fn[] = "D0";
    const unsigned int max_copies = 99;    // Max allowed is 9999

    char source_fn[13];
    char dest_fn[13];
    FILE *src_fh;
    int i;

    chdir(".\\root\\");

    next_source(source_root_fn ,source_fn);
    do
    {
        // open source file for copying
        printf("Source Filename: %s\n", source_fn);
        src_fh = fopen(source_fn, "rb");

        // create destination root filename
        strcpy(dest_fn,source_fn);
        strncpy(dest_fn, dest_root_fn, 2);

        for (i=1; i<=max_copies; i++)
            make_copy(src_fh, i, dest_fn);

        next_source(source_root_fn ,source_fn);

    } while (strlen(source_fn) > 0);

    return 0;
}
