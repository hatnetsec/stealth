#ifndef INCLUDED_IPC_
#define INCLUDED_IPC_

#include <string>

//#include <bobcat/selector>


#include <bobcat/linearmap>

#include "../stealthenums/stealthenums.h"
#include "../wait11/wait11.h"

class Options;

class IPC: public StealthEnums
{
    Options        &d_options;

    Wait11          d_wait11;

    std::string     d_requestText;
    size_t          d_requestorPid = 0;
    size_t          d_daemonPid;

    static FBB::LinearMap<std::string, Mode> const s_request;

    public:
        IPC();
                                            // always returns true, or
        bool signalDaemon();                // throws exception on failure

        StealthEnums::Mode request();       // retrieve the request/msg and 
                                            // requestor's pid
        std::string const &requestText() const;

        void sendRequestor(std::string const &msg);

        void signaled();                    // call after receiving a signal

        void wait(bool doM2 = true);        // wait until signaled
        
        void timedWait();                   // wait until signaled or wait
                                            // until --repeat time has passed

        void timedWait(size_t seconds);     // wait until signaled or wait
                                            // until seconds has passed
                                            // (no m2 messages), called from
                                            // the ipc-modes

        bool timeout() const;               // true if timedWait's waiting
                                            // time has expired

        void writeRunFile(pid_t pid);

        void write(std::string const &msg) const;   // write msg and own pid
                                                    // to the runfile
        size_t daemonPid() const;

    private:
        void readDaemonPid();
        void sendRequest(char const *request, pid_t pid);
};

inline void IPC::timedWait(size_t seconds)
{
    d_wait11.waitFor(seconds, false);
}

inline void IPC::signaled()
{
    d_wait11.notify();
}

inline bool IPC::timeout() const
{
    return not d_wait11.signaled();
}

inline std::string const &IPC::requestText() const
{
    return d_requestText;
}

inline size_t IPC::daemonPid() const
{
    return d_daemonPid;
}

#endif

