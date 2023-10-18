#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * ans = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("could not open the file!");
    exit(EXIT_FAILURE);
  }

  char * line = NULL;
  size_t sz = 0;
  char * ans_value = NULL;
  while (getline(&line, &sz, f) != -1) {
    char * p = strchr(line, '\n');
    if (p != NULL) {
      *p = '\0';
    }
    ans_value = lookupValue(kvPairs, line);
    //    printf("%s\n", ans_value);
    addCount(ans, ans_value);
  }
  free(line);
  if (fclose(f) != 0) {
    perror("could not close the file!");
    exit(EXIT_FAILURE);
  }
  return ans;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 3) {
    perror("no enough input files!");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    //   (call this result c)

    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);

    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    if (f == NULL) {
      fprintf(stderr, "could not open the file:%s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("could not close the file!");
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c

    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);

  return EXIT_SUCCESS;
}
