#include "options.ih"

void Options::setStdout()
{
    if (d_arg.option('o') or d_ipc)
    {
        if (d_daemon)
            wmsg << "--stdout ignored: conflicts with --daemon" << endl;
        else
        {
            d_stdout = true;
            d_multiStreambuf.insert(cout);
        }
    }
}
