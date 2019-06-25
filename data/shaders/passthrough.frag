uniform sampler2D tex;
uniform int width;
uniform int height;
uniform int srgb;

out vec4 FragColor;

void main()
{
    vec2 uv = gl_FragCoord.xy / vec2(width, height);
    if (srgb > 0)
		FragColor = pow(texture(tex, uv), vec4(1./2.2));
	else
		FragColor = texture(tex, uv);
}
