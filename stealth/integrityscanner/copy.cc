#include "integrityscanner.ih"

//  SEE ALSO THE MEMBER waitForSentinel()

void IntegrityScanner::copy(Process &src, string const &fname)
{
    ofstream currentReport(fname.c_str());

    if (!currentReport)
        fmsg << "Can't open `" << fname << "' to write" << noidl;

    m3 << "copy: about to read child input" << endl;

    string line;
    off_t length = 0;

        // `line' is the line as produced by the executed command
    while (getline(src, line))
    {
        checkSize(fname, length += line.length() + 1);  // throws if not OK

        m3 << "copy SAW: `" << line << '\'' << endl;

        if (line.find(d_sentinel) == 0)
        {
            m3 << "GOT Sentinel" << endl;
            break;
        }

        string path = getPath(line);    // extract the path from the line

        if (not (this->*d_skip)(path))      // write `line' to the report, 
            currentReport << line << '\n';  // unless it can be skipped
    }

    testExitValue(src.str(), line);
}





