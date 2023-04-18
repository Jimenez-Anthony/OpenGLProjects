# OpenGLProjects

In order to properly use and run the open gl projects you are required to use Visual Studio (preferably 2022 since that is the version that these projects
were developed in). You also need to download and use the OpenGl Library folder that contains all the necessary libraries and files in order to run an OpenGL
project.

After downloading the OpenGl folder contained in this repo, you can download a project folder. Open the solution file and prior to running the project you
will need to add the library directory to the project. To do this is simple:

<img width="592" alt="Screenshot 2023-01-03 141500" src="https://user-images.githubusercontent.com/70342613/210450300-f3a576f5-85ec-487c-80ed-9a85564cd4d3.png">

Right click on the solution in Visual Studio and open up the Properties tab. Once there you will see a menu similar to the image above. Click on VC++ Directories and right click on "External Include Directories". Then select <Edit>.

<img width="287" alt="Screenshot 2023-01-03 141757" src="https://user-images.githubusercontent.com/70342613/210450540-f7cd3b5e-66dd-49bc-9510-8862c5851903.png">

Selecting <Edit> will open a text box like the image above. In that text box type in the exact location that you saved the OpenGL Library files. This will add the libraries to the project, allowing Visual Studio to reference these header files when compiling the project.
  
You will then need to individually add the libraries to the linker's External Dependencies. To do this, refer to the image's and steps below:
  
<img width="586" alt="Screenshot 2023-01-03 142034" src="https://user-images.githubusercontent.com/70342613/210450879-eb7c0bce-38ad-4a44-926b-287c2dc32ac5.png">

In the same menu as the C/C++ dependencies were in you will find a tab below this called "Linker". Clicking on that tab will show more options, one of which being
called "Input". Click on input and you will then be shown new menu options. Select "Additional Dependencies" and then click on the <Edit> button to bring up another
text box.
  
<img width="467" alt="Screenshot 2023-01-03 142251" src="https://user-images.githubusercontent.com/70342613/210451173-7f5eab89-4523-497f-a575-6e4e1283cd1e.png">

 
Once this text box opens, you will then need to individually add each library to the dependency list. The screenshot above contains all the necessary dependencies
needed to run the projects. If any are needed to be added in the future, this is where you will do it. You may then run the projects, but will then run into an additional error that can fixed with ease.
  
If everything compiles with no issue, but you face an error similar to the image below you will need to move the included DLL files downloaded with each project to the x64 folder that has been created once the project can be compiled.
  
<img width="459" alt="Screenshot 2023-01-03 142524" src="https://user-images.githubusercontent.com/70342613/210451568-d0615b60-06dc-48ca-9a21-981de280594c.png">

Once the DLL files are added, the project should run without issues. If you have any further questions on the projects, feel free to email me @ jimenezanthony883@gmail.com
  
 <img width="419" alt="Screenshot 2023-01-03 142755" src="https://user-images.githubusercontent.com/70342613/210451755-dfdea0af-cdb8-41bb-af71-08a96dd13d6c.png">
