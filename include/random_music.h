#include "library.h"

string random_music( string directory, string extension, string filename_optional = "" )
{
    if ( filename_optional != "" )
        return directory + "/" + filename_optional;

    srand( time(0) );

    struct dirent *de=NULL;
    DIR *d=NULL;

//  if(argc != 2)
//  {
//    fprintf(stderr,"Usage: %s dirname\n",argv[0]);
//    return(1);
//  }

    d=opendir(directory.c_str());
    if(d == NULL)
    {
        perror("Couldn't open directory");
        exit(2);
    }
    vector <string> files;

    // Loop while not NULL
    while(de = readdir(d))
    {
        if ( de->d_name != "." || de->d_name != ".." )
        {
        //    if ( de-> == extension )
            string f_ext = "";
            string filename = de->d_name;
            size_t i = filename.rfind('.', filename.length());
            if (i != string::npos) {
                  f_ext = (filename.substr(i+1, filename.length() - i));
            }

            if ( f_ext == extension )

            files.push_back( de->d_name);
        }
//    printf("%i\n",de->d_reclen);
    }

    for( int i = 0; i<files.size(); i++ )
    {
//      printf("%s\n",files[i].c_str() );
    }

    closedir(d);

    return directory + "/" + files[ rand()%files.size() ];
}

