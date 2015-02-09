#include "stealth.ih"

void Stealth::policyDepDataMembers()
{
    d_policyFile = d_options.policyFile();

    d_policyFile->chdirBase();        

    openStealthReport();

    d_integrityScanner = make_shared<IntegrityScanner>(
                                d_task, *d_policyFile, 
                                d_fatal, d_stealthReport
                            );
}


