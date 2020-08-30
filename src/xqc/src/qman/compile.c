#include "../../include/qman.h"

int qman_fnCompile(qman_stQMan* qman){
  logging_stLog log = {.program = "xQCompiler"};
  
  log.level = debug;
  log.msg = "init success";
  logging_fnLog(log, qman->prefs->logLevel);
  
  log.level = debug;
  log.msg = "initiating xQScanner + xQParser...\n";
  logging_fnLog(log, qman->prefs->logLevel);
  
  ast_stSrcTree res = scanner_fnScanAndParseFiles(qman->prefs);
  
  { // Unsafe
    log.level = debug;
    char* msg = malloc(sizeof(char*));
    sprintf(msg, "xQScanner returned code `%d`\n", res.rc);
    log.msg = msg;
    logging_fnLog(log, qman->prefs->logLevel);
    free(msg);
  }
  
  if(res.rc){
    return res.rc;
  } else {
    log.level = debug;
    log.msg = "initiating xQCodegen...\n";
    logging_fnLog(log, qman->prefs->logLevel);
    
    int rc = 1; //codegen_fnGenerate(&res, qman->prefs);
    
    { // Unsafe
      log.level = debug;
      char* msg = malloc(sizeof(char*));
      sprintf(msg, "xQCodegen returned code `%d`\n", rc);
      log.msg = msg;
      logging_fnLog(log, qman->prefs->logLevel);
      free(msg);
    }
    
    return rc;
  }
}