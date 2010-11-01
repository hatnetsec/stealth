#ifndef _INCLUDED_SCANNER_H_
#define _INCLUDED_SCANNER_H_

#include <string>
#include <vector>
#include <iosfwd>
#include <sys/types.h>
#include <bobcat/process>

namespace FBB
{
    class Pattern;
}

class ConfigSorter;
class Reporter;

class Scanner
{
    typedef std::vector<std::string>     StringVector;
    typedef StringVector::const_iterator const_iterator;

    ConfigSorter   &d_sorter;
    Reporter       &d_reporter;
    FBB::Pattern   &d_firstWord;
    FBB::Process    d_sshFork;
    FBB::Process    d_shFork;
    std::string     d_sentinel;
    std::string     d_label;
    const_iterator  d_cmdIterator;
    bool            d_testExitValue;
    size_t          d_nScans;
    off_t           d_maxSize;
    std::string     d_maxSizeStr;
    bool            d_quit;
    StringVector    d_skipFiles;
                                        // the abs path is at the end of 
                                        // the line. Any text may precede
                                        // it
    bool (Scanner::*d_skip)(std::string const &absPath);

    static FBB::Pattern  s_split;
    static FBB::Pattern  s_firstWord;

    public:
        Scanner(ConfigSorter &sorter, Reporter &reporter);
        size_t nScans() const
        {
            return d_nScans;
        }
        void preamble();
                                    // run one series of tests
        void        run(volatile bool *done);    


        void killChildren();
        
    private:
                        // copy a textfile
        void        copy(std::istream &src, std::string const &fname);

                        // terminate or return 'false' if the retrieved 
                        // file's size exceeds d_max_size.
        bool        checkSize(std::string const &fname, off_t length);

                                    // executes a command, and compares
                                    // its output to previously
                                    // generated output. Returns true if
                                    // the outputs are identical
        bool        doCHECKcommand(FBB::Process &child);

                                    // executes a command, without
                                    // comparing its output to previously
                                    // generated output
        void        doPlainCommand(FBB::Process &child);

                                    // execute the command from d_sorter
        void        execute(std::string const &command);    

                                    // get a remote file
        void        get(std::string const &command);

                                    // execute a local command
        void        local(std::string const &command);

                                    // start the nextCommand, including
                                    // echo $? to obtain the resultcode
        void        nextCommand(std::ostream &inserter, 
                                std::string const &command);

                                    // returns true if the contents of the
                                    // `current' logfile and `logfile'
                                    // don't differ.
        bool        noDifferences(std::string const &current,
                                  std::string const &logfile);

                                    // put a local file to the client
        void        put(std::string const &command);

                                    // construct put-dd command
        std::string putCommand(std::string const &source, 
                                std::string const &destination) const;

                                    // copy any file
        void        read(std::istream &src, std::string const &fname);

                                    // execute a remote command
        void        remote(std::string const &command);

                                    // return `true' if `word' was the 
                                    // first word. In that case, remove 
                                    // `word', and have d_firstWord match
                                    // what's beyond. 
                                    // Return false otherwise.
        bool        removeFirstWord(char const *word); 

                                    // see if there are any differences
                                    // between the output of the current
                                    // command and the output from the
                                    // previously run command
        bool        sameOutput(std::string const &logfile,
                               std::istream &extractor);

                                    // define the sentinel. Redefined
                                    // at each new run()
        void        setSentinel();

                                    // see if the exit value is 0
        void        testExitValue(std::string const &s);

                                    // wait for the sentinel and exitvalue
        void        waitForSentinel(std::istream &extractor);

                                    // write any file to the client
        void        write(std::string const &fname);

        void        removeLOG();    // remove LOG = from current command

                                    // true if filename not in d_skipFiles
        bool        skip(std::string const &line);

                                    // always indicates "don't skip"
        bool        dontSkip(std::string const &line);

                                    // fill the d_skipFiles vector and set
                                    // d_skip to &skipING
        void        setSkip(std::string const &fname);

        static std::string fileName(std::string const &name);
        static std::string datetime();
        static void replace(std::string &str, char const *org,
                                         char const *replacement);
};

inline bool Scanner::dontSkip(std::string const &line)
{
    return false;       // by returning false the question 
                        // 'skip line?' is always answered as 'no'
}

#endif
