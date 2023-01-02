#pragma once
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define Info(...)                                                              \
  do {                                                                         \
    fprintf(stdout, "[Info] ");                                                \
    fprintf(stdout, __VA_ARGS__);                                              \
    fflush(stdout);                                                            \
  } while (0)

#define Warn(...)                                                              \
  do {                                                                         \
    fprintf(stderr, "[Error][%d] ", errno);                                    \
    fprintf(stderr, __VA_ARGS__);                                              \
    fflush(stdout);                                                            \
  } while (0)

#define Panic(...)                                                             \
  do {                                                                         \
    fprintf(stderr, "[Panic][%d] ", errno);                                    \
    fprintf(stderr, __VA_ARGS__);                                              \
    exit(1);                                                                   \
  } while (0)
