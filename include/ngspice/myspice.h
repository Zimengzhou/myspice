#ifndef MYSPICE_H
#define MYSPICE_H
#include "sharedspice.h"

extern char *aUser;
extern bool iserror;

static int ngPrint(char* what,int id,void* user);//ngSPICE向外输出函数，比如一些错误打印
static int ngsendStat(char *what, int id, void *user); //仿真情况和百分比（进度？）
static int ngcontrolledExit(int stat, NG_BOOL immediate, NG_BOOL beExiting, int id, void* user);//退出信息
static int ngBGThreadRunning( NG_BOOL Finished, int id, void* user );//后台运行
bool loadSpinit(const char *spinitfilename);
void spiceInit();

#endif