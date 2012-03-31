#if !defined(ARRAY2D_HPP)
#define ARRAY2D_HPP

#include <vector>


namespace ail
{
  typedef signed short int sint16;
  typedef signed short int int16;
  typedef unsigned char uint8;
  

  template<typename T>
  class Array2D
  {
    std::vector<T>  data;
    std::vector<T*> ptr;
    size_t width;
    size_t height;
    
    void Link(void)
    {
      for (unsigned int j = 0; j < height; ++j)
        ptr[j] = &data[j * width];
    }
    
    
  public:
    Array2D(void)
    {
    };
    
    Array2D(const size_t i_width, const size_t i_height) :
    width(i_width),
    height(i_height),
    data(i_width * i_height),
    ptr(i_height)
    {
      Link();
    }
    
    
    size_t getWidth(void)
    {
      return width;
    }
    
    size_t getHeight(void)
    {
      return height;
    }
    
    std::pair<size_t, size_t> getSize(void)
    {
      return std::make_pair(width, height);
    }
    
    void Resize(const size_t niou_width, const size_t niou_height)
    {
      if (width == niou_width && height == niou_height)
        return;
      
      width  = niou_width;
      height = niou_height;
      
      data.resize(niou_height * niou_width);
      ptr.resize(niou_height);
      Link();
    }
    
    
    typename std::vector<T>::iterator begin(void)
    {
      return data.begin();
    }
    
    
    typename std::vector<T>::iterator end(void)
    {
      return data.end();
    }
    
    
    void assign(T value)
    {
      data.assign(width * height, value);
    }
    
    
    Array2D(const Array2D& a) :
    width(a.width),
    height(a.height)
    {
      data = a.data;
      ptr.resize(height);
      Link();
    }
    
    
    Array2D& operator=(const Array2D a)
    {
      swap(*this, a);
      return *this;
    }
    
    template <typename U>
    friend void swap(Array2D<U>& first, Array2D<U>& second)
    {
      using std::swap;
      swap(first.height, second.height);
      swap(first.width, second.width);
      swap(first.data, second.data);
      swap(first.ptr, second.ptr);
    }
    
    ~Array2D()
    {
    };
    
    T* operator[](const size_t ligne)
    {
      return ptr[ligne];
    };
    const T* operator[](const size_t ligne) const
    {
      return ptr[ligne];
    };
    
    T& operator()(const size_t col, const size_t lig)
    {
      return ptr[lig][col];
    };
    const T& operator()(const size_t col, const size_t lig) const
    {
      return ptr[lig][col];
    };
  };//class
}//namespace

#endif