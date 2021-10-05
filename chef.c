#include <stdio.h>
#include <string.h>
/*
    This solution scans the input line from left to right checking all the
  rules at each character position.  If a rule matches, the replacement
  substring is added to the output string, and the index into the input
  line is incremented by the length of the matching substring (this way,
  we will not match characters that were used to match a previous rule).
  If no rules matched at a character, then that character is added to the
  output string as is.
*/


/* The table.  Subs[n][0] is replaced by Subs[n][1] */
char *SubS[29][2] = { {"and",   "und"},
                      {"And",   "Und"},
                      {"Then",  "Den"},
                      {"then",  "den"},
                      {"the",   "der"},
                      {"The",   "Der"},
                      {"Yes",   "Ya"},
                      {"yes",   "ya"},
                      {"Which", "Vich"},
                      {"which", "vich"},
                      {"x.",    "xy."},
                      {"x ",    "xy "},
                      {"w ",    "v "},
                      {"w",     "v"},
                      {"W",     "V"},
                      {"d.",    "dy."},
                      {"d ",    "dy "},
                      {"p.",    "py."},
                      {"p ",    "py "},
                      {"v",     "f"},
                      {"e ",    "ey "},
                      {"e.",    "ey."},
                      {"ir",    "ur"},
                      {"or",    "ur"},
                      {"ou",    "oo"},
                      {"ue",    "oo"},
                      {"Th",    "D"},
                      {"th",    "d"},
                      {"ick",   "ook"}};

void main()
{
FILE *F;                  /* Input file variable                            */
char InS[256];            /* Search string                                  */
char CurS[256];           /* Output string                                  */
char *p;                  /* Used for finding \n                            */
int  i;                   /* Loop variables                                 */
int  N;                   /* Number of lines                                */
int  SCnt;                /* Substring count variable                       */
int  CurPos;              /* Substring location                             */
int  found;               /* Substring found                                */

  F = fopen("Chef.in","rt");    /* Open input file */
  fgets(InS,255,F);
  sscanf(InS,"%d",&N);          /* Read number of lines */

  for (i=0; i < N; i++)
  {
    fgets(InS,255,F);           /* Read the line & remove the C/R */
    p = strstr(InS,"\n");
    if (p)
      *p = 0;
    CurS[0] = 0;

    CurPos = 0;
    while (CurPos < strlen(InS))
    {
      found = 0;
      for (SCnt=0; SCnt < 29; SCnt++)
      {
	if ((!found) && (!strncmp(SubS[SCnt][0], &InS[CurPos], strlen(SubS[SCnt][0]))))
	{
	  found = 1;
	  strcat(CurS, SubS[SCnt][1]);
	  CurPos += strlen(SubS[SCnt][0]);
	}
      }

      if (!found)
      {
	 strncat(CurS, &InS[CurPos], 1);
	 CurPos++;
      }
    }
    printf("%s\n",CurS);
  }
  fclose(F);
}
