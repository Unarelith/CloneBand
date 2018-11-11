#version 120

varying vec4 v_color;
varying vec2 v_texCoord;

uniform sampler2D u_tex;

void main() {
	vec4 color = v_color;

	if (v_texCoord.x != -1 && v_texCoord.y != -1) {
		vec4 texColor = texture2D(u_tex, v_texCoord);
		color = vec4(texColor.rgb - (1 - color.rgb), min(texColor.a, color.a));
	}

	if (color.a < 0.3) discard;

	gl_FragColor = color;
}

