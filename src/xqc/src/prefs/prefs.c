#include "../../include/prefs.h"

prefs_stPrefs prefs_fnParseArgs(int argc, char** argv){
  int idx = 1, flg = 0, flg2 = -1;
  prefs_stPrefs prefs = {.buildType=basic, .buildEmit=bin, .isErr=false, .logLevel=debug, .showHelp=false};
  
  if(!strcmp(argv[idx], "dev")){
    prefs.buildType = adv;
    idx+=1;
  }
  
  while(idx<argc){
    if(flg==0){
      if(prefs.buildType==adv){
        if(!strcmp(argv[idx], "-e")||!strcmp(argv[idx], "--emit")){
          if(idx+1<argc){
            if(!strcmp(argv[idx+1], "bin")){
              prefs.buildEmit = bin;
            } else if(!strcmp(argv[idx+1], "asm")){
              prefs.buildEmit = ASM;
            } else if(!strcmp(argv[idx+1], "ir")){
              prefs.buildEmit = IR;
            } else {
              prefs.error = "invalid argument for flag `--emit`";
              prefs.cmd = "dev"; prefs.isErr = true;
              break;
            }
          } else {
            prefs.error = "argument missing for flag `--emit`";
            prefs.cmd = "dev"; prefs.isErr = true;
            break;
          }
          idx+=2;
        } else {
          if(argv[idx][0]=='-'){
            prefs.error = "invalid flag"; flg+=1;
            prefs.cmd = "dev"; prefs.isErr = true;
            break;
          }
        }
      }
      
      if(!strcmp(argv[idx], "build")||!strcmp(argv[idx], "run")){
        prefs.cmd = argv[idx];
        idx+=1; flg+=1;
      } else if(!strcmp(argv[idx], "help")) {
        if(idx+1<argc){
          prefs.error = "too many arguments for `help`";
          prefs.cmd = ""; prefs.isErr = true; flg+=1;
          break;
        } else {
          if(prefs.buildType==adv){
            prefs.cmd = "dev";
          } else {
            prefs.cmd = argv[0];
          }
          prefs.showHelp = true; idx+=1; flg+=1;
        }
      } else {
        if(prefs.buildType==adv){
          prefs.cmd = "dev";
        } else {
          prefs.cmd = "";
        }
        if(argv[idx][0]=='-'){
          prefs.error = "invalid flag";
        } else {
          prefs.error = "invalid command";
        }
        prefs.isErr = true; flg+=1;
        break;
      }
    } else {
      if(!strcmp(argv[idx], "help")){
        if(idx+1<argc){
          prefs.error = "too many arguments given for `help`";
          prefs.isErr = true; break;
        } else {
          prefs.showHelp = true;
        }
        idx+=1;
      } else {
        if(!strcmp(prefs.cmd, "build")){
          if(!strcmp(argv[idx], "-o")||!strcmp(argv[idx], "--out")){
            if(idx+1<argc){
              prefs.outPath = argv[idx+1]; flg2+=1;
              idx+=2;
              if(idx<argc){
                prefs.error = "too many arguments given for flag `--out`";
                prefs.isErr = true; break;
              }
            } else {
              prefs.error = "argument missing for flag `--out`";
              prefs.isErr = true; break;
            }
          } else {
            if(idx+1<argc){
              if(!strcmp(argv[idx+1], "-o")||!strcmp(argv[idx+1], "--out")){
                    prefs.srcPath = argv[idx]; flg2=1;
              } else {
                prefs.error = "too many values given for `SRC`";
                prefs.isErr = true; break;
              }
            } else {
              prefs.srcPath = argv[idx]; flg2=1;
            }
            idx+=1;
          }
        } else if(!strcmp(prefs.cmd, "run")){
          if(idx+1<argc){
            prefs.error = "too many values given for `SRC`";
            prefs.isErr = true; break;
          } else {
            prefs.srcPath = argv[idx]; flg2=1;
          }
          idx+=1;
        }
      }
    }
  }
  
  if(!prefs.isErr){
    prefs.error = "";
  }
  if(flg2==-1){
    prefs.srcPath="(CWD)";
    prefs.outPath="(CWD)";
  } else if(flg2==0){
    prefs.srcPath="(CWD)";
  } else if(flg2==1){
    prefs.outPath=prefs.srcPath;
  }
  
  return prefs;
}