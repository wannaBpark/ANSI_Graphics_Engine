# ANSI_Graphics_Engine
This walkthrough project is a simple OpenGL engine featuring multiple rendering scenes, developed as part of the Graphics Study in A.N.S.I. 2023.
For more details, please refer to the original engine [ANSI_Graphics_Engine](https://github.com/shh1473/ANSI_Graphics_Engine), which serves as the foundation for this repository.

## Setup Instructions

Follow these steps to install the required libraries and set up the project:

### Prerequisites

1. Install [vcpkg](https://github.com/microsoft/vcpkg).
2. Integrate vcpkg with your IDE (e.g., Visual Studio):
   ```bash
   .\vcpkg integrate install
   ```

### Install Dependencies

Run the following commands in the terminal to install the required libraries:

```bash
.\vcpkg\vcpkg install glfw3:x64-windows                            # OpenGL Framework
.\vcpkg\vcpkg install glew:x64-windows                             # OpenGL Extension
.\vcpkg\vcpkg install glm:x64-windows                              # OpenGL Mathematics
.\vcpkg\vcpkg install stb:x64-windows                              # Image File Loader
.\vcpkg\vcpkg install tinyobjloader:x64-windows                    # Model File Loader
.\vcpkg\vcpkg install imgui[glfw-binding]:x64-windows              # GUI - GLFW
.\vcpkg\vcpkg install --recurse imgui[opengl3-binding]:x64-windows # GUI - OpenGL3
```

> **Note**: The last command installs Dear ImGui with OpenGL3 binding. The `--recurse` flag ensures that vcpkg resolves any potential conflicts caused by overlapping dependencies.

## Usage

1. Include the installed libraries in your project by adding the appropriate `#include` statements. For example:
   ```cpp
   #include <GLFW/glfw3.h>
   #include <GL/glew.h>
   #include <glm/glm.hpp>
   #include <stb_image.h>
   #include <tiny_obj_loader.h>
   #include <imgui.h>
   ```
2. Compile and run the project using your preferred IDE or build system.

## License

This project is licensed under the LGPL-2.1 License.
The choice of this license is influenced by the inclusion of the Visual Leak Detector library, which is also distributed under the LGPL-2.1 License.

## Third-Party Libraries

The following libraries are used in this project:

| Library         | Version          | License                          |
|------------------|------------------|----------------------------------|
| GLFW            | Latest via vcpkg | zlib License                   |
| GLEW            | Latest via vcpkg | Modified BSD License           |
| GLM             | Latest via vcpkg | MIT License                    |
| stb             | Latest via vcpkg | Public Domain (Unlicense/MIT)  |
| tinyobjloader   | Latest via vcpkg | MIT License                    |
| Dear ImGui      | Latest via vcpkg | MIT License                    |

Please ensure that the licenses of these libraries are followed when using this project in a derived or redistributed form.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## Credits and Acknowledgments

This project is inspired by and based on the work of [**shh1473**](https://github.com/shh1473)'s [ANSI_Graphics_Engine](https://github.com/shh1473/ANSI_Graphics_Engine).  
Special thanks to [**shh1473**](https://github.com/shh1473), the instructor of the 2023 A.N.S.I. Graphics Study, for their contributions to the open-source community, which laid the foundation for this project.
