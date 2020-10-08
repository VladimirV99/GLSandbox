# GLSandbox

Environment for developing OpenGL applications with pre-installed libraries and a set of demos.

## Included libraries

- [assimp](https://github.com/assimp/assimp) - A library to import and export various 3d model formats
- [glad](https://github.com/Dav1dde/glad) - GL/GLES/EGL/GLX/WGL loader
- [glfw](https://github.com/glfw/glfw) - Multi-platform library for OpenGL, OpenGL ES and Vulkan
- [glm](https://github.com/g-truc/glm) - Header only C++ mathematics library
- [imgui](https://github.com/ocornut/imgui) - Bloat-free graphical user interface library for C++
- [stb_image](https://github.com/nothings/stb) - Image loading/decoding library

## Adding libraries from scratch

Make a directory for the libraries and navigate to it.
```bash
mkdir libs
cd libs
```

Add glad to the libs directory by extracting the generated C/C++ OpenGL Core profile files from https://glad.dav1d.de/.
In this project, OpenGL version 4.2 is used.
Then add other modules using git
```bash
git submodule add https://github.com/glfw/glfw.git
git submodule add https://github.com/g-truc/glm.git
git submodule add https://github.com/ocornut/imgui.git
git submodule add https://github.com/nothings/stb.git
git submodule add https://github.com/assimp/assimp.git
```

Finally copy the CMakeLists.txt file and all cmake files from this projects libs directory to your own.
To use the libraries just include the libs CMakeLists file in your project CMake configuration.

## Updating libraries

glad is updated by going to https://glad.dav1d.de/ and generating files for a newer version.
All submodule based libraries are updated by pulling the changes from git
```bash
cd libs/library_name
git checkout master
git pull
cd ../..
```
After updating, the changes should be commited to the repository

## License

GLSandbox is not licenced. You are free to do anything you want with the code, no restrictions or limitations.

## Contributing

Feel free to contribute to the project either by submitting issues or making pull requests.

Thank you for the help :blush: