#ifndef XQC_LOGGING_H
#include "x.h"
#define XQC_LOGGING_H

typedef enum logging_eLevel {fatal=1, error=2, warn=3, info=4, debug=5} logging_eLevel;

typedef struct {
  logging_eLevel level;
  char* program;
  char* msg;
} logging_stLog;

void logging_fnLog(logging_stLog log, logging_eLevel lvl);

#endif