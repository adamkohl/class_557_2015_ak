//  Adam Kohl and Jiazhong Zhou
//  noise.fs

#version 410 core

uniform sampler2D texture_background; //landscape
uniform sampler2D texture_foreground; //noisemap

in vec2 pass_TexCoord; //this is the texture coord
in vec4 pass_Color;
out vec4 color;

uniform int texture_blend;

void main(void)                                                   
{
    vec2 noiseVec;
    
    noiseVec = normalize(texture(texture_foreground,pass_TexCoord).xy);
    
    noiseVec = (noiseVec * 2.0 - 1) * .05;

    color = texture(texture_background, pass_TexCoord + noiseVec);
}