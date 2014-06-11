#include "options.ih"

Options::Options()
:
    d_arg(Arg::instance())
{
    // --help and --version already handled by versionHelp, but if nothing
    // is requested on the command line help is also provided.
    if (
        d_arg.nArgs() == 0 && d_arg.nOptions() == 0 && 
        d_arg.nLongOptions() == 0
    )
    {
        usage(d_arg.basename());
        throw 0;
    }

    if (imsg.setActive(d_arg.option('d')))
        imsg.reset(cerr);

    if ((d_reload = d_arg.option(0, "reload")))
        setMode(RELOAD);

    if ((d_rerun = d_arg.option(0, "rerun")))
        setMode(RERUN);

    if ((d_terminate = d_arg.option(0, "terminate")))
        setMode(TERMINATE);

    if ((d_suppress = d_arg.option(0, "suppress")))
        setMode(SUPPRESS);

    if ((d_resume = d_arg.option(0, "resume")))
        setMode(RESUME);

    if ((d_arg.option(&d_runFile, "keep-alive")) != 0)
    {
        d_repeatInterval = numeric_limits<int>::max();
        Lock::setRunFilename(d_runFile);
    }

    checkAction();

    repeatOption();
    setRandomDelay();

    d_reportToStdout = d_arg.option('o');
}       









