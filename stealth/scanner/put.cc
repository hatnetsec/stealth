#include "scanner.h2"

// Command forms:
//      PUT                   local-file remote-file 
//      PUT NOTEST            local-file remote-file 

void Scanner::put(string const &cmd)
{
    if (d_debug)
        cerr << "Scanner::put(): " << cmd << endl;

    removeFirstWord("PUT");                         // strip off `PUT'

    d_testExitValue = !removeFirstWord("NOTEST");   // [NOTEST] ...

    // at this point we have the remote-file and the local-file in the
    // command. d_firstword[1] contains the remote filename,
    //          d_firstword[3] contains the rest    


    string source = d_firstWord[1];                 // get the (remote) source
    if (!source.length())
        Util::exit(1, "PUT command requires source and destination");
            
    d_firstWord.match(d_firstWord[3]);              // strip off source

    string destination = d_firstWord[1];            // get the local dest.
    if (!destination.length())
        Util::exit(1, "At `PUT %s <destination>': destination missing", 
                                    source.c_str());
            
    if (Util::isDirectory(destination))             // is the dest. a dir. ?
        destination += "/" + Util::fileName(source);// then append sourcename


    if (d_debug)
        cerr << "Scanner::put(): scp <client>:" << source << " " << 
                                                     destination << endl;

    string command = putCommand(source, destination);

    if (Arg::getInstance().option('n'))     // no run if -n
        return;

    d_sshFork.out() << command << endl;

    write(source);                      // write the file using dd

    d_sshFork.out() <<
            "/bin/echo \"" << d_sentinel << " $?\""  << endl;
    
    waitForSentinel(d_sshFork.in());

    if (d_debug)
        cerr << "Scanner::put(): " << cmd << " DONE" << endl;

}







