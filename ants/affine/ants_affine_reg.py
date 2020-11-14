import ants
import os


files = os.listdir()


files.remove("ants_avg.py")
files.remove("ants_affine_reg.py")
files.remove("ants_sum.nii.gz")
files.remove("ants_avg.nii.gz")
files.remove("KKI2009-01-MPRAGE.nii.gz")

print(files)
print(len(files))

fixed = ants.image_read("KKI2009-01-MPRAGE.nii.gz")
for img in range(len(files)):


    moving = ants.image_read(files[img])

    affine_reg = ants.registration(fixed, moving, type_of_transform="Affine")

    transformed_img = ants.apply_transforms(fixed, moving, transformlist=affine_reg["fwdtransforms"])


    transformed_img.to_filename("affine_"+files[img])
    
    print("finished", float(img / len(files))*100, "%")

