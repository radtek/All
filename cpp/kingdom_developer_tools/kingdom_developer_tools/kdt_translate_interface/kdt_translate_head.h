#ifndef _KDT_TRANSLATE_HEAD_
#define _KDT_TRANSLATE_HEAD_

#define ATOM_BUSI_EXPORTS

#include "compile_def.h"
#include "type_def.h"
#include "public_func.h"
#include <vector>

/* 支持语言列表
auto 自动检测 ; zh	中文 ; en	英语 ; yue	粤语 ; wyw	文言文 ; jp	日语 ; kor	韩语 ;
fra	法语 ; spa	西班牙语 ; th	泰语 ; ara	阿拉伯语 ; ru	俄语 ; pt	葡萄牙语 ;
de	德语 ; it	意大利语 ; el	希腊语 ; nl	荷兰语 ; pl	波兰语 ; bul	保加利亚语 ;
est	爱沙尼亚语 ; dan	丹麦语 ; fin	芬兰语 ; cs	捷克语 ; rom	罗马尼亚语 ;
slo	斯洛文尼亚语 ; swe	瑞典语 ; hu	匈牙利语 ; cht	繁体中文 ; vie	越南语 ;
*/
typedef struct st_param
{
	st_param()
	{
		m_szAppId[0] = 0x00;
		m_szSecret_key[0] = 0x00;
		m_szLanguageFrom[0] = 0x00;
		m_szLanguageTo[0] = 0x00;
		m_nErrorCode = 0;
	}
	dt_vchar128			m_szAppId;                     //appid
	dt_vchar128			m_szSecret_key;                //密钥
	dt_vchar2			m_szLanguageFrom;              //来源语言
	dt_vchar2			m_szLanguageTo;                //目标语言
	std::vector<std::string> m_vcTarget;               //待翻译语句
	std::vector<std::string> m_vcResult;               //结果
	dt_int              m_nErrorCode;
} trans_param;

extern "C"
{
	ATOM_BUSI_FUNC void kdt_trans_func(trans_param *ptr_param);
};

#endif