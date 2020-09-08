Build Commands:

  Ensure OpenGL is installed on your machine
  Unzip the project
  Open Terminal
  Navigate to the root directory of the project e.g. cd Downloads/acl118_asg1/ 
  Run the following commands in order:
  
    g++ -Wall -c main.cpp
    
    g++ -Wall -o main main.cpp -lglut -lGl -lGLU
    
    ./main
