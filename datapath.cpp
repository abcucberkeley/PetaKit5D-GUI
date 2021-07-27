#include "datapath.h"

dataPath::dataPath()
{
    includeMaster = true;
    maxDepth = 1;
}

dataPath::dataPath(std::string masterPath, bool includeMaster, std::string pattern, int maxDepth, std::unordered_map<std::string,std::pair<bool, std::string>> subPaths) :
    masterPath(masterPath), includeMaster(includeMaster), pattern(pattern), maxDepth(maxDepth), subPaths(subPaths)

{

}

bool dataPath::operator<(const dataPath &dPath){
    return this->masterPath < dPath.masterPath;
}
