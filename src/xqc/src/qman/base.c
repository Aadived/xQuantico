#include "../../include/qman.h"

int qman_fnInit(prefs_stPrefs* prefs){
  logging_stLog log = {.program = "QMan"};
  
  qman_stQMan qman = qman_fnNewQMan(prefs);
  
  if(qman.rc){
    log.level = fatal;
    log.msg = "init failed\n";
    logging_fnLog(log, prefs->logLevel);
    
    return 1;
  } else {
    log.level = debug;
    log.msg = "init success";
    logging_fnLog(log, prefs->logLevel);
    
    log.level = debug;
    log.msg = "initiating xQCompiler...\n";
    logging_fnLog(log, prefs->logLevel);
    
    int rc = qman_fnCompile(&qman);
    
    { // Unsafe
      log.level = debug;
      char* msg = malloc(sizeof(char*));
      sprintf(msg, "xQCompiler returned code `%d`\n", rc);
      log.msg = msg;
      logging_fnLog(log, prefs->logLevel);
      free(msg);
    }
    
    return rc;
  }
}