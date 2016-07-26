#ifndef _LOG_DEL_OPERATE_H_
#define _LOG_DEL_OPERATE_H_
/**
* @file LogDelOperate.h  ��ʱɾ����־��
* DATE 2015-9-23
* @author allenhfchen
*/ 
/************************INCLUDE FILES*************************/
#include <windows.h>
#include <string>
#include <vector>
#include <time.h>
#include <io.h>
#include <iostream>
using namespace std;


class CLogDelOperate
{
public:
	CLogDelOperate();
	virtual ~CLogDelOperate();
	void DeleteBackupLogFile(const string & strLogPath, unsigned int keep_days, const string& strFileType=".log"); //Ĭ���Ǵ���ģ����׺

private:
	void GetFileList(const string& strFullPath, const string& strFileType, unsigned int keep_Time, vector<string> & vFileInfoList, 
		int nMaxFileNum, int & nCurrentCount);

};
#endif  //_LOG_DEL_OPERATE_H_