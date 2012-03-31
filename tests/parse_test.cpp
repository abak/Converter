#include <file_parser.hpp>

#include <string>
#include <cassert>

int main (int argc, char* argv[])
{
  
  std::string filename("../../../data/test_map.txt");
  
  ail::parser parser(filename);

  ail::Array2D<ail::sint16> array = parser.parse_file<ail::sint16>();
   
   
  assert( (array.getSize() == std::make_pair<size_t, size_t>(124, 124)) );

  assert(array[24][20] == 7);
  
  return 0;
}