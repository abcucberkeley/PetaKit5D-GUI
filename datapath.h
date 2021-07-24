#ifndef DATAPATH_H
#define DATAPATH_H
#include <unordered_map>

class dataPath
{
public:
    dataPath();
    std::string masterPath;
    bool includeMaster;
    std::string pattern;
    int maxDepth;
    std::unordered_map<std::string,std::pair<bool, std::string>> subPaths;
};

#endif // DATAPATH_H
