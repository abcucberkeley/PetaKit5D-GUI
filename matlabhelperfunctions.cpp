#include "matlabhelperfunctions.h"
#include <QCoreApplication>
#include <QDir>
#include <QDirIterator>
#include <QLabel>
#include <QCheckBox>
#include <iostream>
#include <fstream>

void addArrayToArgs(std::string &args, const std::vector<std::string> &cellArray, const bool isCharArray, const std::string &prependedString, const std::string &arrayChars, const bool isMcc){
    if(arrayChars.size() != 2){
        std::cout << "Error: addArrayToArgs arrayChars input must be the 2 chars that open and close the array type" << std::endl;
        return;
    }
    std::string surroundQuotes;
    if(isMcc) surroundQuotes = "\"";
    args.append(prependedString+surroundQuotes+arrayChars[0]);
    for(size_t i = 0; i < cellArray.size(); i++){
        if(i > 0) args.append(",");
        if(isCharArray) args.append("\'");
        args.append(cellArray[i]);
        if(isCharArray) args.append("\'");
    }
    args.push_back(arrayChars[1]);
    args.append(surroundQuotes);
}

void addCharArrayToArgs(std::string &args, const std::string &charArray, const std::string &prependedString, const bool isMcc, const bool addEscapeChar){
    std::string escapeChar;
    if(!isMcc) args.append(prependedString+escapeChar+"\'"+charArray+escapeChar+"\'");
    else{
        std::string surroundQuotes = "\"";
        args.append(prependedString+surroundQuotes+charArray+surroundQuotes);
    }
}

void addScalarToArgs(std::string &args, const std::string &scalar, const std::string &prependedString){
    args.append(prependedString+scalar);
}

void addBoolToArgs(std::string &args, const bool mBool, const std::string &prependedString){
    if(mBool) args.append(prependedString+"true");
    else args.append(prependedString+"false");
}

// returns 1 if no paths are added
// returns 0 otherwise
int addDataPathsToArgs(std::string &args, const std::string &prependedString, std::vector<dataPath> dataPaths, const bool isMcc){
    // Data Paths
    std::string surroundQuotes;
    if(isMcc) surroundQuotes = "\"";
    args.append(prependedString+surroundQuotes+"{");
    bool firstCell = true;
    std::vector<std::string> cellArray;
    for(const auto &path :  dataPaths){
        if(path.includeMaster){
            QDirIterator it(path.masterPath,QDir::Files);
            if(it.hasNext()){
                if(firstCell){
                    addCharArrayToArgs(args, path.masterPath.toStdString(), "", false, true);
                    firstCell = false;
                }
                else addCharArrayToArgs(args, path.masterPath.toStdString(), ",", false, true);
            }
            else std::cout << "WARNING: Data Path: " << path.masterPath.toStdString() << " not included because it contains no files. Continuing." << std::endl;
        }
        for(const auto &subPath : path.subPaths){
            if(subPath.second.first){
                QDirIterator it(subPath.second.second,QDir::Files);
                if(it.hasNext()){
                    if(firstCell){
                        addCharArrayToArgs(args, subPath.second.second.toStdString(), "", false, true);
                        firstCell = false;
                    }
                    else addCharArrayToArgs(args, subPath.second.second.toStdString(), ",", false, true);
                }
                else std::cout << "WARNING: Data Path: " << subPath.second.second.toStdString() << " not included because it contains no files. Continuing." << std::endl;
            }
        }
    }
    args.append("}"+surroundQuotes);
    return endsWith(args,surroundQuotes+"{}"+surroundQuotes);
}

void addChannelPatternsToArgs(std::string &args, std::vector<std::pair<QLabel*,QCheckBox*>> channelWidgets, bool customPatterns, QString patternLine, const std::string &prependedString, const bool isMcc, const std::string &arrayChars){
    if(arrayChars.size() != 2){
        std::cout << "Error: addChannelPatternsToArgs arrayChars input must be the 2 chars that open and close the array type" << std::endl;
        return;
    }
    // Channel Patterns
    std::string surroundQuotes;
    if(isMcc) surroundQuotes = "\"";
    args.append(prependedString+surroundQuotes+arrayChars[0]);
    bool firstCell = true;
    if(!customPatterns){
        if(channelWidgets.size()){
            // Grab indexes of checked boxes
            std::vector<int> indexes;
            for(size_t i = 0; i <  channelWidgets.size(); i++){
                if(channelWidgets[i].second->isChecked()) indexes.push_back(i);
            }
            // Go through checked indexes and the label text (channel pattern) in the cell array
            for(int i : indexes){
                // Convert from rich text to plain text
                QTextDocument toPlain;
                toPlain.setHtml(channelWidgets[i].first->text());
                if(firstCell){
                    addCharArrayToArgs(args, toPlain.toPlainText().toStdString(), "", false, true);
                    firstCell = false;
                }
                else addCharArrayToArgs(args, toPlain.toPlainText().toStdString(), ",", false, true);
            }
        }
    }
    // Use custom patterns
    else{
        QString pattern;
        for(int i = 0; i < patternLine.size(); i++){
            if(patternLine[i] == ','){
                if(firstCell){
                    addCharArrayToArgs(args, pattern.toStdString(), "", false, true);
                    firstCell = false;
                }
                else addCharArrayToArgs(args, pattern.toStdString(), ",", false, true);
                pattern.clear();
            }
            else{
                pattern.push_back(patternLine[i]);
            }
        }
        if(pattern.size()) {
            if(firstCell){
                addCharArrayToArgs(args, pattern.toStdString(), "", false, true);
            }
            else addCharArrayToArgs(args, pattern.toStdString(), ",", false, true);
        }
    }
    args.append(arrayChars[1]+surroundQuotes);
}

// convert bool to a string for matlab
std::string btosM(const bool val){
    if(val) return "true";
    else return "false";
}

bool endsWith(std::string_view str, std::string_view suffix)
{
    return str.size() >= suffix.size() && 0 == str.compare(str.size()-suffix.size(), suffix.size(), suffix);
}
