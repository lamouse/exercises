#include <ctime>
#include <chrono>
#include "rtt.hpp"


namespace net::rtt{
    void Rtt::rtt_minmax(){
        info.rtt_rto = info.rtt_srtt + (4.0 * info.rtt_rttvar);
        if(info.rtt_rto < RTT_DEFAULT_RXTMIN){
            info.rtt_rto = RTT_DEFAULT_RXTMIN;
        }else if (info.rtt_rto > max_rtt){
            info.rtt_rto = max_rtt;
        }
    }
    void Rtt::rtt_init(){
        auto now = ::std::chrono::system_clock::now();
        auto sec = ::std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
        info.rtt_base = sec.count();
        info.rtt_rtt    = 0;
        info.rtt_srtt   = 0;
        info.rtt_rttvar = 0.75;
        newpack();
        rtt_minmax();
    }

    uint32_t Rtt::ts(){
        last_ts = get_ts();
        return last_ts;
    }

    uint32_t Rtt::get_ts(){
        auto now = ::std::chrono::system_clock::now();
        auto millisecond = ::std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        return millisecond.count() -  info.rtt_base * 1000;
    }

    void Rtt::newpack()noexcept{
        nrexmt = 0;
    }

    Rtt::Rtt()
    {
        max_rtt = RTT_DEFAULT_RXTMAX;
        nrexmt = RTT_MAXNREXMT;
        rtt_init();
    }

    Rtt::Rtt(int max_timeout, int times) : max_rtt(max_timeout), nrexmt(times){
        rtt_init();
    }

    int Rtt::start() noexcept{
        return info.rtt_rto + 0.5;
    }

    void Rtt::stop(){
        uint32_t ms = get_ts() - last_ts;
        double delta;
        info.rtt_rtt = ms / 1000.0;
        /**
         * update out estimators of RTT, See Jacobson's SIGCOMM '88 paper', Appendix A, for details.
         */
        delta = info.rtt_rtt - info.rtt_srtt;
        info.rtt_srtt += delta / 8; // g = 1/8
        if(delta < 0.0){
            delta = -delta;
        }
        info.rtt_rttvar += (delta - info.rtt_rttvar) / 4;
        rtt_minmax(); 
    }

    bool Rtt::is_timeout()noexcept{
        if(++current_times > nrexmt){
            return true;
        }else{
            info.rtt_rto *= 2;
            return false;
        }
    }

    
    Rtt::~Rtt()
    {

    }
}