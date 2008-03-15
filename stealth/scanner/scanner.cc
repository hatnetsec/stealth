#include "scanner.ih"

/*
    Since the Scanner's destruction is also the termination of the program, no
explicit destruction of the newly created objects is necessary. A pointer is
used to prevent the construction of a constant object. As the constructor
itself would create a constant object, the construction *new... 
is used.

*/

Scanner::Scanner(ConfigSorter &sorter, Reporter &reporter)
:
    d_sorter(sorter),
    d_reporter(reporter),                       // ostream
    d_firstWord(*new Pattern("(\\S+)(\\s+(.*))?")),// firstword ([1]) and 
                                                // the rest ([3]) of a text
    d_sshFork
    (
        d_sorter["SSH"], 
        Process::CIN | Process::COUT | Process::IGNORE_CERR
    ),                 // child: ignores stderr, reads
    d_shFork
    (
        d_sorter["SH"],
        Process::CIN | Process::COUT | Process::IGNORE_CERR
    ),                   // from stdin/stdout
                                                // parent process communicates
                                                // via the Fork object's 
                                                // stream interface.
    d_nScans(0),
    d_maxSize(10 * 1024 * 1024),
    d_maxSizeStr("10M"),
    d_quit(false)
{
    setSentinel();

    if (Arg::instance().option(&d_maxSizeStr, "max-size"))
    {
        d_maxSize = A2x(d_maxSizeStr);
        switch(d_maxSizeStr.find_first_not_of("0123456789"))
        {
            case 'G':
            case 'g':
                d_maxSize *= 1024;
            // FALLING THRU

            case 'M':
            case 'm':
                d_maxSize *= 1024;
            // FALLING THRU

            case 'K':
            case 'k':
                d_maxSize *= 1024;
            // FALLING THRU

            case string::npos:                  // size as-is
            case 'b':
            case 'B':
                reporter << "    MaxSize = " << d_maxSizeStr << endl;
                break;

            default:
                d_reporter.exit() << 
                    "Error in --max-size option specification: " << 
                     d_maxSizeStr << endl;
        }
    }
}



