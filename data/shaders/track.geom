uniform float depth;

layout(triangles) in;
layout(triangle_strip, max_vertices = 24) out;

void main()
{
	vec4 top[3], bot[3];
	for(int i=0; i<3; i++) {
		top[i] = gl_in[i].gl_Position + vec4(0,depth,0,0);
		bot[i] = gl_in[i].gl_Position - vec4(0,depth+2,0,0);
	}
	for (int k=0; k<3; k++) {
		gl_Position = u_projection_view_matrix * top[k];
		EmitVertex();
	}
	EndPrimitive();
	
	for (int i=0; i<4; i++) {
		int k=i%3;
		gl_Position = u_projection_view_matrix * top[k];
		EmitVertex();
		gl_Position = u_projection_view_matrix * bot[k];
		EmitVertex();
	}
	EndPrimitive();
	
	for (int k=2; k>=0; k--) {
		gl_Position = u_projection_view_matrix * bot[k];
		EmitVertex();
	}
	EndPrimitive();
}
