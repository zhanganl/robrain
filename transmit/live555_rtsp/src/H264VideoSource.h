#ifndef _H264VideoSource_H  
#define _H264VideoSource_H  
  

#include "BasicUsageEnvironment.hh"
#include "GroupsockHelper.hh"
#include "liveMedia.hh"
#include "FramedSource.hh"  



#define FRAME_PER_SEC 25  
  
class H264VideoSource : public FramedSource  
{  
public:  
    H264VideoSource(UsageEnvironment & env);  
    ~H264VideoSource(void);  
  
public:  
    virtual void doGetNextFrame();  
    virtual unsigned int maxFrameSize() const;  
  
    static void getNextFrame(void * ptr);  
    void GetFrameData();  
  
private:  
    void *m_pToken;  
    char *m_pFrameBuffer;  
    int  m_hFifo;  
};  
  
#endif  


