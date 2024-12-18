
---

**FDF** is a visualization tool for 3D maps. The application reads data from specified files and renders a visual representation, with a LOT of MAGNIFICENT features.

### Features You’ll Love 🎮
- **Dynamic Zoom**: Zoom in and out as you please!
- **Free Navigation**: Move around freely to explore your map from all angles.
- **Intelligent Color Palette**: Colors change based on a ratio, making visualization more intuitive.
- **Dual View**: Enjoy both classic isometric view and side view for more detailed insights.
- **Scale Adjustment**: Change the scale to see your map just the way you want it.
- **File Format Support**: Works with various map file formats. (.fdf ONLY)
- **User-Friendly Interface**: ^^

### Prerequisites 🔧
Before you begin, ensure you have the following installed:
- GCC
- MinilibX (MLX) library
- Make
- Git
- X11 development files (for MinilibX compilation)

On most Unix-based systems, you can install these prerequisites using your package manager. For example, on Ubuntu or Debian, run:

```bash
sudo apt-get update
sudo apt-get install gcc make git libx11-dev libxext-dev
```

For MinilibX, you may need to follow specific installation instructions provided by the library's documentation. It’s really user-friendly, and you can easily find plenty of documentation on MLX.

### To build FDF from source, follow these steps:
1. Clone the repository: 
   ```bash
   git clone git@github.com:pnaessen/FDF.git
   ```
2. Navigate to the project directory:
   ```bash
   cd fdf
   ```
3. Compile the project using Make:
   ```bash
   make
   ```

This will generate the executable named `fdf`.

Once the executable is created, you can run it:

```bash
./fdf test_maps/anymap.fdf
```

You can test any file; I've secured my code, so you can't break it.

### Troubleshooting
No bugs too good, sorry.

### Interaction
Once the program is running, you can interact with the 3D map using the following controls:

#### Mouse Controls:
- **Left Click**: Increase depth effect
- **Right Click**: Decrease depth effect
- **Scroll Up**: Zoom in
- **Scroll Down**: Zoom out

#### Keyboard Controls:
- **Arrow Keys**:
   - Up/Down: Move the camera up/down
   - Left/Right: Move the camera left/right
- **'A' Key**: Reset view angle
- **'D' Key**: Change view angle
- **ESC Key**: Exit the program

### Project Structure 📁
```
├── libft/               # Custom library with utility functions
├── src/                 # Source code files
│   ├── init.c           # Initialization functions
│   ├── parse.c          # File parsing functions
│   ├── algo.c           # Main algorithm implementation
│   ├── dots.c           # Functions for handling map points
│   ├── line.c           # Line drawing algorithms
│   └── hook.c           # Event handling functions
├── include/             # Header files
├── test_maps/           # Sample map files for testing
├── minilibx-linux/      # MinilibX graphics library
└── Makefile             # Compilation and build instructions
```

### 🔍 Additional Resources
- [MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)

### Acknowledgments
A huge thanks to Cdomet-D, Aljulien, Lbuisson, and Vgarcia for their feedback and ideas—they were super helpful in testing everything and catching those bugs! Also, a big shoutout to the awesome **vicperri** who helped make this project happen.

---

