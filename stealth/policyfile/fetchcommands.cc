#include "policyfile.ih"

// called from PolicyFile()

void PolicyFile::fetchCommands()
{
    directivesAndCommands();

    string &base = d_use["BASE"];

    if (base.back() != '/')
        base += '/';            

    bool ok = d_use.count("SSH");

    for(auto &entry: d_define)
        replaceDefines(entry.second);

    for(auto &entry: d_use)
        replaceDefines(entry.second);

    for(auto &entry: d_command)
        replaceDefines(entry);

    fixRelativeLocations();

    if (size_t parseOnly = d_options.parsePolicy())
    {
        if (parseOnly > 1)
        {
            for(auto &value: d_use)
                mp << "USE " << value.first << ": " << value.second << endl;
        }

        mp.clear();

        mp << "REPORT: " << d_use["REPORT"] << endl;

        for (size_t idx = 0; idx != d_command.size(); ++idx)
           mp << (idx + 1) << ": " << d_command[idx] << endl;

        throw 0;
    }

    if (!ok)
        fmsg << "USE SSH ... entry missing in the policy file" << noidl;
}






