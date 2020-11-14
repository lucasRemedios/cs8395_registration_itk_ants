#include "itkImage.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"
#include "itkNaryAddImageFilter.h"
#include "itkAddImageFilter.h"
#include "itkDivideImageFilter.h"
#include <string>
#include <iostream>

// Define custom types
typedef itk::Image < double, 3 > ImageType ;
typedef itk::ImageFileReader < ImageType > ImageReaderType ; 
typedef itk::NaryAddImageFilter<ImageType, ImageType>AdditionType;
typedef itk::ImageFileWriter < ImageType > ImageWriterType ;
typedef itk::DivideImageFilter<ImageType, ImageType, ImageType> DivisionType;




int main ( int argc, char * argv[] )
{
	int arr_length = 21;
	// The 21 filepaths
	std::string files[arr_length] = {   
				"/home/remedilw/cs_8395/itk_ants_assignment-build/KKI2009-ALL-MPRAGE-NO-DUPLICATES/KKI2009-01-MPRAGE.nii.gz", 
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

	
	// Sum the images using ITK utility
	AdditionType::Pointer sum_files = AdditionType::New();
 
	// Sum the 21 images	
	for (int i=0; i<21; i++){

		// read in each image 
		ImageReaderType::Pointer reader = ImageReaderType::New() ; //creating pointer outside loop fails...
		reader->SetFileName ( files[i]  );
		reader->Update() ;
		
		// Sum
		sum_files->SetInput( i, reader->GetOutput()  );	
	}	

	// Average the sum
	DivisionType::Pointer avg = DivisionType::New();
	sum_files->Update();
	avg->SetInput(   sum_files->GetOutput()  );
	avg->SetConstant( arr_length );
	avg->Update();
	
	// Write the output to file
	ImageWriterType::Pointer out = ImageWriterType::New();
	out->SetInput(avg->GetOutput());
	out->SetFileName("affine_avg.nii.gz");
	out->Update();


	return 0;

}


