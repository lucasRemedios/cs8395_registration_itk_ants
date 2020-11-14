import ants
import os


files = os.listdir()

files.remove("ants_avg.py")
print(files)
print(len(files))

a = ants.image_read(files[0])


for img in range(1, len(files)):


    b = ants.image_read(files[img])

    a += b




a.to_filename("ants_sum.nii.gz")

a /= 21


a.to_filename("ants_avg.nii.gz")

