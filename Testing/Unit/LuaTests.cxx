#include "SimpleITKTestHarness.h"
#include "SimpleITK.h"

class Lua : public ExternalProgramRunner {
};


TEST_F(Lua,SimpleGaussian) {
  // Run the simple gaussian command line program
  std::string Script = dataFinder.getSourceDirectory() + "/Examples/SimpleGaussian.lua";
  std::string output = dataFinder.getOutputFile ( "Lua.SimpleGaussian.nrrd" );
  std::vector<std::string> CommandLine;
  
  CommandLine.push_back ( dataFinder.getLuaExecutable() );
  CommandLine.push_back ( Script );
  CommandLine.push_back ( dataFinder.getFile ( "Input/HeadMRVolumeWithDirection.nhdr" ).c_str() );
  CommandLine.push_back ( "2.0" );
  CommandLine.push_back ( output );

  // Run it!
  RunExecutable ( CommandLine, true );
  ASSERT_TRUE ( dataFinder.fileExists ( output ) );
  itk::simple::ImageFileReader reader;
  itk::simple::ImageHashFilter hasher;
  itk::simple::Image::Pointer image;

  image = reader.SetFilename ( output ).Execute();
  ASSERT_TRUE ( image->GetImageBase().IsNotNull() ) << "Loaded output image";
  EXPECT_EQ ( "911bdaa4ad90f9c6eeb7a80455564a63d9c29a8a", hasher.Execute ( image ) );

}