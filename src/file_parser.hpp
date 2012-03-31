#if !defined(FILE_PARSER)
#define FILE_PARSER

#include "array.hpp"
#include <iostream>
#include <fstrem>
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
      file_stream(i_filename)//should be ok, all files are supposed to be in plain text
    {
    }
    
    ~parser()
    {
      file_stream.close();
    }
    
    
    
    private :
    std::string filename;
    std::ifstream file_stream;
    
    
  public:
    template <typename PixelType>
    Array2D<PixelType>& parse_file(std::string i_filename)
    {
      filename = i_filename;
      file_stream.open(i_filename);
      
      return parse_file();
      
    }
    
    template <typename PixelType>
    Array2D<PixelType>& parse_file()
    {
      
      
      
    }
    
  };
  
  
  
  
  
  
}







#endif

