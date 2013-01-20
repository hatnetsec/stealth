#include "scanner.ih"

//  SEE ALSO THE MEMBER waitForSentinel()

void Scanner::copy(Process &src, string const &fname)
{
    ofstream currentReport(fname.c_str());

    if (!currentReport)
        d_reporter.error() << "Can't open `" << fname << "' to write" << endl;

    imsg << "Scanner::copy(): about to read child input" << endl;

    string line;
    off_t length = 0;

        // `line' is the line as produced by the executed command
    while (getline(src, line))
    {
        if (!checkSize(fname, length += line.length() + 1))
            return;

        imsg << "copy SAW: `" << line << '\'' << endl;

        if (line.find(d_sentinel) == 0)
        {
            imsg << "GOT Sentinel" << endl;
            break;
        }

        string path = getPath(line);    // extract the path from the line

        if (not (this->*d_skip)(path))      // write `line' to the report, 
            currentReport << line << '\n';  // unless it can be skipped
    }

    testExitValue(src.str(), line);
}





