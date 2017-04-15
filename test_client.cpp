
#define LOG_TAG "TestService"

/*参考：frameworks\av\mediaserver\Main_mediaserver.cpp*/

#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/wait.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <cutils/properties.h>
#include <utils/Log.h>
#include <unistd.h>

#include "IHelloService.h"
#include "IGoodByeService.h"


using namespace android;

/**
  * ./test_client hello
  * ./test_client readfile
  *  ./test_client hello some
  */

int main(int argc, char **argv)
{
	int cnt = 0;
	if(argc < 2) {
		 ALOGI("Usage:\n");
		 ALOGI("%s <hello|goodbye>\n",argv[0]);
		  ALOGI("%s <readfile>\n",argv[0]);
		 ALOGI("%s <hello|goodbye> <name>\n",argv[0]);
		 return -1;
	}

	/*getservice*/

	sp<ProcessState> proc(ProcessState::self());
	/*获得BpServiceManager*/
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder;
	if(strcmp(argv[1], "readfile") == 0 ) {
		binder  = sm->getService(String16("hello"));
		if(binder == 0)
		{
			 ALOGI("can not get hello service:\n");
				 return -1;
		}

		sp<IHelloService> service
				= interface_cast<IHelloService>(binder);
		int fd ;
		fd = service->get_fd();
		 ALOGI("client call get_fd:%d\n",fd);
		 lseek(fd, 0, SEEK_SET);
		char buf[500];
		int len = read(fd,buf, 500 );
		buf[len]='\0';
		
		 
		 ALOGI("client read buf:%s \n",buf);
	}
	else if(strcmp(argv[1], "hello") == 0 ) {
		binder  = sm->getService(String16("hello"));
			if(binder == 0)
			{
				 ALOGI("can not get hello service:\n");
				 return -1;
			}

			sp<IHelloService> service
				= interface_cast<IHelloService>(binder);

			if(argc < 3) {
				service->sayhello();
				ALOGI("call  say_hello\n");
			}
			else {
				cnt = service->sayhello_to(argv[2]);
				ALOGI("call  say_hello_to cnt:%d\n",cnt);
			}
	} else {
			binder  = sm->getService(String16("goodbye"));
			if(binder == 0)
			{
				 ALOGI("can not get hello service:\n");
				 return -1;
			}

			sp<IGoodByeService> service
				= interface_cast<IGoodByeService>(binder);

			if(argc < 3) {
				service->saygoodbye();
				ALOGI("call  say_hello\n");
			}
			else {
				cnt = service->saygoodbye_to(argv[2]);
				ALOGI("call  say_hello_to cnt:%d\n",cnt);
			}
	}
	
	return 0;
}


