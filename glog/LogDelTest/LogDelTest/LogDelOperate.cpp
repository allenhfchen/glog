#include "LogDelOperate.h"

CLogDelOperate::CLogDelOperate()
{

}

CLogDelOperate::~CLogDelOperate()
{

}

void CLogDelOperate::DeleteBackupLogFile(const string & strLogPath, unsigned int keep_days)
{
	vector<string>  vFileInfoList;
	int count = 0;
	GetFileList(strLogPath, string(".log"), keep_days, vFileInfoList, 100, count);

	for(size_t i = 0; i < vFileInfoList.size(); i++)
	{
		::remove(vFileInfoList[i].c_str());
	}
}

void CLogDelOperate::GetFileList(const string& strFullPath, const string& strFileType, unsigned int keep_Time, vector<string> & vFileInfoList, int nMaxFileNum, int & nCurrentCount)
{
	string strCondition = strFullPath + "\\*.log";
	struct _finddata_t file_data;
	intptr_t hFile;
	hFile = ::_findfirst(strCondition.c_str(), &file_data);
	if(-1L != hFile )
	{
		do{
			printf("GetFileList(%s), file :%s, attrib=%d.current count=%d\n", strFullPath.c_str(), file_data.name, file_data.attrib, nCurrentCount);

			if(_A_SUBDIR != file_data.attrib)    //如果不是目录文件，就将该文件的相关信息放入lstFilesList中
			{
				if(strstr(file_data.name, strFileType.c_str()) == NULL)
					continue;

				string strFileName = strFullPath + "/" + file_data.name;
				time_t writeTime = file_data.time_write;
				time_t keepTime;

                keepTime = time(NULL) - keep_Time*24*60*60;  //按天数保存,保存日志期限，换算成秒
		
				if(writeTime < keepTime)
				{
					//超过保留时间，需要删除
					//logger.info("[file delete] need remove file(%s),current count=%d\n", strFileName.c_str(), nCurrentCount);
					vFileInfoList.push_back(strFileName);
					if(++nCurrentCount >= nMaxFileNum)
					{
						::_findclose(hFile);
						nCurrentCount = 0;   //返回前计数器要清空！
						return;
					}
				}
			}
			else    //如果是目录文件，就递归调用GetFileList函数，读取目录中的文件
			{
				if(file_data.name[0] == '.')  
					continue;           //每个目录下面都有两个默认目录就是..和.分别表示上一级目录和当前目录
				string strSubPath = strFullPath + "/" + file_data.name;	
				GetFileList(strSubPath, strFileType, keep_Time, vFileInfoList, nMaxFileNum, nCurrentCount);
			}
		}
		while(0 == _findnext(hFile, &file_data));
		::_findclose(hFile);
		nCurrentCount = 0;//返回前计数器要清空！
	}
}

