#ifndef XQC_QMAN_H
#include "x.h"

#include "ast.h"
#include "logging.h"
#include "scanner.h"
#include "prefs.h"
#define XQC_QMAN_H

typedef struct {
  prefs_stPrefs* prefs;
  int rc;
} qman_stQMan;

qman_stQMan qman_fnNewQMan(prefs_stPrefs* prefs);

int qman_fnCompile(qman_stQMan* qman);

int qman_fnInit(prefs_stPrefs* prefs);

#endif
