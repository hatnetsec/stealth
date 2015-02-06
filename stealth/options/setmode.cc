#include "options.ih"

void Options::setMode()
{
    if ((d_reload = d_arg.option(0, "reload")))
        d_mode = RELOAD;

    if ((d_rerun = d_arg.option(0, "rerun")))
        d_mode = RERUN;

    if ((d_terminate = d_arg.option(0, "terminate")))
        d_mode = TERMINATE;

    if ((d_suspend = d_arg.option(0, "suspend")))
        d_mode = SUSPEND;

    if ((d_resume = d_arg.option(0, "resume")))
        d_mode = RESUME;

    if (
        (d_daemon = d_arg.option(&d_unixDomainSocket, 'd'))
        &&
        (d_arg.nArgs() == 0)
    )
        fmsg << "--daemon: missing run-file or policy file" << endl;

    d_ipc = d_reload || d_rerun || d_terminate || d_suspend || d_resume;

    if (d_ipc)
        d_unixDomainSocket = d_arg[0];

    d_foreground = not d_ipc and not d_daemon;
}
