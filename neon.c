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

}

int main(int argc, char *argv[]) {
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

