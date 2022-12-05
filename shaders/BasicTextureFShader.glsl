#version 330

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform bool invert = false;

void main() {
    if(invert){
        FragColor = vec4(1,1,1,2) - texture(ourTexture, TexCoord);
    }else {
        FragColor = texture(ourTexture, TexCoord);
    }
}
