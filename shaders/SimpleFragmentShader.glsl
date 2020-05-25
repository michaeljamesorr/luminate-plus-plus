#version 330 core
out vec4 color;

uniform vec3 tint;
uniform float opacity;

void main(){
  color = vec4(tint.xyz, opacity);
}