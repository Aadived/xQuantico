#ifndef XQC_PREFS_H
#include "x.h"

#include "logging.h"
#define XQC_PREFS_H

typedef enum prefs_eBuildType {basic, adv} prefs_eBuildType;
typedef enum prefs_eEmitType {bin, ASM, IR} prefs_eEmitType;

typedef struct {
  prefs_eBuildType buildType;
  prefs_eEmitType buildEmit;
  char* srcPath;
  char* srcName;
  char* srcBasePath;
  char* outPath;
  char* outName;
  char* outBasePath;
  char* cmd;
  bool isErr;
  logging_eLevel logLevel;
  char* error;
  bool showHelp;
} prefs_stPrefs;

prefs_stPrefs prefs_fnParseArgs(int argc, char** argv);

#endif