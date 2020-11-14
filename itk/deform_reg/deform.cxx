#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

#include "itkImageRegistrationMethod.h"
#include "itkMultiResolutionImageRegistrationMethod.h"
#include "itkAffineTransform.h"
#include "itkMeanSquaresImageToImageMetric.h"
#include "itkRegularStepGradientDescentOptimizer.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkResampleImageFilter.h"
#include "itkMattesMutualInformationImageToImageMetric.h"
#include <itkMeanSquaresImageToImageMetric.h>
#include "itkLBFGSBOptimizerv4.h"
#include "itkBSplineTransformInitializer.h"


#include "itkBSplineTransform.h"


#include "itkCommand.h"

const unsigned int nDims = 3 ;
typedef itk::Image < double, nDims > ImageType ;

class OptimizerIterationCallback : public itk::Command
{
public:
  // itk set up such that things like pointers and new() are available for this class
  //OptimizerIterationCallback::Pointer myCallback = OptimizerIterationCallback::New() ;
  // standard things we need in every itk-inheriting class
  typedef OptimizerIterationCallback Self ;
  typedef itk::Command Superclass ;
  typedef itk::SmartPointer<OptimizerIterationCallback> Pointer ;
  itkNewMacro(OptimizerIterationCallback);

  // specific typedefs we need for our observer
  typedef itk::RegularStepGradientDescentOptimizer OptimizerType ;
  //typedef itk::LBFGSBOptimizerv4 OptimizerType;

  typedef const OptimizerType * OptimizerPointerType ;

  // if i want to change things in my caller
 void
 Execute(itk::Object * caller, const itk::EventObject & event) 
  {
    Execute((const itk::Object *)caller, event);
  }
 
  // if i am just observing the caller (no changes)
  void
  Execute(const itk::Object * caller, const itk::EventObject & event) 
  {
    // somehow get my hands on the optimizer 
    // caller is the optimizer, but it's of the wrong type, but i know it is an optimizer so i can cast it to the optimizer type
    OptimizerPointerType optimizer = dynamic_cast < OptimizerPointerType > ( caller )  ;
    std::cout << optimizer->GetCurrentIteration() << " " << optimizer->GetValue() << std::endl ;
  }
};

class RegistrationIterationCallback : public itk::Command
{
public:
  // itk set up such that things like pointers and new() are available for this class
  //OptimizerIterationCallback::Pointer myCallback = OptimizerIterationCallback::New() ;
  // standard things we need in every itk-inheriting class
  typedef RegistrationIterationCallback Self ;
  typedef itk::Command Superclass ;
  typedef itk::SmartPointer<RegistrationIterationCallback> Pointer ;
  itkNewMacro(RegistrationIterationCallback);

  // specific typedefs we need for our observer
  typedef itk::RegularStepGradientDescentOptimizer OptimizerType ;

  //typedef itk::LBFGSBOptimizerv4 OptimizerType;
  typedef OptimizerType * OptimizerPointerType ;
  
  typedef itk::ImageRegistrationMethod < ImageType, ImageType > RegistrationMethodType ;
  typedef RegistrationMethodType * RegistrationPointerType ;

  // if i want to change things in my caller
 void
 Execute(itk::Object * caller, const itk::EventObject & event) 
  {
    // somehow get my hands on the registration method 
    // caller is the registration method
    RegistrationPointerType registration = dynamic_cast < RegistrationPointerType > ( caller ) ;
    //std::cout << "Level: " << registration->GetCurrentLevel () << std::endl ;

    OptimizerPointerType optimizer = dynamic_cast < OptimizerPointerType > ( registration->GetModifiableOptimizer() ) ;

    optimizer->SetMaximumStepLength ( optimizer->GetMaximumStepLength() * 0.5 ) ;
    /*
    if ( registration->GetCurrentLevel() == 0 )
      optimizer->SetMaximumStepLength ( 0.25 ) ;
    else if ( registration->GetCurrentLevel() == 1 )
      optimizer->SetMaximumStepLength ( 0.125 ) ;
    else
      optimizer->SetMaximumStepLength ( 0.125 ) ;
    */
  }
 
  // if i am just observing the caller (no changes)
  void
  Execute(const itk::Object * caller, const itk::EventObject & event) 
  {
    // nothing
  }
};

int main ( int argc, char * argv[] )
{
  // Verify command line arguments
  //if( argc < 4 )
  //  {
    //std::cerr << "Usage: " << std::endl ;
    //std::cerr << argv[0] << " inputMovingImageFile inputFixedImageFile outputRegisteredImageFile" << std::endl ; 
  //  return -1 ;
  //  }

    int arr_length = 21;

    // The 21 filepaths

    std::string files[arr_length] = {

                                          "../../itk_ants_assignment-build/KKI2009-ALL-MPRAGE-NO-DUPLICATES/KKI2009-01-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-02-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-03-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-04-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-05-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-06-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-07-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-08-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-09-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-10-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-12-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-13-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-14-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-15-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-16-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-18-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-23-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-28-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-30-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-32-MPRAGE.nii.gz",
                                          "../affine_reg-build/registered_KKI2009-39-MPRAGE.nii.gz"
					};



  // Setup types
  //const unsigned int nDims = 3 ;
  //typedef itk::Image < int, nDims > ImageType ;
  typedef itk::ImageFileReader < ImageType > ImageReaderType ; 
  typedef itk::ImageFileWriter < ImageType > ImageWriterType ;
  

  // set up typedefs (don't forget to include the header files)
  //  typedef itk::ImageRegistrationMethod < ImageType, ImageType > RegistrationMethodType ;
  typedef itk::ImageRegistrationMethod < ImageType, ImageType > RegistrationMethodType ;
  typedef itk::AffineTransform < double, 3 > AffineTransformType ; // leaving at default values, could skip it

  typedef itk::BSplineTransform<double, 3, 3> BSplineTransformType;

  typedef itk::MattesMutualInformationImageToImageMetric < ImageType, ImageType > MetricType ;
  
  //typedef itk::MeanSquaresImageToImageMetric < ImageType, ImageType > MetricType ;
  typedef itk::RegularStepGradientDescentOptimizer OptimizerType ; // no template arguments
  //typedef itk::LBFGSBOptimizerv4 OptimizerType;
  typedef itk::LinearInterpolateImageFunction < ImageType > InterpolatorType ;
  typedef itk::ResampleImageFilter < ImageType, ImageType > ResampleFilterType ;
  typedef itk::BSplineTransformInitializer<BSplineTransformType, ImageType> InitializerType;


  for (int i=0; i< arr_length; i++){

	  std::cout << files[i] << std::endl;
	  std::cout<<i<<std::endl;
 
	  // Always register to same fixed image
	  ImageReaderType::Pointer fixedReader = ImageReaderType::New() ; 
	  fixedReader->SetFileName ( "../affine_template-build/affine_avg.nii.gz" );
	  fixedReader->Update() ;


	  // read in each moving image
	  ImageReaderType::Pointer movingReader = ImageReaderType::New() ; 
	  movingReader->SetFileName ( files[i] ) ;
	  movingReader->Update() ;


	  // Registration!


	  // declare the variables
	  RegistrationMethodType::Pointer registrationMethod = RegistrationMethodType::New() ;
	  BSplineTransformType::Pointer transform = BSplineTransformType::New ();
	  MetricType::Pointer metric = MetricType::New () ;
	  OptimizerType::Pointer optimizer = OptimizerType::New() ;
	  InterpolatorType::Pointer interpolator = InterpolatorType::New() ;

	  InitializerType::Pointer transformInitializer = InitializerType::New();


	  // deform stuff
	  const unsigned int numberOfGridNodes = 10;
	  

	  ImageType::ConstPointer fixedImage = fixedReader->GetOutput();

	  //ImageType::RegionType fixedRegion = fixedImage->GetBufferedRegion();
	  
	  //ImageType::SizeType   fixedSize = fixedRegion.GetSize();
          
	  //ImageType::PointType     fixedOrigin = fixedImage->GetOrigin();
          //ImageType::DirectionType fixedDirection = fixedImage->GetDirection();


	
	  // ImageType::SpacingType fixedSpacing = fixedImage->GetSpacing();
	  //BSplineTransformType::PhysicalDimensionsType fixedPhysicalDimensions;
          BSplineTransformType::MeshSizeType           meshSize;
 	  
	  /* 
	  for (unsigned int j = 0; j < nDims; j++)
	  {
	    fixedPhysicalDimensions[j] =
	      fixedSpacing[j] * static_cast<double>(fixedSize[j] - 1);
	  }
		*/

	  meshSize.Fill(numberOfGridNodes - 3);
	  transformInitializer->SetTransform(transform);
	  transformInitializer->SetImage(fixedImage);
	  transformInitializer->SetTransformDomainMeshSize(meshSize);
      	  transformInitializer->InitializeTransform();



	  //transform->SetTransformDomainOrigin(fixedOrigin);
	  //transform->SetTransformDomainPhysicalDimensions(
          //fixedPhysicalDimensions);
	  //transform->SetTransformDomainMeshSize(meshSize);
	  //transform->SetTransformDomainDirection(fixedDirection);
 
 
	  typedef BSplineTransformType::ParametersType ParametersType;
	  const unsigned int numberOfParameters = transform->GetNumberOfParameters();
	 
	  //const unsigned int numberOfNodes = numberOfParameters / nDims;
	 
	  ParametersType parameters(numberOfParameters);
	  parameters.Fill(0.0);
	  transform->SetParameters(parameters);
 

	  // connect the pipeline
	  registrationMethod->SetMovingImage ( movingReader->GetOutput() ) ;
	  registrationMethod->SetFixedImage ( fixedReader->GetOutput() ) ;
	  registrationMethod->SetOptimizer ( optimizer ) ;
	  registrationMethod->SetMetric ( metric ) ;
	  registrationMethod->SetInterpolator ( interpolator ) ;
	  




 	  //registrationMethod->SetInitialTransformParameters(transform->GetParameters());	  
	  registrationMethod->SetTransform ( transform ) ;
	  const unsigned int numberOfLevels = 1;
 
	  //registrationMethod->SetNumberOfLevels(numberOfLevels);
  	  //registration->SetSmoothingSigmasPerLevel(smoothingSigmasPerLevel);

	  const unsigned int numParameters = transform->GetNumberOfParameters();
	  

	  // set up the relevant parameters
	  //optimizer->MinimizeOn () ;
	  optimizer->SetNumberOfIterations ( 200 ) ;

	  std::cout << "Min: " << optimizer->GetMinimumStepLength () << std::endl ;
	  std::cout << "Max: " << optimizer->GetMaximumStepLength () << std::endl ;
	  std::cout << "Current: " << optimizer->GetCurrentStepLength () << std::endl ;

	  optimizer->SetMinimumStepLength ( 0.0001 ) ;
	  optimizer->SetMaximumStepLength ( 2.00 ) ; // TODO: might want to adjust this some more

	  transform->SetParameters(parameters);

	  //transform->SetIdentity () ;
	  registrationMethod->SetInitialTransformParameters ( transform->GetParameters() ) ;
	 

	  // set up the callback function
	  OptimizerIterationCallback::Pointer myCallback = OptimizerIterationCallback::New();
	  optimizer->AddObserver(itk::IterationEvent(), myCallback);

	  // set up the second callback for the registration method
	  RegistrationIterationCallback::Pointer myRegCallback = RegistrationIterationCallback::New() ;
	  registrationMethod->AddObserver ( itk::IterationEvent(), myRegCallback ) ;

	  //registrationMethod->SetNumberOfLevels ( 3 ) ;
	  registrationMethod->SetFixedImageRegion ( fixedReader->GetOutput()->GetLargestPossibleRegion() ) ;

	  // run the registration
	  // TODO: put this in a try-catch block
	  registrationMethod->Update() ;

	  // why did it stop?
	  std::cout << optimizer->GetStopConditionDescription () << std::endl ;

	  //transform->SetParameters(parameters);



	  // apply the transform we get from the registration
	  ResampleFilterType::Pointer resampleFilter = ResampleFilterType::New() ;
	  resampleFilter->SetInput ( movingReader->GetOutput() ) ;
	  // transform that we are applying
	  resampleFilter->SetTransform ( transform ) ;
	  // set the grid to where the fixed image is, just in case it moved too far
	  resampleFilter->SetReferenceImage ( fixedReader->GetOutput() ) ;
	  resampleFilter->UseReferenceImageOn () ;

	  // update
	  resampleFilter->Update() ;

	 
	  // Write out the result  
	  ImageWriterType::Pointer writer = ImageWriterType::New() ; 
	  if(i==0)
	  {
		std::cout << i << std::endl;   
		writer->SetFileName ( "1_BSpline_registered_KKI2009-01-MPRAGE.nii.gz"  ) ;
	  }
	  else{
		std::cout << i << std::endl;
		writer->SetFileName ( "1_BSpline_" + files[i].substr(20)  ) ;
	  }
	  writer->SetInput ( resampleFilter->GetOutput() ) ; // need to figure out the argument here
	  writer->Update() ;
  }

  // Done.
  return 0 ;
}
