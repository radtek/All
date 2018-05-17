#include "toolplatform.h"
#include "qt_windows.h"
#include "../kdt_translate_interface/kdt_translate_head.h"
#pragma comment(lib,"../debug/kdt_translate_interface.lib")
#include <QDebug>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	qDebug() << "1";
	trans_param obj_param;
	strcpy(obj_param.m_szAppId,"20180309000133299");                    //appid
	strcpy(obj_param.m_szSecret_key,"VDZlUclYn255xwCSi7X2");            //密钥
	strcpy(obj_param.m_szLanguageFrom,"zh");							//来源语言
	strcpy(obj_param.m_szLanguageTo,"en");								//目标语言
	obj_param.m_vcTarget.push_back(std::string("苹果"));
	obj_param.m_vcTarget.push_back(std::string("栗子树"));
	obj_param.m_vcTarget.push_back(std::string("分心"));
	obj_param.m_vcTarget.push_back(std::string("指令无效"));
	obj_param.m_vcTarget.push_back(std::string("湘潭大学"));

	kdt_trans_func(&obj_param);
	if (obj_param.m_nErrorCode == 0)
	{
		for (std::vector<std::string>::iterator iter = obj_param.m_vcResult.begin(); iter != obj_param.m_vcResult.end(); iter++)
		{
			qDebug() <<QString("翻译结果:")<< iter->c_str();
		}
	}
	ToolPlatform w;
	w.show();
	return a.exec();
}
