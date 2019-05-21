#define ASSIGN_BOOL(dest, val) InterlockedExchange(&dest, (long)val)
#define ASSIGN_POINTER(dest, val) InterlockedExchangePointer(&dest, val)
#define ASSIGN_LONG(dest, val) InterlockedExchange(&dest,val)

