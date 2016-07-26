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

			if(_A_SUBDIR != file_data.attrib)    //�������Ŀ¼�ļ����ͽ����ļ��������Ϣ����lstFilesList��
			{
				if(strstr(file_data.name, strFileType.c_str()) == NULL)
					continue;

				string strFileName = strFullPath + "/" + file_data.name;
				time_t writeTime = file_data.time_write;
				time_t keepTime;

                keepTime = time(NULL) - keep_Time*24*60*60;  //����������,������־���ޣ��������
		
				if(writeTime < keepTime)
				{
					//��������ʱ�䣬��Ҫɾ��
					//logger.info("[file delete] need remove file(%s),current count=%d\n", strFileName.c_str(), nCurrentCount);
					vFileInfoList.push_back(strFileName);
					if(++nCurrentCount >= nMaxFileNum)
					{
						::_findclose(hFile);
						nCurrentCount = 0;   //����ǰ������Ҫ��գ�
						return;
					}
				}
			}
			else    //�����Ŀ¼�ļ����͵ݹ����GetFileList��������ȡĿ¼�е��ļ�
			{
				if(file_data.name[0] == '.')  
					continue;           //ÿ��Ŀ¼���涼������Ĭ��Ŀ¼����..��.�ֱ��ʾ��һ��Ŀ¼�͵�ǰĿ¼
				string strSubPath = strFullPath + "/" + file_data.name;	
				GetFileList(strSubPath, strFileType, keep_Time, vFileInfoList, nMaxFileNum, nCurrentCount);
			}
		}
		while(0 == _findnext(hFile, &file_data));
		::_findclose(hFile);
		nCurrentCount = 0;//����ǰ������Ҫ��գ�
	}
}

