#include "../../include/qman.h"

qman_stQMan qman_fnNewQMan(prefs_stPrefs* prefs){
  return (qman_stQMan){
    .prefs = prefs,
    .rc = 0,
  };
}