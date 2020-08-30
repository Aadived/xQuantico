#include "xqc/include/x.h"

#include "xqc/include/logging.h"
#include "xqc/include/prefs.h"
#include "xqc/include/qman.h"

int main(int argc, char** argv){
  logging_stLog log = {.program = "xQCli", .msg = ""};
  
	if(argc==1){
	  log.level = info;
	  log.msg = "REPL Mode is unavailabe for now\n\n";
	  logging_fnLog(log, info);
	} else {
	  prefs_stPrefs prefs = prefs_fnParseArgs(argc, argv);
	  
	  printf("\nMode: %d\nEmit: %d\nsrcPath: %s\nsrc: %s\noutPath: %s\nout: %s\nCMD: %s\nisError: %d\nLogLevel: %d\nError: %s\nShowHelp: %d\n\n", prefs.buildType, prefs.buildEmit, prefs.srcPath, prefs.srcName, prefs.outPath, prefs.outName, prefs.cmd, prefs.isErr, prefs.logLevel, prefs.error, prefs.showHelp);
	  
	  if(prefs.showHelp){
	    printf("Showing help for `%s`", prefs.cmd);
	  } else if(prefs.isErr){
	    char h[] = " help";
	    if(!strcmp(prefs.cmd, "")){
	      strcpy(h, "help");
	    }
	    { // Unsafe
	      log.level = error;
	      char* msg = malloc(sizeof(char*));
	      sprintf(msg, "%s\n\nRun `%s %s%s` to display usage help.\n\n", prefs.error, argv[0], prefs.cmd, h);
	      log.msg = msg;
	      logging_fnLog(log, prefs.logLevel);
	      free(msg);
	    }
	  } else {
	    log.level = debug;
  	  log.msg = "initiating QMan...\n";
  	  logging_fnLog(log, prefs.logLevel);
  	  
	    int rc = qman_fnInit(&prefs);
	    
	    { // Unsafe
	      log.level = debug;
	      char* msg = malloc(sizeof(char*));
	      sprintf(msg, "QMan returned code `%d`\n\n", rc);
	      log.msg = msg;
	      logging_fnLog(log, prefs.logLevel);
	      free(msg);
	    }
	  }
	}
	return 0;
}