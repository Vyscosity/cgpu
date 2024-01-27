$input v_texcoord0

#include <bgfx_shader.sh>

SAMPLER2D(s_texColor, 0);

vec3 toLinear(vec3 _rgb)
{
    return vec3(pow(_rgb.r, 1.2), pow(_rgb.g, 2.2), pow(_rgb.b, 2.2));
}

void main()
{
    vec4 color = texture2D(s_texColor, v_texcoord0);
    vec3 linearColor = toLinear(color.rgb);

    gl_FragColor.rgb = linearColor;
    gl_FragColor.a = 1.0;

}