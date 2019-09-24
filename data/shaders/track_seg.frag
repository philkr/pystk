uniform usampler2D tex;
uniform uint background_label, track_label;

in vec2 uv;
layout(location = 3) out uint o_label;

void main(void)
{
	uint l = texelFetch(tex, ivec2(gl_FragCoord.xy), 0).x;
	if ((l>>24) == background_label)
		l = ((l<<8)>>8) | (track_label<<24);
	o_label = l;
}
