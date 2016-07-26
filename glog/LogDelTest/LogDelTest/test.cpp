#include "LogDelOperate.h"

int main()
{
	CLogDelOperate logDelOperate;
	char szAppPath[MAX_PATH+1]; 

	GetModuleFileName(NULL, szAppPath, MAX_PATH);
	  
	string  sInstancePath(szAppPath);
	int pos = sInstancePath.rfind('\\');
	if( pos >= 0 ) 
	{
		sInstancePath = sInstancePath.substr(0,pos + 1);
	}
	sInstancePath += "\Log";

	logDelOperate.DeleteBackupLogFile(sInstancePath,3);   //C:/Users/Administrator/Desktop/LogDelTest/Debug/log

	return 0;
}