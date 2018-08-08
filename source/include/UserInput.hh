#ifndef UserInput_h
#define UserInput_h 1

#include "globals.hh"
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <typeinfo>
#include <cstring>

class DataCollection;

class UserInput {

std::map<std::string, std::string> cfgParams;
std::string cfgFileName = "configuration.txt";
public:
  UserInput();
  ~UserInput();
  
  double GetDetThickness(){return detThickness;}
  double GetParticleEnergy(){return particleEnergy;}
  std::string GetTreeFileName(){return treeFile;}
  std::string GetParticleType(){return particleType;}

  
public:
  double detThickness;
  double particleEnergy;
  std::string particleType;
  std::string treeFile;
};

#endif
