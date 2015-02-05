#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void next_source( char * pattern, char * fn )
{
    static DIR *dir=NULL;
    struct dirent *ent;

    if (dir == NULL)
    {
        dir = opendir (".\\root\\");
        if (dir == NULL)
        {
            /* could not open directory */
            perror ("");
            return EXIT_FAILURE;
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
    const max_copies = 999;

    char source_fn[13];
    char dest_fn[13];

    next_source(source_root_fn ,source_fn);
    do
    {
        printf("%s\n", source_fn);
        next_source(source_root_fn ,source_fn);
    } while (strlen(source_fn) > 0);

    return 0;
}
