#include "scanner.h2"

void Scanner::run()
{
    d_cmdIterator = d_sorter.firstCmd();        // d_cmdIterator is set to
                                                // the first command. It's a
                                                // true iterator, so we can 
                                                // add values to it, below.
    string cmdNr;

    if (Arg::getInstance().option(&cmdNr, 'r')) // is there  a command number?
    {
                                                // if so, add its number to
                                                // d_cmdIterator    
        d_cmdIterator += atoi(cmdNr.c_str()) - 1;
        execute(*d_cmdIterator);                // and execute that command
    }
    else                                        // no number: process all
    {                                           // commands    
        for
        (
            vector<string>::const_iterator beyond = d_sorter.beyondCmd();
                d_cmdIterator != beyond;
                    d_cmdIterator++
        )
            execute(*d_cmdIterator);
    }

    if (d_debug)
        cerr << "Stealth: policy file processed\n";
}


