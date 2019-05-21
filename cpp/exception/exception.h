#ifndef _PLAT_EXCEPTION_
#define _PLAT_EXCEPTION_

#include <string>
class Exception
{
public:
	Exception()
	{};

	~Exception()
	{};

	virtual void getMsg() const=0;
}


#endif
