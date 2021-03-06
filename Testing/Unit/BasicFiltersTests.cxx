#include <SimpleITKTestHarness.h>

#include <sitkImage.h>
#include <sitkImageFileReader.h>
#include <sitkImageFileWriter.h>
#include <sitkHashImageFilter.h>
#include <sitkRecursiveGaussianImageFilter.h>
#include <sitkCastImageFilter.h>
#include <sitkPixelIDValues.h>
#include <sitkLabelStatisticsImageFilter.h>
#include <sitkExtractImageFilter.h>
#include <sitkFastMarchingImageFilter.h>
#include <sitkScalarToRGBColormapImageFilter.h>
#include <sitkJoinSeriesImageFilter.h>

#include "itkRecursiveGaussianImageFilter.h"
#include "itkExtractImageFilter.h"
#include "itkFastMarchingImageFilterBase.h"
#include "itkScalarToRGBColormapImageFilter.h"

TEST(BasicFilters,ScalarToRGBColormap_ENUMCHECK) {
  typedef itk::ScalarToRGBColormapImageFilter< itk::Image<float,3>, itk::Image< itk::RGBPixel<float>,3> > ITKType;
  EXPECT_EQ( (int)ITKType::Red, (int)itk::simple::ScalarToRGBColormapImageFilter::Red);
  EXPECT_EQ( (int)ITKType::Green, (int)itk::simple::ScalarToRGBColormapImageFilter::Green);
  EXPECT_EQ( (int)ITKType::Blue, (int)itk::simple::ScalarToRGBColormapImageFilter::Blue);
  EXPECT_EQ( (int)ITKType::Grey, (int)itk::simple::ScalarToRGBColormapImageFilter::Grey);
  EXPECT_EQ( (int)ITKType::Hot, (int)itk::simple::ScalarToRGBColormapImageFilter::Hot);
  EXPECT_EQ( (int)ITKType::Cool, (int)itk::simple::ScalarToRGBColormapImageFilter::Cool);
  EXPECT_EQ( (int)ITKType::Spring, (int)itk::simple::ScalarToRGBColormapImageFilter::Spring);
  EXPECT_EQ( (int)ITKType::Summer, (int)itk::simple::ScalarToRGBColormapImageFilter::Summer);
  EXPECT_EQ( (int)ITKType::Autumn, (int)itk::simple::ScalarToRGBColormapImageFilter::Autumn);
  EXPECT_EQ( (int)ITKType::Winter, (int)itk::simple::ScalarToRGBColormapImageFilter::Winter);
  EXPECT_EQ( (int)ITKType::Copper, (int)itk::simple::ScalarToRGBColormapImageFilter::Copper);
  EXPECT_EQ( (int)ITKType::Jet, (int)itk::simple::ScalarToRGBColormapImageFilter::Jet);
  EXPECT_EQ( (int)ITKType::HSV, (int)itk::simple::ScalarToRGBColormapImageFilter::HSV);
  EXPECT_EQ( (int)ITKType::OverUnder, (int)itk::simple::ScalarToRGBColormapImageFilter::OverUnder);
}

TEST(BasicFilters,RecursiveGaussian_ENUMCHECK) {

  typedef itk::RecursiveGaussianImageFilter< itk::Image<float,3> > ITKRecursiveGausianType;
  EXPECT_EQ( (int)ITKRecursiveGausianType::ZeroOrder, (int)itk::simple::RecursiveGaussianImageFilter::ZeroOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::FirstOrder, (int)itk::simple::RecursiveGaussianImageFilter::FirstOrder );
  EXPECT_EQ( (int)ITKRecursiveGausianType::SecondOrder, (int)itk::simple::RecursiveGaussianImageFilter::SecondOrder );
}


TEST(BasicFilters,Extract_ENUMCHECK) {

  typedef itk::ExtractImageFilter< itk::Image<float,3>, itk::Image<float,3> > ITKExtractType;
  EXPECT_EQ( (int)ITKExtractType::DIRECTIONCOLLAPSETOUNKOWN, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOUNKOWN );
  EXPECT_EQ( (int)ITKExtractType::DIRECTIONCOLLAPSETOIDENTITY, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOIDENTITY );
  EXPECT_EQ( (int)ITKExtractType::DIRECTIONCOLLAPSETOSUBMATRIX, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOSUBMATRIX );
  EXPECT_EQ( (int)ITKExtractType::DIRECTIONCOLLAPSETOGUESS, (int)itk::simple::ExtractImageFilter::DIRECTIONCOLLAPSETOGUESS );

}


TEST(BasicFilters,FastMarching_ENUMCHECK) {

  typedef itk::FastMarchingImageFilterBase< itk::Image<float,3>, itk::Image<float,3> > ITKType;

  EXPECT_EQ( (int) ITKType::Nothing, (int) itk::simple::FastMarchingImageFilter::Nothing );
  EXPECT_EQ( (int) ITKType::NoHandles, (int) itk::simple::FastMarchingImageFilter::NoHandles );
  EXPECT_EQ( (int) ITKType::Strict, (int) itk::simple::FastMarchingImageFilter::Strict );
}

TEST(BasicFilters,Cast) {
  itk::simple::HashImageFilter hasher;
  itk::simple::ImageFileReader reader;

  reader.SetFileName ( dataFinder.GetFile ( "Input/RA-Float.nrrd" ) );
  itk::simple::Image image = reader.Execute();
  ASSERT_TRUE ( image.GetITKBase() != NULL );
  hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
  EXPECT_EQ ( "3ccccde44efaa3d688a86e94335c1f16", hasher.Execute ( image ) );

  EXPECT_EQ ( image.GetPixelIDValue(), itk::simple::sitkFloat32 );
  EXPECT_EQ ( image.GetPixelIDTypeAsString(), "32-bit float" );

  typedef std::map<std::string,itk::simple::PixelIDValueType> MapType;
  MapType mapping;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt32;
  mapping["efa4c3b27349b97b02a64f3d2b5ca9ed"] = (itk::simple::PixelIDValueType)itk::simple::sitkUInt64;
  mapping["sitkInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = (itk::simple::PixelIDValueType)itk::simple::sitkFloat64;
  mapping["226dabda8fc07f20e2b9e44ca1c83955"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat32;
  mapping["e92cbb187a92610068d7de0cb23364db"] = (itk::simple::PixelIDValueType)itk::simple::sitkComplexFloat64;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt8;
  mapping["2f27e9260baeba84fb83dd35de23fa2d"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt8;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt16;
  mapping["a963bd6a755b853103a2d195e01a50d3"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt16;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt32;
  mapping["6ceea0011178a955b5be2d545d107199"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt32;
  mapping["sitkVectorUInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorUInt64;
  mapping["sitkVectorInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorInt64;
  mapping["3ccccde44efaa3d688a86e94335c1f16"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat32;
  mapping["ac0228acc17038fd1f1ed28eb2841c73"] = (itk::simple::PixelIDValueType)itk::simple::sitkVectorFloat64;
  mapping["sitkLabelUInt8"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt8;
  mapping["sitkLabelUInt16"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt16;
  mapping["sitkLabelUInt32"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt32;
  mapping["sitkLabelUInt64"] = (itk::simple::PixelIDValueType)itk::simple::sitkLabelUInt64;

  bool failed = false;

  // Loop over the map, load each file, and compare the hash value
  for ( MapType::iterator it = mapping.begin(); it != mapping.end(); ++it )
    {
    itk::simple::PixelIDValueType pixelID = it->second;
    std::string hash = it->first;

    std::cerr << std::flush;
    std::cerr << std::flush;
    if ( pixelID == itk::simple::sitkUnknown )
      {
      std::cerr << "Enum value: " << pixelID << " (" << hash << ") is unknown and not instantiated" << std::endl;
      continue;
      }

    std::cerr << "Testing casting to pixelID: " << pixelID << " is " << itk::simple::GetPixelIDValueAsString ( pixelID ) << std::endl;

    try
      {
      itk::simple::CastImageFilter caster;
      itk::simple::Image test = caster.SetOutputPixelType ( pixelID ).Execute ( image );

      hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 );
      EXPECT_EQ ( hash, hasher.Execute ( test ) ) << "Cast to " << itk::simple::GetPixelIDValueAsString ( pixelID );

      }
    catch ( ::itk::simple::GenericException &e )
      {

      // hashing currently doesn't work for label images
      if ( hash.find( "sitkLabel" ) == 0 )
        {
        std::cerr << "Hashing currently is not implemented for Label Images" << std::endl;
        }
      else
        {
        failed = true;
        std::cerr << "Failed to hash: " << e.what() << std::endl;
        }

      continue;
      }

  }
  EXPECT_FALSE ( failed ) << "Cast failed, or could not take the hash of the imoge";

}

TEST(BasicFilters,HashImageFilter) {
  itk::simple::HashImageFilter hasher;
  EXPECT_EQ ( "itk::simple::HashImageFilter\nHashFunction: SHA1\n", hasher.ToString() );
  EXPECT_EQ ( itk::simple::HashImageFilter::SHA1, hasher.SetHashFunction ( itk::simple::HashImageFilter::SHA1 ).GetHashFunction() );
  EXPECT_EQ ( itk::simple::HashImageFilter::MD5, hasher.SetHashFunction ( itk::simple::HashImageFilter::MD5 ).GetHashFunction() );
}

TEST(BasicFilters,LabelStatistics) {
  itk::simple::Image image = itk::simple::ReadImage ( dataFinder.GetFile ( "Input/cthead1.png" ) );
  itk::simple::Image labels = itk::simple::ReadImage ( dataFinder.GetFile ( "Input/2th_cthead1.mha" ) );

  itk::simple::LabelStatisticsImageFilter stats;
  stats.Execute ( image, labels );

  EXPECT_TRUE ( stats.HasLabel ( 0 ) );
  EXPECT_NEAR ( stats.GetMinimum ( 0 ), 0, 0.01 );
  EXPECT_NEAR ( stats.GetMaximum ( 0 ), 99, 0.01 );
  EXPECT_NEAR ( stats.GetMean ( 0 ), 13.0911, 0.001 );
  EXPECT_NEAR ( stats.GetSigma ( 0 ),  16.4065, 0.01 );
  EXPECT_NEAR ( stats.GetVariance ( 0 ),  269.173, 0.01 );
  EXPECT_NEAR ( stats.GetCount ( 0 ),  36172, 0.01 );
  EXPECT_NEAR ( stats.GetSum ( 0 ),  473533, 0.01 );
  EXPECT_NEAR ( stats.GetMedian ( 0 ), 12.0, 0.001 );

  const itk::simple::LabelStatisticsImageFilter::LabelListingType myLabels = stats.GetValidLabels();
  EXPECT_EQ ( myLabels.size() , 3u);

  const itk::simple::LabelStatisticsImageFilter::LabelStatisticsMap myMap = stats.GetLabelStatisticsMap();
  EXPECT_EQ( myLabels.size() , myMap.size() );

  const itk::simple::MeasurementMap myMeasurementMap = stats.GetMeasurementMap(0);
  EXPECT_EQ( myMeasurementMap.size(), 8u ); //4 measurements produced

  const itk::simple::BasicMeasurementMap myBasicMeasurementMap =
    myMeasurementMap.GetBasicMeasurementMap();
  EXPECT_EQ( myBasicMeasurementMap.size(), 8u ); //4 measurements produced

  EXPECT_EQ ( myMeasurementMap.ToString(), "Count, Maximum, Mean, Minimum, Sigma, Sum, Variance, approxMedian, \n36172, 99, 13.0911, 0, 16.4065, 473533, 269.173, 12, \n" );
}

TEST(BasicFilters,JoinSeriesImageFilter) {
  itk::simple::JoinSeriesImageFilter j;

  EXPECT_EQ( j.GetName(), std::string( "JoinSeries" ) );
  EXPECT_NO_THROW( j.ToString() );

  EXPECT_EQ ( j.GetSpacing(), 1.0 );
  EXPECT_EQ ( j.GetOrigin(), 0.0 );

  itk::simple::Image image = itk::simple::ReadImage ( dataFinder.GetFile ( "Input/cthead1.png" ) );

  std::vector< itk::simple::Image > v( 5, image );

  itk::simple::Image result = itk::simple::JoinSeries( v, 2.0, 0.5 );

  EXPECT_EQ ( result.GetSpacing()[2], 2.0 );
  EXPECT_EQ ( result.GetOrigin()[2], 0.5 );

  std::cout << result.ToString();

  EXPECT_EQ ( itk::simple::Hash( result ), "04a39fb32832eef77e1cf8570d94e10cc75eb525" );
}
