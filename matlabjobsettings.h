#ifndef MATLABJOBSETTINGS_H
#define MATLABJOBSETTINGS_H

#include <QString>
#include <vector>
#include "MatlabEngine.hpp"
#include "MatlabDataArray.hpp"

using namespace matlab::engine;

class matlabJobSettings
{
public:
    matlabJobSettings();
    matlabJobSettings(size_t &outA, std::vector<matlab::data::Array> &data, QString &funcType, std::tuple<QString, QString, bool> &mPathJNameParseCluster);
    size_t outA;
    std::vector<matlab::data::Array> data;
    QString funcType;
    std::tuple<QString, QString, bool> mPathJNameParseCluster;
};

#endif // MATLABJOBSETTINGS_H
