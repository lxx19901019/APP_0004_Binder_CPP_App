
/*参考：frameworks\av\mediaserver\Main_mediaserver.cpp*/


#define LOG_TAG "HelloService"

//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>


#include "IHelloService.h"

using namespace android;

int main(void)
{
	/* add service*/

	/*while(1) {read date ,parse date, call func}*/
	/*打开驱动，mmap*/
	sp<ProcessState> proc(ProcessState::self());
	/*获得BpServiceManager*/
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
 	sm->addService(String16("hello"), new BnHelloService());

	/*循环体*/
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
	return 0;
}

