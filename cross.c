#include <stdio.h>
#include <string.h>

/* Prototypes */
void FindCross(char *word1, char *word2, int *cross_1, int *cross_2);
void PrintCross(char *p1_word1, char *p1_word2, char *p2_word1, char *p2_word2, int p1_cross_1, int p1_cross_2, int p2_cross_1, int p2_cross_2);

main()
{
   FILE   *infile;        /* Input file pointer */
   char   p1_word1[11];   /* First word of first pair */
   char   p1_word2[11];   /* Second word of first pair */
   char   p2_word1[11];   /* First word of second pair */
   char   p2_word2[11];   /* Second word of second pair */
   int    cross_p1_word1; /* Position of cross in first word, pair 1 */
   int    cross_p1_word2; /* Position of cross in second word, pair 1 */
   int    cross_p2_word1; /* Position of cross in first word, pair 2 */
   int    cross_p2_word2; /* Position of cross in second word, pair 2 */

   /* Open the input file */
   infile = fopen("cross.in", "r");

   /* Loop through all cases in the file */
   while ( !feof(infile) )
   {
      /* Read two pairs of words */
      fgets(p1_word1, 80, infile);
      p1_word1[strlen(p1_word1)-1] = '\0';
      fgets(p1_word2, 80, infile);
      p1_word2[strlen(p1_word2)-1] = '\0';
      fgets(p2_word1, 80, infile);
      p2_word1[strlen(p2_word1)-1] = '\0';
      fgets(p2_word2, 80, infile);
      p2_word2[strlen(p2_word2)-1] = '\0';

      /* Make sure we don't output the last case twice */
      if ( !feof(infile) )
     {
         /* Find where the first pair crosses if they do */
         FindCross(p1_word1, p1_word2, &cross_p1_word1, &cross_p1_word2);

         /* Find where the second pair crosses if they do */
         FindCross(p2_word1, p2_word2, &cross_p2_word1, &cross_p2_word2);

         /* If we didn't find a cross in both pairs, output accordingly */
         if ( (cross_p1_word1 == -1) || (cross_p1_word2 == -1) ||
              (cross_p2_word1 == -1) || (cross_p2_word2 == -1) )
            printf("Cannot cross the words.\n");
         else
            /* Otherwise, output the two crosses */
            PrintCross(p1_word1, p1_word2, p2_word1, p2_word2, cross_p1_word1,
                       cross_p1_word2, cross_p2_word1, cross_p2_word2);

         /* Put in our blank line between output sets */
         printf("\n");
      }
   }

   /* Close the input file */
   fclose(infile);
}


/* Procedure FindCross finds the positions of the leading cross of
 * two words.  If none can be found, -1 is returned in the index variables */

void FindCross(char *word1, char *word2, int *cross_1, int *cross_2)
{
   int   x, y;  /* Looping variables */

   *cross_1 = -1;
   *cross_2 = -1;

   /* For each letter in the first word, try to find it in the second word */
   for (x=0; (x < strlen(word1)) && (*cross_1 == -1); x++)
   {
      for (y=0; (y < strlen(word2)) && (*cross_2 == -1); y++)
      {
         /* If the 2 letters are the same, we have found the leading cross */
         if (word1[x] == word2[y])
         {
            *cross_1 = x;
            *cross_2 = y;
         }
      }
   }
}


/* Procedure PrintCross produces the output of two pair of crossing words */

void PrintCross(char *p1_word1, char *p1_word2, char *p2_word1, char *p2_word2,
                int p1_cross_1, int p1_cross_2, int p2_cross_1, int p2_cross_2)
{
   int   x, y;            /* Looping variables */
   int   max_cross_2;     /* Line on which horizontal words will appear */
   char  screen[25][25];  /* An array of the "screen" */
   int   num_y_lines;     /* Number of lines to output for this pair */

   /* Initialize the screen array */
   for (y=0; y < 25; y++)
   {
      for (x=0; x < 25; x++)
        screen[y][x] = ' ';
   }

   /* Find the line that has the horizontal words */
   if (p1_cross_2 > p2_cross_2)
      max_cross_2 = p1_cross_2;
   else
      max_cross_2 = p2_cross_2;

   /* Store the first word of pair 1 into the screen array */
   for (x=0; x < strlen(p1_word1); x++)
      screen[max_cross_2][x] = p1_word1[x];

   /* Store the first word of pair 2 into the screen array */
   for (x=0; x < strlen(p2_word1); x++)
      screen[max_cross_2][x+strlen(p1_word1)+2] = p2_word1[x];

   /* Store the second word of pair 1 into the screen array */
   for (y=0; y < strlen(p1_word2); y++)
      screen[y+max_cross_2-p1_cross_2][p1_cross_1] = p1_word2[y];

   /* Store the second word of pair 2 into the screen array */
   for (y=0; y < strlen(p2_word2); y++)
      screen[y+max_cross_2-p2_cross_2][strlen(p1_word1)+2+p2_cross_1] =
         p2_word2[y];

   /* Calculate the number of lines that we need to output */
   if ( strlen(p1_word2)-p1_cross_2 > strlen(p2_word2)-p2_cross_2 )
      num_y_lines = max_cross_2 + strlen(p1_word2) - p1_cross_2;
   else
      num_y_lines = max_cross_2 + strlen(p2_word2) - p2_cross_2;

   /* Output the answer from our "screen" array */
   for (y=0; y < num_y_lines; y++)
   {
      for (x=0; x < strlen(p1_word1) + strlen(p2_word1) + 2; x++)
         printf("%c", screen[y][x]);
      printf("\n");
   }
}

