import ants
import os
import fnmatch

files = []

for file in os.listdir():
        if fnmatch.fnmatch(file, '20_10_0_deform*'):
            files.append(file)


print(files)
print(len(files))


a = ants.image_read(files[0])


for img in range(1, len(files)):

    print("adding", files[img])
    b = ants.image_read(files[img])

    a += b




a.to_filename("ants_20_10_0_deform_sum.nii.gz")

a /= 21


a.to_filename("ants_20_10_0_deform_avg.nii.gz")

