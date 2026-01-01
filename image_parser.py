from PIL import Image
import os
import sys

def convert_image(file_path, target_format): 
    
    img = Image.open(file_path) 
    # Get the file name without extension and the directory 
    file_name = os.path.splitext(os.path.basename(file_path))[0] 
    directory = os.path.dirname(file_path)
    # Define new file path 
    new_file_path = f"{file_name}.{target_format}" 
    # print(f"AQUI POHA{new_file_path}")
  
    # Save the image with the new format 
    img.save(new_file_path) 
    
    # print(f"Image converted and saved at {new_file_path}")


convert_image(sys.argv[1], "ppm")