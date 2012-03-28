#include <array.hpp>
#include <assert.h>

#include <iostream>

int main(int argc, char * argv[])
{
  int n_failed_tests = 0;
  
  
  typedef signed short pixel_16s_t;
  typedef unsigned char pixel_8u_t;
  
  //instanciation
  ail::Array2D<pixel_16s_t> tab_16s;
  
  tab_16s.Resize(10,20);
  
  assert(tab_16s.getWidth() == 10);
  assert(tab_16s.getHeight() == 20);
  assert(tab_16s.getSize() == std::make_pair(static_cast<size_t> (10), static_cast<size_t>(20)));





}