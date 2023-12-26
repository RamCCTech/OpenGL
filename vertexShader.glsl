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