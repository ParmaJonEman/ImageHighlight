# Highlight
### Setup

- [Install OpenCV](https://opencv.org/releases/), and replace the path in the CMAKE file on the find_package line with your new path
- If you're on Windows, [download dirent.h](https://github.com/tronkko/dirent) and put in your linker's include folder
- Build the project with the standard CMAKE build commands

### Run

- Run the application via the command line with the following usage patten:
    - highlight.exe \<image\>
- Example:
    - hightlight.exe cat.jpg
- Key commands:
    - Left click and release to select a region of interest. 
    - Press any key to escape