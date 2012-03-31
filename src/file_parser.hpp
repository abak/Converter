#if !defined(FILE_PARSER)
#define FILE_PARSER

#include "array.hpp"
#include <iostream>
#include <fstream>
#include <string>


namespace ail
{
  
 class parser
  {
    
  public:
    parser()
    {}
    
    parser(std::string i_filename):
      filename(i_filename),
      file_stream(i_filename.c_str())//should be ok, all files are supposed to be in plain text
    {
    }
    
    ~parser()
    {
      if(file_stream.is_open())
        file_stream.close();
    }
    
    
    
  
  private:
    
    std::string filename;
    std::ifstream file_stream;
    
    template <typename PixelType>
    std::vector<PixelType> parse_line(std::string& line)
    {
      
      
    }
    
    
  
  public:
    
    template <typename PixelType>
    Array2D<PixelType> parse_file()
    {
      Array2D<PixelType> result;
      
      if(!file_stream.is_open())
        std::cout<<"\nCan't open file : "<<filename<<"\n";
      
      std::vector<std::string> input_data;
      
      while(!file_stream.eof())
      {
        std::string current_line;
        getline(file_stream, current_line);
       // std::cout<<current_line;
        input_data.push_back(current_line);
      }
      
      //handle first line + allocate output array
      
      
      //handle the rest of the file
      for(size_t idx = 1 ; idx < input_data.size() ; ++idx)
      {
        
      }
      
      
      file_stream.close();
      
      return result;
    }
    
    
    
    
    
    template <typename PixelType>
    Array2D<PixelType> parse_file(std::string i_filename)
    {
      filename = i_filename;
      file_stream.open(i_filename.c_str());
      
      return parse_file<PixelType>();
      
    }
    
   
    
  };
  
  
}







#endif

