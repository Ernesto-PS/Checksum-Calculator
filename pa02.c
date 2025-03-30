#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define LETTERS_PER_ROW 80

int main(int argc, char* argv[])
{
    char *iFile = argv[1];
    int checksumSize = atoi(argv[2]);
    char *plainText;
    int charASCII = 0;
    int charCounter = 0;
    unsigned long cs8 = 0;
    unsigned long cs16 = 0;
    unsigned long cs32 = 0;

    // Opens key file
    FILE *inputFile = fopen(iFile, "r");
    if (inputFile == NULL) 
    {
        fprintf(stderr, "Could not open input file!\n");
        return 0;
    }

    // Checks that the checksum size is valid
    if (checksumSize != 8 && checksumSize != 16 && checksumSize != 32)
    {
        fprintf(stderr, "Valid checksum sizes are 8, 16, or 32\n");
        return 0;
    }

    // Allocation of space for the plainText pointer
    plainText = malloc(sizeof(char) * 5000);
    
    // Reads and stores characters from inputFile into the plainText
    while ((charASCII = getc(inputFile)) != EOF)
    {
        plainText[charCounter] = (char)charASCII;
        charCounter++;
    }
    
    // Stores termination character in the plaintext
    plainText[charCounter] = '\0';

    // Calculates checksum size depending on bits used
    int ptLength = strlen(plainText);
    charCounter = 0;
    if (checksumSize == 8)
    {
        while (charCounter < ptLength)
        {
            cs8 = cs8 + plainText[charCounter];
            charCounter++;
        }
        cs8 &= 0xff;

        // Prints text
        for (int i = 0; i < ptLength; i++) 
        {
            if (i % LETTERS_PER_ROW == 0)
                printf("\n");
            printf("%c", plainText[i]);
        }
        printf("\n");

        // Prints all of the results
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, cs8, ptLength);
    }

    else if (checksumSize == 16)
    {
        // Determines padding
        if (ptLength % 2)
        {
            strcat(plainText, "X");
            ptLength++;
        }

        while (charCounter < ptLength)
        {
            cs16 = cs16 + (plainText[charCounter] << 8);
            cs16 = cs16 + plainText[charCounter + 1];
            charCounter = charCounter + 2;
        }
        cs16 &= 0xffff;

        // Prints text
        for (int i = 0; i < ptLength; i++) 
        {
            if (i % LETTERS_PER_ROW == 0)
                printf("\n");
            printf("%c", plainText[i]);
        }
        printf("\n");

        // Prints all results
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, cs16, ptLength);
    }
    
    else if (checksumSize == 32)
    {
        // Determines padding
        int padding = ptLength % 4;
        for (int i = padding; i < 4; i++)
        {
            strcat(plainText, "X");
            ptLength++;
        }

        while (charCounter < ptLength)
        {
            cs32 = cs32 + (plainText[charCounter] << 24);
            cs32 = cs32 + (plainText[charCounter + 1] << 16);
            cs32 = cs32 + (plainText[charCounter + 2] << 8);
            cs32 = cs32 + plainText[charCounter + 3];
            charCounter = charCounter + 4;
        }
        cs32 &= 0xffffffff;

        // Prints text
        for (int i = 0; i < ptLength; i++) 
        {
            if (i % LETTERS_PER_ROW == 0)
                printf("\n");
            printf("%c", plainText[i]);
        }
        printf("\n");

        // Prints all results
        printf("%2d bit checksum is %8lx for all %4d chars\n", checksumSize, cs32, ptLength);
    }

    fclose(inputFile);
    return 0;
}