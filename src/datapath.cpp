#include "datapath.h"

// Default constructor includes the masterPath and sets a max depth of one
dataPath::dataPath()
{
    includeMaster = true;
    maxDepth = 1;
}

// Constructor to allow custom input
dataPath::dataPath(QString masterPath, bool includeMaster, QString pattern, int maxDepth, std::unordered_map<QString,std::pair<bool, QString>> subPaths) :
    masterPath(masterPath), includeMaster(includeMaster), pattern(pattern), maxDepth(maxDepth), subPaths(subPaths)
{

}

// Sorting for this class is done through the masterPath member
bool dataPath::operator<(const dataPath &dPath){
    return this->masterPath < dPath.masterPath;
}

// Needed this one for Clang
// Sorting for this class is done through the masterPath member
bool dataPath::operator<(const dataPath &dPath) const{
    return this->masterPath < dPath.masterPath;
}
