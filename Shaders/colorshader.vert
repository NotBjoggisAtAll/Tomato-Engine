#version 330 core

layout(location = 0) in vec4 posAttr;
layout(location = 1) in vec4 colAttr;
uniform mat4 mMatrix;
uniform mat4 vMatrix;
uniform mat4 pMatrix;

void main() {
   gl_Position = pMatrix * vMatrix * mMatrix * posAttr;
}
