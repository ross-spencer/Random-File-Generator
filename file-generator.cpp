#include "FileGenerator.h"

FileGenerator::FileGenerator(int n, int size)
{
   number_of_files = n;
   size_of_files = size;

/*
   xml << "<?xml version=\"1.0\" encoding=\"ISO-8859-1\" ?>";
   xml << "<files>";
   xml_out.open("files\\list.xml", std::ios_base::out);
*/

   xml_out.open("files\\list.csv", std::ios_base::out);

}

FileGenerator::~FileGenerator()
{
/*
   xml << "</files>";
*/

   if(xml_out.is_open())
   {
      xml_out << xml.str();
      xml_out.close();
   }
   else
   {
      std::cout << "unable to close xml..." << std::endl;
   }
}

void FileGenerator::Generate()
{
   int random_char = 0;
   
   std::stringstream filename;
   std::stringstream content;

   filename.flags(std::ios::internal | std::ios::hex);
   filename.fill(0x30);

   // initialize random seed...
   srand(time(NULL));

   LPSECURITY_ATTRIBUTES attr;
   attr = NULL;
   CreateDirectory ("hello", attr);

   for(int i = 1; i <= number_of_files; i++)
   {
      filename << "files\\";
      filename << size_of_files;
      filename.width (10);
      filename << i << ".txt";

      for(int x = 0; x < k*k; x++)
      {
         //random char, within range of printible characters...
         random_char = rand() % 93 + 33;
         content << static_cast<char>(random_char);
      }

      std::fstream new_file(filename.str().c_str(), std::ios_base::out | std::ios_base::binary);

      MetaData(filename.str());

      if(new_file.is_open())
      {
         for(int j = 0; j < size_of_files; j++)
         {
            new_file << content.str() << std::endl;
         }
      }
      else
      {
         std::cout << "An error has occurred... (does the \\files\\ directory exist?)" << std::endl;
      }
   
      new_file.close();

      //don't need to clear, same amount of data going back in...
      content.seekp(std::ios_base::beg);
      filename.seekp(std::ios_base::beg);
   }
}

void FileGenerator::MetaData(std::string filename)
{
   static int count = 0;

   size_t pos;
   pos = filename.find("\\");   
   std::string filename_trimmed = filename.substr(pos+1);   

/*
   xml << "<file>";
   xml << "<name>" << filename_trimmed << "</name>";
   xml << "<size>" << size_of_files << "</size>";
   xml << "</file>";
*/

   if(count > 0)
   {
      xml << ",";
   }

   xml << filename_trimmed << ",";
   
   time_t rawtime;
   tm * ptm;
   time ( &rawtime );
   ptm = gmtime ( &rawtime );

   xml << ptm->tm_mday << "/" << (ptm->tm_mon)+1 << "/" << (ptm->tm_year)+1900;

   if(xml_out.is_open())
   {
      xml_out << xml.str();
      xml.str(std::string());
   }
   else
   {
      std::cout << "error writing xml output." << std::endl;
   }

   count++;
}
