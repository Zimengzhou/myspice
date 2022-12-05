#include <stdio.h>
#include "myspice.h"
#include <string.h>

char *aUser;
bool iserror = false;

void setUser(const char* username)
{
    if(username !=NULL)
        strcpy(aUser, username);
    else
        aUser = "myspice";
}
//定义ngSpice所需回调函数
//ngSPICE向外输出函数，比如一些错误打印
static int ngPrint(char* what,int id,void* user)
{
    if (strncasecmp(what,"stderr ",7)==0)
    {
        printf("\033[31m%s\n\033[0m",what+7);
        iserror = true;//occurs errors.
    }
    else if (strncasecmp(what,"stdout ",7)==0)
    {
        printf(what + 7);
    }
    printf("\n");
    
    return 0;
}
static int ngsendStat(char *what, int id, void *user)
{
    printf(what);
    printf("\n");
    return 0;
}
static int ngcontrolledExit(int stat, NG_BOOL immediate, NG_BOOL beExiting, int id, void* user)
{
    iserror = true;//occur errors.
    return 0;
}
static int ngBGThreadRunning( NG_BOOL Finished, int id, void* user )
{
    printf("Finished Or Running:%d\n",Finished);
    return 0;
}

//初始化ngspice.dll
void spiceInit()
{
    
    ngSpice_Init(&ngPrint, &ngsendStat, &ngcontrolledExit, NULL, NULL, &ngBGThreadRunning, aUser);
    loadSpinit("../src/lib/ngspice/spinit");
    ngSpice_Command( "unset interactive" );
    ngSpice_Command( "set noaskquit" );
    ngSpice_Command( "set nomoremode" );
    ngSpice_Command( "set ngbehavior=ltps" );
    //spinit文件,一系列的初始化命令
    
    ngSpice_Command("source ../example/laser_driver.cir");
    ngSpice_Command("bg_run");//启动仿真
}
/**
 * @brief 加载spinit文件
 * @param spinitfilename 文件路径
 */
bool loadSpinit(const char* spinitfilename)
{
    char cmd[200];
    FILE *spinitf;
    spinitf = fopen(spinitfilename, "r");
    printf(spinitfilename);
    while(!feof(spinitf))
    {
        fgets(cmd, 200, spinitf);
        ngSpice_Command(cmd);
    }
    fclose(spinitf);
    return true;
}