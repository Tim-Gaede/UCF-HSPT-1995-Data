/***************************************************************************/
/* Tenth Annual UCF ACM/UPE High School Programming Tournament             */
/* May 3, 1996                                                             */
/*                                                                         */
/* Program: PASSWORD                                                       */
/***************************************************************************/


#include <stdio.h>
#include <ctype.h>


#define TRUE    1
#define FALSE   0


/* This function checks to see if the string is in all lower-case */
int allLower(char *word)
{
   int   ok;
   int   i;

   ok = TRUE;
   for (i=0; i < strlen(word); i++)
   {
      if ( (word[i] < 'a') || (word[i] > 'z') )
	 ok = FALSE;
   }

   return (ok);
}


/* This function checks to see if the string is in all upper-case */
int allUpper(char *word)
{
   int   ok;
   int   i;

   ok = TRUE;
   for (i=0; i < strlen(word); i++)
   {
      /* If a character is not in the range 'A' to 'Z', then the string */
      /* is NOT all upper-case                                          */
      if ( (word[i] < 'A') || (word[i] > 'Z') )
	 ok = FALSE;
   }

   return (ok);
}


/* This function checks to see if the string is all digits */
int allDigits(char *word)
{
   int   ok;
   int   i;

   ok = TRUE;
   for (i=0; i < strlen(word); i++)
   {
      /* If a character is not in the range '0' to '9', then the string */
      /* is NOT all digits                                              */
      if ( (word[i] < '0') || (word[i] > '9') )
	 ok = FALSE;
   }

   return (ok);
}


/* This function checks to see if the string is an English word */
int englishWord(char *word)
{
   int    ok;
   int    onlyLetters;
   int    lastConsonant;
   int    i;
   char   ch;

   /* Check and see if the string has only letters */
   onlyLetters = TRUE;
   for (i=0; i < strlen(word); i++)
   {
      if ( ((word[i] < 'A') || (word[i] > 'Z')) &&
	   ((word[i] < 'a') || (word[i] > 'z')) )
	 onlyLetters = FALSE;
   }

   /* If the string has only letters, check to see if every consonant is */
   /* followed by at least one vowel (a, e, i, o, u) -- except for the   */
   /* last consonant                                                     */
   if (onlyLetters == TRUE)
   {
      lastConsonant = -1;
      for (i=0; i < strlen(word); i++)
      {
	 /* Check if the letter is not a vowel, implying it's a consonant */
	 ch = toupper(word[i]);
	 if ( (ch != 'A') && (ch != 'E') && (ch != 'I') &&
	      (ch != 'O') && (ch != 'U') )
	    lastConsonant = i;
      }
      ok = TRUE;

      /* We don't want to check what is after the last letter (whether */
      /* it's a consonant or a vowel) so don't check it                */
      for (i=0; i < strlen(word)-1; i++)
      {
	 /* If the ith letter is a consonant, check for a vowel after */
	 /* it unless it is the last consonant                        */
	 ch = toupper(word[i]);
	 if ( (i != lastConsonant) && (ch != 'A') && (ch != 'E') &&
	      (ch != 'I') && (ch != 'O') && (ch != 'U') )
	 {
	    /* If there is not a vowel after the consonant, mark it not ok */
	    ch = toupper(word[i+1]);
	    if ( (ch != 'A') && (ch != 'E') && (ch != 'I') &&
		 (ch != 'O') && (ch != 'U') )
	       ok = FALSE;
	 }
      }
   }
   else
      ok = FALSE;

   /* Return whether the string is an English word or not */
   return (ok);
}


void main()
{
   FILE   *infile;     /* Input file */
   char   word[256];   /* Input string */

   /* Open the input file */
   if ( (infile = fopen("password.in", "r")) == NULL )
   {
      fprintf(stderr, "Unable to open input file!\n");
      exit(1);
   }

   /* Read until EOF */
   while (!feof(infile))
   {
      /* Read string */
      fgets(word, 255, infile);

      /* Check to make sure we just didn't hit EOF */
      /* Echo the string */
      if (word[strlen(word)-1] == '\n')
	 word[strlen(word)-1] = '\0';
      printf("%s\n", word);

      /* If the string is not all lower-case, not all upper-case, */
      /* not all digits, not an English word, and is at least 5   */
      /* characters long, then it's a good password               */
      if ( (!allLower(word)) && (!allUpper(word)) &&
	   (!allDigits(word)) && (!englishWord(word)) &&
	   (strlen(word) >= 5) )
	 printf("Good\n");
      else
	 printf("Not Good\n");

      /* Don't forget the blank line after the output for each set */
      printf("\n");
   }
}
