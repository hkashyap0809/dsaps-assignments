# Implement Seam Carving Algorithm
### Problem Statement: 
Apply seam carving content aware image-resizing algorithm on a given image. Take the height and width (in pixels) of the output image as inputs from the user.<br/>

Original Image:<br/>
Resize Image by cropping<br/>
 
Resize Image by Scaling<br/>
Lowest Energy Seam<br/>
Resize using Seam Carving<br/>
 
### What is Seam Carving?
- Seam-carving is a content-aware image resizing technique where the image is reduced in size by one pixel of height (or width) at a time.
- A vertical seam in an image is a path of pixels connected from the top to the bottom with one pixel in each row.
- A horizontal seam is a path of pixels connected from the left to the right with one pixel in each column.
### Steps:
- Energy Calculation: Each pixel has some RGB values.
- Calculate energy for each pixel. For ex.- You can use dual-gradient energy function but you are free to use any energy function of your choice. Also, you can refer to this link for details.
- Seam Identification: Identify the lowest energy seam.
- Seam Removal: Remove the lowest energy seam.
#### Program Flow:
1. Extract individual pixel’s RGB values from the sample image **./data/input/sample.jpeg** and write them into **./data/input/rgb_in.txt**
2. Load the RGB values from **./data/input/rgb_in.txt** in a 3D matrix.
3. Apply seam carving algorithm.
4. Write the individual pixel’s RGB values for resized image into the **./data/output/rgb_out.txt**
5. Generate sample image output **./data/output/sample_out.jpeg** using the **./data/output/rgb_out.txt.**<br/>

For your convenience we’ve provided you a python script **./src/driver.py** which will perform 1st and 5th task. Also, there is a corresponding **./src/main.cpp** file which will be executed by the python script which will perform the 2nd and 4th task.
#### Your Task:
You have to write the code for seam carving algorithm inside the solve() function of main.cpp. i.e. You just have to perform the 3rd task.<br/>

Dependencies:<br/>
You’ll need to install the python image library Pillow to extract RGB values of each pixel and to generate images back from RGB values of each pixel.<br/>

To install Pillow: **pip install Pillow**<br/>
The python script is only compatible with Linux/Mac operating systems. If there are enough Windows users, we might release the script for Windows too.
     
If you’re a windows user you can request us for the input text file(rgb_in.txt) so that you can start working on the problem.
#### How to Run:
Open the seam-carving directory in the terminal and run the python file driver.py located in /src. Also, you need to pass the input image filename(must be present inside /data/input) as a command line argument.<br/>
Ex: **python ./src/driver.py sample1.jpeg**

#### Evaluation parameters:<br/>
Accuracy and Performance of the code.