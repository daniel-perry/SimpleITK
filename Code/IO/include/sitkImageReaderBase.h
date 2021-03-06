#ifndef __sitkImageReaderBase_h
#define __sitkImageReaderBase_h

#include "sitkNonCopyable.h"
#include "sitkPixelIDValues.h"
#include "sitkIO.h"

namespace itk {

// Forward decalaration for pointer
class ImageIOBase;

template<class T>
class SmartPointer;

  namespace simple {

    /** \class ImageReaderBase
     * \brief An abract base class for image readers
     *
     */
    class SITKIO_EXPORT ImageReaderBase :
      protected NonCopyable
    {
    public:
      // The default constructor and the destructor will be implicitly
      // declared as public.

    protected:


      void GetPixelIDFromImageIO( const std::string &fileName,
                                  PixelIDValueType &outPixelType,
                                  unsigned int & outDimensions);

      unsigned int GetDimensionFromImageIO( const std::string &fileName, unsigned int i);

    private:

      PixelIDValueType ExecuteInternalReadScalar( int componentType );

      PixelIDValueType ExecuteInternalReadVector( int componentType );

      PixelIDValueType ExecuteInternalReadComplex( int componentType );

      itk::SmartPointer<ImageIOBase> GetImageIOBase(const std::string &fileName);

    };
  }
}


#endif // __sitkImageReaderBase_h
