import ants
import os
import fnmatch

files = []

for file in os.listdir():
    if fnmatch.fnmatch(file, 'affine_*'):
        files.append(file)


print(files)
print(len(files))


fixed = ants.image_read("ants_affine_avg.nii.gz")
for img in range(len(files)):


    moving = ants.image_read(files[img])

    deformable_reg = ants.registration(fixed, moving, type_of_transform="ElasticSyN", reg_iterations=(20, 10, 0), verbose=1)

    transformed_img = ants.apply_transforms(fixed, moving, transformlist=deformable_reg["fwdtransforms"])


    transformed_img.to_filename("20_10_0_deform_"+files[img])
    
    print("finished", float(img / len(files))*100, "%")

