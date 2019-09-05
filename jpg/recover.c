/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>


 

int main(void)
{
    
    int counter = 0;
    unsigned char buffer[512];
    char jpgName[8];
    bool found = false;
    FILE* jpg;
    
    // opens card file, checks if it is valid
    FILE* card = fopen("card.raw", "r");
    if (card == NULL)
    {
        printf("Could not open file.");
        fclose(card);
        return 1;
    }
    
    while(!feof(card))
    {
        // reads into card 512 bytes at a time and checks for EOF
        fread(&buffer, sizeof(buffer), 1, card);
        if (!feof(card))
        {
            // checks to see if first 4 bytes are a jpeg signature
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
            {   
                if (found == true)
                {
                    // closes any currently open .jpg
                    fclose(jpg);
                }
                // creates new .jpg file and writes to it
                sprintf(jpgName, "%03d.jpg", counter);
                jpg = fopen(jpgName, "w");
                fwrite(&buffer, sizeof(buffer), 1, jpg );
                counter++;
                found = true;
            }
            else if (found == true)
            {
                // if no new file found, continue writing    
                fwrite(&buffer, sizeof(buffer), 1, jpg );
            }
        }    
    }
        
    fclose(card);
        
    fclose(jpg);
        
    return 0;

}