#include "stealth.ih"

void Stealth::doTasks()
{
    resetUniquePtrs();

    if (not d_options.ipc())
    {
        m1 << "timestamps use " << 
            (d_options.timestamp() == TIMESTAMPS ? 
                "local time" 
            : 
                "UTC"
            ) << endl;
    }

    if (d_options.dryrun())
        d_stealthReport << "--dry-run: SH/SSH connections not established" << 
                                                                        endl;
    else
        d_integrityScanner->startCommandShells(); 

    jobsHandler();
}








