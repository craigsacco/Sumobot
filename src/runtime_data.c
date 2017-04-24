#include <runtime_data.h>
#include <ch.h>

struct SumoRuntimeData_t sumoRuntimeData;
mutex_t sumoRuntimeDataMutex;

void sumoRuntimeDataInit(void)
{
    // initialise mutex
    chMtxObjectInit(&sumoRuntimeDataMutex);
}

void sumoRuntimeDataLock(void)
{
    // lock the mutex
    chMtxLock(&sumoRuntimeDataMutex);
}

void sumoRuntimeDataUnlock(void)
{
    // unlock the mutex
    chMtxUnlock(&sumoRuntimeDataMutex);
}
