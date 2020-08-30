#include "../../include/logging.h"

void logging_fnLog(logging_stLog log, logging_eLevel lvl){
  if(log.level <= lvl){
    char* level;
    if(log.level == fatal){
      level = "FATAL";
    } else if(log.level == error){
      level = "ERROR";
    } else if(log.level == warn){
      level = "WARNING";
    } else if(log.level == info){
      level = "INFO";
    } else if(log.level == debug){
      level = "DEBUG";
    }
    printf("\n(%s)[%s]: %s", log.program, level, log.msg);
  }
}