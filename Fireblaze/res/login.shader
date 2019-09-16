#type vertex
#version 430 core

layout(location = 0) in vec3 in_Position;
layout(location = 2) in vec2 in_TexCoord;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

uniform mat3 u_TexTransform;

out vec2 v_TexCoord;

void main()
{
	gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(in_Position, 1.0);
	v_TexCoord = (u_TexTransform * vec3(in_TexCoord, 1.0)).xy;	
}

#link [Type=Renderer, Name="u_ModelMatrix", Link="ModelMatrix"]
#link [Type=Renderer, Name="u_ViewMatrix", Link="ViewMatrix"]
#link [Type=Renderer, Name="u_ProjectionMatrix", Link="ProjectionMatrix"]
#link [Type=User, Name="u_TexTransform", Link="Transform"]

#type fragment
#version 430 core

layout(location = 0) out vec4 FragColor;

uniform sampler2D u_Texture;

in vec2 v_TexCoord;

void main()
{
	FragColor = texture(u_Texture, v_TexCoord);
}

#link [Type=User, Name="u_Texture", Link="Texture"]