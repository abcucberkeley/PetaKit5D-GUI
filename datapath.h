#ifndef DATAPATH_H
#define DATAPATH_H
#include <unordered_map>

// Class used to store a data path. A data path consists of:
// A masterPath
// A boolean that holds whether or not to include the masterPath
// in the paths submitted for a job
// A pattern that will be used to identify specific subPaths
// A maxDepth which is how deep into the masterPath will be searched
// for subDirs
// An unordered map that contains a list of subPaths and whether or not they
// are currently going to be submitted for a job.
class dataPath
{
public:
    dataPath();
    dataPath(std::string masterPath, bool includeMaster, std::string pattern, int maxDepth, std::unordered_map<std::string,std::pair<bool, std::string>> subPaths);
    bool operator<(const dataPath &dPath);

    std::string masterPath;
    bool includeMaster;
    std::string pattern;
    int maxDepth;
    std::unordered_map<std::string,std::pair<bool, std::string>> subPaths;

/*private:
    size_t numPaths;*/
};

#endif // DATAPATH_H
