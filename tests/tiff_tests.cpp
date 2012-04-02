#include <tiff_saver.hpp>
#include <file_parser.hpp>


int main(int argc, char * argv[])
{

  ail::tiff_saver saver("../../../data/test_out.tif");
  ail::parser parser("../../../data/test_map.txt");
  
  ail::Array2D<ail::sint16> array = parser.parse_file<ail::sint16>();

  
  saver.save_array(array);

  
  
  return 0;
}