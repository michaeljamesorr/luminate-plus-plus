#version 330 core
out vec4 color;

in vec2 texCoord;

uniform vec3 tint;
uniform float opacity;
uniform sampler2D texData;

void main(){
  vec4 texel = texture(texData, texCoord);
  color = texel; //mix(texel, vec4(tint.xyz, opacity), 0.5);
}