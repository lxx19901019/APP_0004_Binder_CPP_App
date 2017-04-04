

/*参考：frameworks\av\include\media\IMediaPlayerService.h*/

#ifndef ANDROID_IGOODBYESERVEICE_H
#define ANDROID_IGOODBYESERVEICE_H

#include <utils/Errors.h>  // for status_t
#include <utils/KeyedVector.h>
#include <utils/RefBase.h>
#include <utils/String8.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>


#define HELLO_SVR_CMD_SAYGOODBYE      0
#define HELLO_SVR_CMD_SAYGOODBYE_TO 	1

namespace android {



class IGoodByeService: public IInterface 
{
	public:
    	DECLARE_META_INTERFACE(GoodByeService);
		virtual void saygoodbye(void) = 0;
		virtual int saygoodbye_to(const char *name) = 0;
};


class BnGoodByeService: public BnInterface<IGoodByeService>
{
public:
    status_t    onTransact( uint32_t code,
                                    const Parcel& data,
                                    Parcel* reply,
                                    uint32_t flags = 0);
	void saygoodbye(void) ;
	int saygoodbye_to(const char *name) ;
};

}

#endif



