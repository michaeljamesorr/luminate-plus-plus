#version 330 core
out vec4 color;

in vec2 texCoord;

uniform vec3 tint;
uniform float opacity;
uniform sampler2D texData;

void main(){
  vec4 texel = texture(texData, texCoord);
  vec3 rgb;
  if(length(tint)>0){
    rgb = mix(texel.xyz, tint.xyz, 0.5);
  }else{
    rgb = texel.xyz;
  }
  color = vec4(rgb, texel.w*opacity);
}