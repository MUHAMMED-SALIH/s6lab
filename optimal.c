
#include<stdio.h>
#define MAX_PAGE 25 // Define a constant, program can support only this MAX_PAGE number of pages.
#define MAX_FRAME 25 // Define a constant, program can support only this MAX_FRAME number of frames.

/**
 * Function main returns 0 on success.
 */
int main()
{
 // Declare arrays for pages and frames and distance_from_future_occurance
 int pages[MAX_PAGE], frames[MAX_FRAME], distances[MAX_PAGE];
 
 // Number of pages, frames, page faults variables
 int numberPages, numberFrames, numberPageFaults = 0;
 
 // Other variables
 int i, j, temp, flag, found, lastFilledFrame, index, highestDistance;
 
 // Get number of frames from user
 printf("Enter number of frames (max limit is %d): ", MAX_FRAME);
 scanf("%d", &numberFrames);
 printf("You provided number of frames: %d\n", numberFrames);
 
 // Initialize frames array with -1 values and set lastFilledFrame value to -1
 for(i = 0; i < numberFrames; i++) frames[i] = -1;
 lastFilledFrame = -1;
 
 // Get pages from user
 printf("Enter pages (enter -999 to exit, max number of pages limit is %d):\n", MAX_PAGE);
 numberPages = 0;
 for(i = 0; i < MAX_PAGE; i++)
 {
  scanf("%d", &temp);
  if(temp == -999 || numberPages == MAX_PAGE) break;
  pages[i] = temp;
  numberPages++;
 }
 printf("You provided number of pages: %d\n", numberPages);
 
 // Traverse the sequence of pages according Optimal Page Replacement Algorithm
 for(i = 0; i < numberPages; i++) // For every page
 {
  flag = 0; // Flag to show availability of page in frame
 
  // Get the availability of required page in frame
  for(j = 0; j < numberFrames; j++) // For every frame
  {
   if(frames[j] == pages[i]) // If page found in frame
   {
    flag = 1; // Set flag to 1, showing that page is available in frame
    printf("\t"); // Print tab space instead "FAULT" word
    break; // Break the loop
   }
  }
   
  // If page is not available in frame, replace some page by required page and print "FAULT" word
  if(flag == 0) 
  {
   if (lastFilledFrame == numberFrames-1) // If frames fully filled
   {
    // For every frame containing page, calculate distances to future occurance
    for(j = 0; j < numberFrames; j++)
    {
     for(temp = i + 1; temp < numberPages; temp++) // For every future page
     {
      distances[j] = 0; // Set this page_occurances_in_future to zero, showing no occurance
  
      if (frames[j] == pages[temp]) // If frame containing page matches to future occuring page
      {
       distances[j] = temp - i; // Store distance
       break;
      }
     } // For every future page loop ends here
    } // Loop for calculating distances ends here
    
    // Choose best candidate index for page replacement in frame, this best candidate is not occuring in future
    found = 0;
    for(j = 0; j < numberFrames; j++) // For every frame
    {
     if(distances[j] == 0) // If page's distance value is 0, means if no occurance in future
     {           // Or if frame value is -1, means empty frame 
      index = j; // Set this frame index to index variable
      found = 1; // Set to 1, means a page not occuring in future is found
      break;
     }
    }
   }
   else // If frames has not fully filled, best candidate is blank frame
   {
     index = ++lastFilledFrame; // Set blank frame's index to index variable
     found = 1; // Set to 1, means a suitable frame index found
   }
   
   // If still not choosed best candidate, get best candidate that is having highest distance in future
   if(found == 0)
   {
    highestDistance = distances[0];
    index = 0;
    for(j = 1; j<numberFrames; j++) // For every frame
    {
     if(highestDistance < distances[j])
     {
      highestDistance = distances[j];
      index = j; // In last, index will contain farest distanced element's index in current frames
     }
    }
   }
   
   // Do the page replacement
   frames[index] = pages[i]; // Replace the identified index located page by required page
   printf("FAULT\t"); // Print "FAULT"
   numberPageFaults++; // Increment number of page faults
  }
  
  // Print the pages that are present in current frames
  for(j = 0; j < numberFrames; j++)
  {
   if(frames[j] != -1) printf("%d\t", frames[j]);
  }
  printf("\n");
 }
 
 // Print number of page faults.
 printf("Number of page faults = %d\n", numberPageFaults);
 
 return 0;
}
