
/*参考：frameworks\av\mediaserver\Main_mediaserver.cpp*/


#define LOG_TAG "TestService"

//#define LOG_NDEBUG 0

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "IHelloService.h"
#include "IGoodByeService.h"
using namespace android;


/*usage:test_server <file>*/
int main(int argc, char *argv[])
{
	int fd;

	if(argc == 2)
		fd = open(argv[1], O_RDWR);
	/* add service*/

	/*while(1) {read date ,parse date, call func}*/
	/*打开驱动，mmap*/
	sp<ProcessState> proc(ProcessState::self());
	/*获得BpServiceManager*/
    sp<IServiceManager> sm = defaultServiceManager();
    ALOGI("ServiceManager: %p", sm.get());
 	sm->addService(String16("hello"), new BnHelloService(fd));
	sm->addService(String16("goodbye"), new BnGoodByeService());
	/*循环体*/
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
	return 0;
}

