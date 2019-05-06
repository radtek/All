#ifndef _TABLE_TASKINFO_
#define _TABLE_TASKINFO_

class CTaskInfo
{
public:
    CTaskInfo()
    {
        m_nSno = 0;
        m_szTaskname[0] = 0x00;
        m_cTasktype = 0x00;
        m_nCode = 0;
    }

    virtual ~CTaskInfo()
    {}

public:
    int     m_nSno;
    char    m_szTaskname[256];
    char    m_cTasktype;// '1' normal, '2' timmer
    char    m_nCode;

private:

};

#endif