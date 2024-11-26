#version 330 core

in vec2 pass_Position;
out vec4 o_Color;

vec2 iSqr(vec2 z) { 
    return vec2((z.x * z.x) - (z.y * z.y), 2 * z.x * z.y);
}

vec3 colorFunc(int iter) { 
    vec3 color = vec3(0.4 + 0.012 * iter, 1.0, 0.2 + 0.4 * (1.0 + sin(0.3 * iter)));
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 m = abs(fract(color.xxx + K.xyz) * 6.0 - K.www);
    return vec3(color.z * mix(K.xxx, clamp(m - K.xxx, 0.0, 1.0), color.y));
}
 
void main() 
{
    vec2 c, z;
    c = vec2(pass_Position.x - 0.5, pass_Position.y);
    z = c;

    int i; 
    vec3 color = vec3(0.0, 0.0, 0.0);
    vec2 res;
    for (int i = 0; i < 10; i++) { 
        res = iSqr(z) + c;
        if (length(res) > 4.0) {
            color = colorFunc(i);
            break;
        }
        z = res;
    }

    o_Color = vec4(color, 1.0);
}
