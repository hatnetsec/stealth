#include "integrityscanner.ih"

                                        // receives the next command to execute
void IntegrityScanner::execute(string const &cmd)
{
    if (!(s_firstWord << cmd))          // determine first word and the rest
        fmsg << "Corrupt line in policy file: " << cmd << noidl; 
    else
        m1 << cmd << endl;
    
    if (s_firstWord[1] == "LABEL")      // set a label 
    {
        d_label = s_firstWord[3];       // the text beyond the LABEL keyword
        replace(d_label,          // change \\n into newlines
                        "\\n", "\n");   
    }
    else if (s_firstWord[1] == "LOCAL") // run a local command
        local(s_firstWord[3]);
    else if (s_firstWord[1] == "GET")   // get a file from the client
        get(cmd);
    else if (s_firstWord[1] == "PUT")   // put a file to the client
        put(cmd);
    else                                // or run a remote command
        remote(cmd);
}



