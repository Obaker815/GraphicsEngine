#version 460 core

in vec2 vUV;

out vec4 FragColor;

uniform sampler2D uTexture;

void main()
{
    FragColor = texture(uTexture, vUV);
    //FragColor = vec4(vUV.xy, 0.0, 1.0);
}
