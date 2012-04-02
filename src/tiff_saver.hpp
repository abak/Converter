#include <tiffio.h>
#include <string>
#include <iostream>

#include "array.hpp"



namespace ail
{

class tiff_saver
  {

  public:
    tiff_saver(void):
    tif_file(NULL)
    {
    }
    
    tiff_saver(std::string i_filename):
      filename(i_filename)
    {
      tif_file = TIFFOpen(i_filename.c_str(), "w");
      if(!tif_file)
        std::cout<<"An error occurred while opening the destination tiff file";
    }
    
    
    ~tiff_saver()
    {
      //not particularly cool, but RAII
      if(tif_file)
      {
        TIFFClose(tif_file);
        tif_file = NULL;
      }
    }
    
    template <typename PixelType>
    bool save_array(Array2D<PixelType>& array)
    {
      if(!tif_file)
      {
        std::cout<<"Invalid file was specified, something went horribly wrong";
        return false;
      }
      
      //first, we write the metadata
      
      TIFFSetField(tif_file, TIFFTAG_IMAGEWIDTH, array.getWidth());
      TIFFSetField(tif_file, TIFFTAG_IMAGELENGTH, array.getHeight());
      TIFFSetField(tif_file, TIFFTAG_SAMPLESPERPIXEL, 1);//since all maps are supposed to be 1 channel
      TIFFSetField(tif_file, TIFFTAG_BITSPERSAMPLE, 8*sizeof(PixelType));
      TIFFSetField(tif_file, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
      TIFFSetField(tif_file, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);//we actually don't give a flying shit, since we have only 1 plane.
      TIFFSetField(tif_file, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
      
      //now we write the actual data
      tsize_t bytes_per_line = array.getRowByteSize();
      unsigned char *buf = NULL; //tiff buffer per se
      
      //i think i'm copy-pasting some stupid code, but i can't prove, it
      //and i don't feel like reading the whole libtiff doc (or lack thereof)
      tsize_t tiff_file_scanline_size = TIFFScanlineSize(tif_file);//ndebug purpose
      
      if (tiff_file_scanline_size < bytes_per_line)
        buf = static_cast<unsigned char *>(_TIFFmalloc(bytes_per_line));
      else
        buf = static_cast<unsigned char *>(_TIFFmalloc(tiff_file_scanline_size));
      
      if(!buf)
      {
        std::cout<<"An error occurred while allocating internal buffer : Abort, abort";
        return false;
      }
      
      /*//Now writing image to the file one strip at a time
       for (uint32 row = 0; row < h; row++)
       {
       memcpy(buf, &image[(h-row-1)*linebytes], linebytes);    // check the index here, and figure out why not using h*linebytes
       if (TIFFWriteScanline(out, buf, row, 0) < 0)
       break;
       }*/
      
      for(size_t y = 0 ; y < array.getHeight() ; ++y)
      {
        memcpy( buf, array[y], bytes_per_line);
        int error_code = TIFFWriteScanline(tif_file, buf, y, 0);
        if(error_code<0)
        {
          std::cout<<"An error occured while writing line number "<<y;
          std::cout<<"Tiff Error code : "<<error_code;
        }
        
      }
      
      _TIFFfree(buf);
      
      return true;
    }
    
    
  private :
    std::string filename;
    TIFF* tif_file;
    
    
  };
}//namspace