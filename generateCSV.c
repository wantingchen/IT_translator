#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SSIZE   240
#define SPACE   "&nbsp;"
#define FSPACE  "　"
#define FFSPACE "\t"

int removeSpace(char* str) {
    char* c = strstr(str, SPACE);
    if (!c) return 0;
    strcpy(c, (c+6));
    return 1;
}

int removeFullSpace(char* str) {
    char* c = strstr(str, FSPACE);
    if (!c) return 0;
    strcpy(c, (c+3));
    return 1;
}

int removeFFSpace(char* str) {
    char* c = strstr(str, FFSPACE);
    if (!c) return 0;
    strcpy(c, (c+1));
    return 1;
}

int convert(char* arg) {
    char fileName[48];
    FILE *fd_in = fopen(arg, "r");

    if (!fd_in) {
        perror ("Error opening file: ");
        return 1;
    }

    int pos=0, c;
    int d;
    char *s; 
    char strParser[SSIZE];

    strcpy(fileName, "./csv/\0");
    strcat(fileName, strstr(arg, "termb"));
    strcpy(strstr(fileName, "htm"), "csv");
    printf("Start converting %s to %s ...\n", arg, fileName);

    FILE *fd_out = fopen(fileName, "w");

    if (!fd_out) {
        perror ("Error creating file: ");
        return 2;
    }

    do {
        c = getc(fd_in);
        if ((strParser[pos++]=c) == '>') {
            strParser[pos] = '\0';
            pos = 0;
            if ( (s=strstr(strParser, "</td"))) {
                strcpy(s, "\0");
                if (s!=strParser) {
                    do {
                        d = removeSpace(strParser);
                    } while (d!=0);
                    do {
                        d = removeFullSpace(strParser);
                    } while (d!=0);
                    do {
                        d = removeFFSpace(strParser);
                    } while (d!=0);

                    fprintf(fd_out, "%s,", strParser);
                    //printf("%s,", strParser);
                }
            }
            if ( (s=strstr(strParser, "</tr"))) {
                fprintf(fd_out, "\n");
                //printf("\n");
            }
         }
     }while (c!=EOF);

     fclose(fd_out);
     fclose(fd_in);
     
     return 0;
}


int main(int argc, char* argv[]) {
	if (argc==1) {
        puts("No input file!");
        exit(1);
    }

    int iFile = 1;
    do {
        convert(argv[iFile++]);
    } while (iFile < argc);

    return 0;
}
