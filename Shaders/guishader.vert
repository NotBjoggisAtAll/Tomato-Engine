#version 330 core

layout(location = 0) in vec2 posAttr;

uniform mat4 mMatrix;
uniform mat4 pMatrix;

out vec2 UV;

void main() {
    gl_Position = mMatrix * vec4(posAttr,0,1);
    UV = vec2((posAttr.x+1.0)/2.0, (posAttr.y+1.0)/2.0);
}
