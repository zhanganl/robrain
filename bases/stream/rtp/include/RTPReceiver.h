#ifndef __RTPRECEIVER_H__
#define __RTPRECEIVER_H__

#include "rtcpapppacket.h"
#include "rtptimeutilities.h"
#include "rtpaddress.h"
#include "rtpsourcedata.h"
#include "rtpsession.h"


using namespace jrtplib;


class CRTPReceiver : public RTPSession  
{  
// protected:  
//     void OnPollThreadStep();  
//     void ProcessRTPPacket(const RTPSourceData &srcdat, const RTPPacket &rtppack);  
//     void OnRTCPCompoundPacket(RTCPCompoundPacket *pack, const RTPTime &receivetime, const RTPAddress *senderaddress);  
      
// public:  
//     CThreadSafeArray m_ReceiveArray;  
//     void InitBufferSize();  
  
// private:  
//     CVideoData* 	m_pVideoData;  
//     unsigned char 	m_buffer[BUFFER_SIZE];  
//     int 			m_current_size;  
};


#endif