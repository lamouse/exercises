#ifndef NET_RTT_HPP
#define NET_RTT_HPP

#include <inttypes.h>

#define RTT_DEFAULT_RXTMIN  2            //min retransmit timeout value int seconds
#define RTT_DEFAULT_RXTMAX  60           //max retransmit timeout value, in seconds 
#define RTT_MAXNREXMT       3            //max #times to retransmit

namespace net::rtt {

    /**
     * internet RTT
     *
     * 
     */
    struct rtt_info
    {
        float rtt_rtt;      //most recent measured RTT, in seconds
        float rtt_srtt;     //smoothed RTT estimator, in seconds
        float rtt_rttvar;   //smoothed mean deviation, in seconds
        float rtt_rto;      //current RTO to use, in seconds
        u_int32_t rtt_base; //# sec since 1/1/1970 at start
    };
    
    class Rtt
    {
    private:
        rtt_info info;
        int max_rtt;
        int nrexmt;     // #times retransmitted 0, 1, 2, ...
        int current_times = 0;
        uint32_t last_ts;
        void rtt_minmax();
        void rtt_init();
        uint32_t get_ts();
    public:
        /**
         * default max rtt time see RTT_DEFAULT_RXTMAX
         */
        Rtt();
        // max rtt times, and timeout times
        Rtt(int max_rtt_time, int times);
        //return current milliseconds - init milliseconds(init time is seconds) and set last ts
        uint32_t ts();
        /**
         * return RTO(second)
         * @return int 
         */
        int start()noexcept;

        /**
         * @brief 判断是否超时，该函数有个副作用当未超时时rtt_info的rtt_rto = rtt_rto*2
         * 
         * @return true 
         * @return false 
         */
        bool is_timeout() noexcept;
        void stop();
        void newpack() noexcept;
        ~Rtt();
    };    

}

#endif
