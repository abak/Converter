#if !defined(ARRAY2D_HPP)
#define ARRAY2D_HPP

#include <vector>


template<typename T>
class Array2D
{
  std::vector<T>  m_data;
  std::vector<T*> m_ptr;
  size_t m_iWidth;
  size_t m_iHeight;
  
  void Link(void)
  {
    for (unsigned int j = 0; j < m_iHeight; ++j)
      m_ptr[j] = &m_data[j * m_iWidth];
  }
  
  
public:
  Array2D(void)
  {
  };
  Array2D(const size_t i_width, const size_t i_height) :
  m_iWidth(i_width),
  m_iHeight(i_height),
  m_data(i_width * i_height),
  m_ptr(i_height)
  {
    Link();
  }
  
  
  void Resize(const size_t niou_width, const size_t niou_height)
  {
    if (m_iWidth == niou_width && m_iHeight == niou_height)
      return;
    
    m_iWidth  = niou_width;
    m_iHeight = niou_height;
    
    m_data.resize(niou_height * niou_width);
    m_ptr.resize(niou_height);
    Link();
  }
  
  
  typename std::vector<T>::iterator begin(void)
  {
    return m_data.begin();
  }
  
  
  typename std::vector<T>::iterator end(void)
  {
    return m_data.end();
  }
  
  
  void assign(T value)
  {
    m_data.assign(m_iWidth * m_iHeight, value);
  }
  
  
  Array2D(const Array2D& a) :
  m_iWidth(a.m_iWidth),
  m_iHeight(a.m_iHeight),
  m_data(a.m_data)
  {
    m_ptr.resize(m_iHeight);
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
    swap(first.m_iHeight, second.m_iHeight);
    swap(first.m_iWidth, second.m_iWidth);
    swap(first.m_data, second.m_data);
    swap(first.m_ptr, second.m_ptr);
  }
  
  ~Array2D()
  {
  };
  
  T* operator[](const size_t ligne)
  {
    return m_ptr[ligne];
  };
  const T* operator[](const size_t ligne) const
  {
    return m_ptr[ligne];
  };
  
  T& operator()(const size_t col, const size_t lig)
  {
    return m_ptr[lig][col];
  };
  const T& operator()(const size_t col, const size_t lig) const
  {
    return m_ptr[lig][col];
  };


#endif