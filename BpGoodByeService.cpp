
#define LOG_TAG "GoodByeService"

/*参考：frameworks\av\libmedia\IMediaPlayerService.cpp*/

#include "IGoodByeService.h"


namespace  android {
	class BpGoodByeService: public BpInterface<IGoodByeService>
	{
		public:
			BpGoodByeService(const sp<IBinder>& impl)
				: BpInterface<IGoodByeService>(impl)
			{
			}
		void saygoodbye()
		{   
			Parcel data,reply;
			data.writeInt32(0);
			

	        remote()->transact(HELLO_SVR_CMD_SAYGOODBYE, data, &reply);	
		}

		int saygoodbye_to(const char *name)
		{
			Parcel data,reply;
			data.writeInt32(0);
			data.writeString16(String16(name));
	        remote()->transact(HELLO_SVR_CMD_SAYGOODBYE_TO, data, &reply);

			return reply.readInt32();
		}

	};

IMPLEMENT_META_INTERFACE(GoodByeService, "android.media.IGoodByeService");


}


