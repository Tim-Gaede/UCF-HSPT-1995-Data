#include <stdio.h>


#define TRUE    1
#define FALSE   0


main()
{
   FILE   *infile;
   char   inputLine[80];
   int    lastHouse;
   int    houseOfPoliceman;
   int    i;
   int    visited[5000];
   int    caught;
   int    numVisited;
   int    startHouse;
   int    currentHouse;

   /* Open the input file */
   infile = fopen("salesman.in", "r");

   /* Process all data sets */
   while ( fgets(inputLine, 79, infile) != NULL )
   {
      sscanf(inputLine, "%d %d", &lastHouse, &houseOfPoliceman);

      /* Initialize visited flags */
      for (i=0; i < lastHouse; i++)
	 visited[i] = FALSE;

      /* Initialize variables */
      caught = FALSE;
      numVisited = 0;
      startHouse = 2;

      /* Continue processing visits to houses until salesman is caught */
      while (!caught)
      {
	 /* Go to kth (startHouse-th) house */
	 currentHouse = startHouse;

	 /* Try to visit every kth house */
	 while ( (!caught) && (currentHouse <= lastHouse) )
	 {
	    /* If salesman tries the policeman's house, then he's caught. */
	    /* Otherwise, we count the house as visited, but only if it   */
	    /* hasn't been visited before.                                */
	    if (currentHouse == houseOfPoliceman)
	       caught = TRUE;
	    else if (!visited[currentHouse-1])
	    {
	       visited[currentHouse-1] = TRUE;
	       numVisited++;
	    }

	    /* Go to next house */
	    currentHouse = currentHouse + startHouse;
	 }

	 /* Go back to beginning and start with (k+1)th house */
	 startHouse++;
      }

      /* The salesman's been caught so output how many people were visited */
      printf("The salesman visits %d people before being caught.\n", numVisited);
   }

   /* Close the input file */
   fclose(infile);
}
