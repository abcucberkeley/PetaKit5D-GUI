#include "matlabjobsettings.h"

matlabJobSettings::matlabJobSettings()
{

}

matlabJobSettings::matlabJobSettings(size_t &outA, std::vector<matlab::data::Array> &data, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster)
    : outA(outA), data(data), funcType(funcType), mPathJNameParseCluster(mPathJNameParseCluster)
{

}
