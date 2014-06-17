#ifndef INCLUDED_OPTIONS_
#define INCLUDED_OPTIONS_

#include <memory>

#include <bobcat/argconfig>
#include <bobcat/linearmap>
#include <bobcat/log>
#include <bobcat/multistreambuf>
#include <bobcat/syslogstream>

#include "../stealthenums/stealthenums.h"

class Options: public StealthEnums
{
    FBB::ArgConfig &d_arg;

    std::unique_ptr<FBB::SyslogStream> d_syslog;
    FBB::Log d_log;

    FBB::MultiStreambuf d_multiStreambuf;
    std::ostream d_msg;                     // d_msg handles all messages to
                                            // syslog and/or d_log

    Mode d_mode = INTEGRITY_SCAN;

    std::string d_policyFilePath;
    std::string d_skipFilePath;
    std::string d_runFile;
    std::string d_maxSizeStr;

    bool d_reload;
    bool d_rerun;
    bool d_resume;
    bool d_suspend;
    bool d_terminate;
    bool d_daemon;
    bool d_randomDelay;
    bool d_sendMail = true;
    bool d_logMail = false;
    bool d_stdout = false;
    bool d_repeat;
    size_t d_repeatInterval;
    size_t d_delayInterval = 0;
    size_t d_commandNr = 0;
    std::streamsize d_maxDownloadSize = 10 * 1024 * 1024;   // 10 MB

    FBB::LinearMap<std::string, FBB::Facility>::const_iterator 
                                                        d_syslogFacility;
    FBB::LinearMap<std::string, FBB::Priority>::const_iterator 
                                                        d_syslogPriority;


    static Options *s_options;

    static FBB::Facility    s_defaultSyslogFacility;
    static FBB::Priority    s_defaultSyslogPriority;
    static char const       s_defaultConfigFile[];
    static char const       s_defaultSyslogIdent[];

    static size_t   s_defaultVerbosity;
    static size_t   s_shortestRepeatInterval;

    static FBB::LinearMap<std::string, FBB::Facility> const 
                                                        s_syslogFacilities;
    static FBB::LinearMap<std::string, FBB::Priority> const 
                                                        s_syslogPriorities;

    static FBB::LinearMap<Mode, char const *> const     s_ipc;

    public:
        static Options &instance();

        Options(Options const &other) = delete;

        void oldOptions() const;

        bool parseConfigFile() const;
        bool verboseOrJustParse() const;
        bool verbose() const;
        bool ipc() const;
        bool reload() const;        
        bool rerun() const;
        bool terminate() const;
        bool suspend() const;
        bool resume() const;
        bool daemon() const;
        bool repeat() const;
        bool sendMail() const;
        bool logMail() const;
        bool stdout() const;

        Mode mode() const;

        size_t repeatInterval() const;
        size_t randomAddition() const;
        size_t commandNr() const;
        std::streamsize maxDownloadSize() const;

        std::string const &maxSizeStr() const;
        std::string const &policyFilePath() const;
        std::string const &skipFilePath() const;
        std::string const &basename() const;
        std::string const &runFile() const;

        static void usage(std::string const &progname);

    private:
        Options();

        void setCommandNr();
        void setRepeat();
        void setRandomDelay();
        void setMail();
        void setSkipFilePath();
        void setDownloadSize();

        bool setSyslog();

        std::string syslogTag() const;
        FBB::Priority syslogPriority() const;
        FBB::Facility syslogFacility() const;


        void checkAction() const;

        void loadConfigFile();

        void warnOption(char const *label) const;
};

inline Options::Mode Options::mode() const
{
    return d_mode;
}

inline bool Options::sendMail() const
{
    return d_sendMail;
}

inline bool Options::logMail() const
{
    return d_logMail;
}

inline bool Options::reload() const
{   
    return d_reload;
}

inline bool Options::verbose() const
{   
    return d_arg.option('V');
}

inline bool Options::parseConfigFile() const
{   
    return d_arg.option('c');
}

inline bool Options::verboseOrJustParse() const
{   
    return d_arg.option("cd");
}

inline bool Options::rerun() const
{   
    return d_rerun;
}

inline bool Options::repeat() const
{   
    return d_repeat;
}

inline bool Options::terminate() const
{   
    return d_terminate;
}

inline bool Options::suspend() const
{   
    return d_suspend;
}

inline bool Options::resume() const
{   
    return d_resume;
}

inline bool Options::daemon() const
{   
    return d_daemon;
}

inline bool Options::ipc() const
{   
    return d_reload || d_rerun || d_terminate || d_suspend || d_resume;
}

inline bool Options::stdout() const
{   
    return d_stdout;
}

inline std::string const &Options::policyFilePath() const
{   
    return d_policyFilePath;
}

inline std::string const &Options::skipFilePath() const
{   
    return d_skipFilePath;
}

inline std::string const &Options::runFile() const
{   
    return d_runFile;
}

inline std::string const &Options::basename() const
{   
    return d_arg.basename();
}

inline size_t Options::repeatInterval() const
{
    return d_repeatInterval;
}

inline size_t Options::commandNr() const
{
    return d_commandNr;
}

inline std::streamsize Options::maxDownloadSize() const
{
    return d_maxDownloadSize;
}

inline std::string const &Options::maxSizeStr() const
{
    return d_maxSizeStr;
}

#endif





