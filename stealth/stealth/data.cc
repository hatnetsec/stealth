#include "stealth.ih"

FBB::LinearMap<Stealth::Mode, Stealth::Task> Stealth::s_task =
    {
        {RELOAD,            &Stealth::reload},          // autoscan
        {TERMINATE,         &Stealth::terminate},       // terminates
        {INTEGRITY_SCAN,    &Stealth::integrityScan},
        {SUSPEND,           &Stealth::suspend},
        {RESUME,            &Stealth::resume},          // autoscan
        {RERUN,             &Stealth::rerun},           // autoscan
    };

    // possible incoming requests at the ipcInterface
FBB::LinearMap<Stealth::Mode, Stealth::Action> Stealth::s_request =
    {
        {INTEGRITY_SCAN,    &Stealth::unknownRequest},

        {PING,              &Stealth::pingRequest},
        {RERUN,             &Stealth::rerunRequest},
        {SUSPEND,           &Stealth::suspendRequest},
        {RESUME,            &Stealth::resumeRequest},
        {RELOAD,            &Stealth::reloadRequest},
        {TERMINATE,         &Stealth::terminateRequest},

        {UNKNOWN,           &Stealth::unknownRequest},
    };



