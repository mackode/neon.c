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

maxret_t findMax(int N, float *xval);
maxret_t findMaxVec(int N, float *xval);

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
      if(++n >= argc) {
        printf("-n option requires integer argument\n");
        return(-1);
      } else {
        N = atoi(argv[n]);
      }
    } else {
      printf("Unknown argument [%s] ignoring\n", argv[n]);
    }
  }

  if(N < 0) N = 0;
  if(N > Nlimit) N = Nlimit;

  msize = ((size_t) N) * sizeof(float);
  N = (int)msize / sizeof(float);
  xval = (float *)malloc(msize);
  if(xval == NULL) {
    fprintf(stderr, "Memory allocation error: %s:%d\n", __FILE__, __LINE__);
    return(-1);
  }

  srand((unsigned int) time((time_t *)NULL));
  for(n = 0; n < N; n++) {
    xval[n] = ((float) (rand() % 200000)) * 5.0e-5;
  }

  time1 = getTimeInSec();
  for(n = 0; n < TIME_ITER; n++) {
    mret = findMax(N, xval);
  }
  duration = getTimeInSec() - time1;
  rate = ((double) TIME_ITER) * ((double) N) * 12.0e-9;
  rate /= duration;
  membw = ((double) TIME_ITER) * ((double) N) * 4.0e-6;
  membw /= duration;
  
  printf("Scalar: index = %d, max = %f, duration = %f msec\n", mret.ind, mret.val, 1e3 * duration / ((double) TIME_ITER));
  printf("    rate = %f GOps/s, memory = %f MB/s\n", rate, membw);

  time1 = getTimeInSec();
  for(n = 0; n < TIME_ITER; n++) {
    mret = findMaxVec(N, xval);
  }
  duration = getTimeInSec() - time1;
  rate = ((double) TIME_ITER) * ((double) N) * 12.0e-9;
  rate /= duration;
  membw = ((double) TIME_ITER) * ((double) N) * 4.0e-6;
  membw /= duration;

  printf("Neon: index = %d, max = %f, duration = %f msec\n", mret.ind, mret.val, 1e3 * duration / ((double) TIME_ITER));
  printf("    rate = %f GOps/s, memory = %f MB/s\n", rate, membw);

  if(xval != NULL) free((void *) xval);
  return(0);
}

maxret_t findMax(int N, float *xval) {
  int n;
  float x, x2, x3;
  float val;
  maxret_t mret = {-1, -1.0e38};

  const float A = 0.052;
  const float B = 0.24;
  const float C = 3.3;
  const float D = 10.1;

  for(n = 0; n < N; n++) {
    x = xval[n];
    x2 = x * x;
    x3 = x2 * x;
    val = A * x3 + B * x2 + C * x + D;

    if(val > mret.val) {
      mret.val = val;
      mret.ind = n;
    }
  }

  return(mret);
}

maxret_t findMaxVec(int N, float *xval) {
  maxret_t mret = {-1, -1.0e38};
  return(mret);
}

