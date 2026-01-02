from PIL import Image
import os
import sys

def convert_image(file_path, target_format, size=(0, 0)): 
    directory = os.path.dirname(file_path)
    print(directory)
    img = Image.open(file_path) 
    if size != (0, 0):
        img = img.resize(size)

    file_name = os.path.splitext(os.path.basename(file_path))[0] 
    
    new_file_path = f"{file_name}.{target_format}" if directory == '' else f"{directory}/{file_name}.{target_format}" 
    img.save(new_file_path) 

#Da pra otimizar isso bastante na vdd
# print((len(sys.argv) - 1))
try:
    convert_image(sys.argv[1], "ppm", (int(sys.argv[2]), int(sys.argv[3])))
    exit()

except IndexError:  
    convert_image(sys.argv[1], "ppm", (0, 0))
    exit()

print("Error") #Na teoria é pra nunca acontecer!