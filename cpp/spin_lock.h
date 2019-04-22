#include <pthread.h>

#ifdef _WIN32
#define ATOM_CMP_SET(lock,old,new)\
	(InterlockedCompareExchange(lock,new,old) == old)



#else

#endif
