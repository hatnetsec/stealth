#include "integrityscanner.ih"

void IntegrityScanner::run()
{
    ++d_nScans;

    setSentinel();                              // determine d_sentinel

    d_cmdIterator = d_policyFile.firstCmd();        // d_cmdIterator is set to
                                                // the first command. It's a
                                                // true iterator, so we can 
                                                // add values to it, below.

    if (size_t cmdNr = d_options.commandNr())   // is there  a command number?
    {
        d_cmdIterator += cmdNr - 1;             // if so, set the cmdIterator
        execute(*d_cmdIterator);                // and execute that command
    }
    else                                        // no number: process all
    {                                           // commands    
        auto beyond = d_policyFile.beyondCmd();

        for (auto &cmd: ranger(d_cmdIterator, beyond))
        {
            if (d_run.interrupted())    // terminate, suspend, reload
            {
                m1 << "Running integrity scan interrupted by " << 
                            d_run.modeName() << " request" << endl;
                return;
            }

            execute(cmd);
        }
    }

    m3 << "policy file processed" << endl;
}





