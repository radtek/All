#include <pthread.h>

#ifdef _WIN32
#define ATOM_CMP_SET(lock,old,new)\
	(InterlockedCompareExchange(lock,new,old) == old)

#else
#define ATOM_CMP_SET(lock,old,new)\
	(__sync_bool_compare_and_swap(lock,old,new))

#endif
