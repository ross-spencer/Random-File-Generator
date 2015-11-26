#include <fstream>
#include <iostream>
#include <sstream>

#include <windows.h>
 


const int k = 1024;

class FileGenerator
{
   public:

      FileGenerator(int n, int size);
      ~FileGenerator();

      void Generate();
      void MetaData(std::string filename);

   private:

      int number_of_files;
      int size_of_files;

      std::fstream xml_out;
      std::stringstream xml;

};
