#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char bolb[1024];

int main()
{
    char input[1024];
    printf("Enter the file name: \n");
    scanf("%1023s", input);

    char cwd[FILENAME_MAX];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return 1;
    }

    strcat(cwd, "/");

    char inputFile[FILENAME_MAX];
    strcpy(inputFile, cwd);
    strcat(inputFile, input);
    printf("Input file: %s\n", inputFile);
    char outfile[FILENAME_MAX];
    strcpy(outfile, cwd);
    strcat(outfile, "copy");
    strcat(outfile, input);
    printf("Output file: %s\n", outfile);
    FILE *fp = fopen(inputFile, "rb");
    if (fp == NULL)
    {
        perror("Error opening input file");
        return 1;
    }

    FILE *fw = fopen(outfile, "wb");
    if (fw == NULL)
    {
        perror("Error opening output file");
        fclose(fp);
        return 1;
    }

    fseeko(fp, 0, SEEK_END);
    long int amount = ftello(fp);

    if (amount <= 0)
    {
        perror("File size error");
        fclose(fp);
        fclose(fw);
        return 1;
    }

    printf("File size is %ld bytes\n", amount);
    fseeko(fp, 0, SEEK_SET);
    while (1)
    {
        size_t n = fread(bolb, 1, 1024, fp);
        if (n == 0)
            break;
        fwrite(bolb, 1, n, fw);
        printf("%d  data left\r", (amount -= n));
    }

    fclose(fp);
    fclose(fw);

    printf("\nFile copy successful\n");

    return 0;
}
