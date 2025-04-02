/*Author: Ramona Namugenyi and  Huda Qazi
  Date: 4/4/2025
  Title: Weighted Running Application in C*/
  #include <stdio.h>
  #include <stdlib.h>
  
  void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean);
  void printRunningMeans(double* runningMean, int numMeas);
  
  int main() {
      char filename[256];  
      FILE* Inputp = NULL;
      int try;
      
      /*File opening with 3 tries*/ 
      for (try = 0; try < 3; try++) {
          printf("Enter the name of the input file: ");
          scanf("%255s", filename);
          Inputp = fopen(filename, "r");
          if (Inputp == NULL) {
              fprintf(stderr, "ERROR: Input file %s not opened\n", filename);
          } else {
              break;
          }
      }
      if (try == 3) {
          fprintf(stderr, "ERROR: too many failures opening input file\n");
          exit(1);
      }
  
      /*Check if file is empty*/ 
      fseek(Inputp, 0, SEEK_END);
      if (ftell(Inputp) == 0) {
          fprintf(stderr, "ERROR: input file is empty\n");
          fclose(Inputp);
          exit(1);
      }
      rewind(Inputp);
  
      /*Get numMeas with validation and 3 trials*/ 
      int numMeas;
      int tries;
      for (tries = 0; tries < 3; tries++) {
          printf("Enter the number of measurements: ");
          scanf("%d", &numMeas);
          if (numMeas > 0 && numMeas <= 40) break;
          printf("ERROR: numMeas is out of range\n");
          printf("enter 0<numMeas<=40\n");
      }
      if (tries == 3) {
          fprintf(stderr, "ERROR: too many failures reading the number of measurements\n");
          fclose(Inputp);
          exit(1);
      }
  
      /*Dynamic allocation of arrays*/ 
      double* measurements = malloc(numMeas * sizeof(double));
      double* weightedRunningMean = malloc(numMeas * sizeof(double));
      if (measurements == NULL || weightedRunningMean == NULL) {
          fprintf(stderr, "ERROR: Array was not successfully allocated\n");
          free(measurements);
          free(weightedRunningMean);
          fclose(Inputp);
          exit(1);
      }
  
      /*Reading measurements from file*/ 
      int actualCount = 0;
      while (actualCount < numMeas && fscanf(Inputp, "%lf", &measurements[actualCount]) == 1) {
          actualCount++;
      }
      fclose(Inputp);
  
      if (actualCount < numMeas) {
          printf("ERROR: fewer than numMeas measurements in the file\n");
          numMeas = actualCount;  /*Adjusting to actual count present in the file*/
      }
  
      /*Calculating running means*/ 
      WeightedRunningMean(measurements, weightedRunningMean, numMeas);
  
      printf("The running sums are\n");
      printRunningMeans(weightedRunningMean, numMeas);
  
      /*Freeing dynamically allocated arrays*/ 
      free(measurements);
      free(weightedRunningMean);
      return 0;
  }
  
  void WeightedRunningMean(double* measurements, double* weightedRunningMean, int numInRunningMean) {
      if (numInRunningMean <= 0) return;
      weightedRunningMean[0] = measurements[0];
      for (int k = 1; k < numInRunningMean; k++) {
          weightedRunningMean[k] = (weightedRunningMean[k-1]/2.0 + measurements[k])/1.5;
      }
  }
  
  void printRunningMeans(double* runningMean, int numMeas) {
      for (int i = 0; i < numMeas; i++) {
          printf("%10.2f", runningMean[i]);
          if ((i + 1) % 5 == 0 && i != numMeas - 1) {
              printf("\n");
          }
      }
      printf("\n");
  }