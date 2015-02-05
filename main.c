#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void next_source( char * fn )
{
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir (".\\root\\")) != NULL)
    {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL)
        {
            printf ("%s\n", ent->d_name);
            strcpy(fn, &(ent->d_name));
            break;
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
}

int main()
{
    const char source_root_fn[] = "S0";
    const char dest_root_fn[] = "D0";
    const max_copies = 999;

    char source_fn[13];
    char * p_source_fn = source_fn;
    char dest_fn[13];

    next_source(p_source_fn);
    printf("%s\n", p_source_fn);

    printf("Hello world!\n");
    return 0;
}
