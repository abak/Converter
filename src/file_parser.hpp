#if !defined(FILE_PARSER)
#define FILE_PARSER

#include "array.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>


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
      std::vector<PixelType> result;
      std::string remaining;
      
      size_t pos = line.find("\t");
      std::string value = line.substr(0, pos);
      remaining = line.substr(pos + 1, line.length());//+1 to pop the \t
      result.push_back(atof(value.c_str()));
      
      
      while(0 != remaining.length())
      {
        pos = remaining.find("\t");
        if(pos == remaining.npos)
        {
          pos = remaining.find("\r"); 
        }
        value = remaining.substr(0, pos);
        remaining = remaining.substr(pos + 1, remaining.length());
        result.push_back(atof(value.c_str()));
      }
      
      return result;
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
      std::vector<PixelType> extracted_data;
      extracted_data = parse_line<PixelType>(input_data[0]);
      
      result.Resize(extracted_data.size(), input_data.size() - 1);
      for(size_t idx = 0 ; idx <<extracted_data.size() ; ++idx)
        result[0][idx] = extracted_data[idx];
      
      //handle the rest of the file
      for(size_t line_idx = 1 ; line_idx < input_data.size() - 1 ; ++line_idx)
      {
        extracted_data = parse_line<PixelType>(input_data[line_idx]);
        assert(extracted_data.size() == result.getWidth());
        for(size_t idx = 0 ; idx < extracted_data.size() ; ++idx)
          result[line_idx][idx] = extracted_data[idx];
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

