#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <memory.h>
#include <time.h>
#include <sys/time.h>

#include <arm_neon.h>

#define TIME_ITER 5000

typedef struct {
  int ind;
  float val;
} maxret_t;

static inline double getTimeInSec(void) {
  double dtime = -1.0;
  struct timeval tv;

  if(gettimeofday(&tv, NULL) == 0) {
    dtime = ((double)tv.tv_sec) + ((double)tv.tv_usec) * 1e-6;
  }

  return(dtime);
}

maxret_t findMax(int N, float *xval) {
maxret_t finMaxVec(int N, float *xval) {

int main(int argc, char *argv[]) {
  int n;
  int N = 1024 * 1024 + 1;
  size_t msize;
  maxret_t mret = {-1, 0.0};
  float *xval = NULL;
  double time1, duration;
  double rate, membw;

  const int Nlimit = 256 * 1024 * 1024;
  
  for (n = 1; n < argc; n++) {
    if(strcmp(argv[n], "-h") == 0) {
      printf("neon [-h] [-n #samples]\n");
      return(0);
    } else if(strcmp(argv[n], "-n") == 0) {

    }
  }

  return(0);
}

maxret_t findMax(int N, float *xval) {
  maxret_t mret = {-1, -1.0e38};
  return(mret);
}

maxret_t finMaxVec(int N, float *xval) {
  maxret_t mret = {-1, -1.0e38};
  return(mret);
}

