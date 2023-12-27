### Readme: OpenGL Visualizer with Shaders

This repository contains a simple OpenGL visualizer implemented in C++ using the Qt framework. The application visualizes geometric shapes and curves, allowing users to interactively add points, lines, polygons, and curves. The project utilizes shaders for rendering, providing flexibility and customization.

### Shaders

The shaders used in this project are written in GLSL (OpenGL Shading Language) and are responsible for controlling the visual appearance of the rendered objects. Here's a brief overview of the shaders:

1. **Vertex Shader (`vertexShader.glsl`):**
   - Handles the transformation of vertex positions.
   - Reads the vertex positions and colors from the buffers.
   - Passes data to the fragment shader.

```glsl
attribute highp vec4 posAttr;
attribute lowp vec4 colAttr;
varying lowp vec4 col;
uniform highp mat4 matrix;
uniform float time;
void main() {
    col = colAttr;
    float scaleSpeed = 0.5;
    float scaleFactor = 1.0 + scaleSpeed * sin(time * scaleSpeed);
    vec4 scaledPosition = posAttr * vec4(scaleFactor, scaleFactor, 1.0, 1.0);
    gl_Position = matrix * scaledPosition;
}
```

2. **Fragment Shader (`fragmentShader.glsl`):**
   - Controls the color of each pixel.
   - Utilizes varying variables to receive data from the vertex shader.
   - Can be dynamically updated to change the rendering appearance.

```glsl
varying lowp vec4 col;
void main() {
    gl_FragColor = col;
}

```

### Usage

1. **Building and Running:**
   - Ensure you have the necessary dependencies installed.
   - Build the project using a C++ compiler.
   - Run the executable.

2. **User Interface:**
   - The UI allows users to add points, lines, polygons, and curves.
   - Region and polygon clipping functionalities are available.
   - Users can change the color of the rendered shapes interactively.

3. **Shaders:**
   - The shaders (`vertexShader.glsl` and `fragmentShader.glsl`) can be modified to customize the rendering.
   - Use the `setColor` method in the `OpenGLWindow` class to dynamically change fragment shader color.

```cpp
void OpenGLWindow::setColor(const QString& text, const QString& filePath) {
    // Code to update the fragment shader with the provided color text.
}
```

### Notes

- This application uses Qt for GUI and OpenGL for rendering.
- Shaders play a crucial role in defining the visual appearance of rendered shapes.

### Author

Ram Agrawal
