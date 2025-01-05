# Skeleton for C project

This is an adaptation of a skeleton provided for system programming exercices, adapted to work on all plateforms with Clion.  
You need some setup in order to use it for real linux-like system programming :

### Steps to run it from your IDE on Windows

- Install a WSL distro with all build-essential packages (and cmake / gdb if not provided with)
- Create a new toolchain in Clion from File/Build, Deployment, Execution/Toolchain
- Select WSL and it should detect your WSL config with all required packages
- Delete cmake-build-debug folder if it was already created before and generate project with cmakelist.txt

### Using the skeleton

Once you run the skeleton profile on your Clion IDE, you should see a message in the console indicating invalid paramters usage.  
You can set parameter by editing the skeleton executable profile in the specific field for this (try adding -h and run again, you'll see)
