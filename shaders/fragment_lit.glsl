#version 460 core

uniform struct Light {
    float intensity;
    vec3 position;
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
} _Light;

uniform struct Material {
    vec3 color;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
} _Material; 

in vec3 FragPositionInWorld;
in vec3 Normal;

out vec4 FragColor;
uniform vec3 _ViewerPosition = vec3(0.0f);


void main()
{
    vec3 viewDirection = normalize(_ViewerPosition - FragPositionInWorld);
    vec3 lightDirection = _Light.position - FragPositionInWorld;
    float lightDistance = pow(length(lightDirection), 2);
    lightDirection = normalize(lightDirection);

    // Ambient light value = material ambient value * light ambient color * light color
    vec3 ambientLight = _Material.ambient * _Light.ambient * _Light.color;

    // Diffuse light value = material diffuse value * lambertian * light diffuse color * light color
    vec3 diffuseLight = _Material.diffuse * max(dot(Normal, lightDirection), 0.0) * _Light.diffuse * _Light.color;

    // PHONG
    // Reflect Direction = normalize(reflect(-lightDirection, Normal))
    // Specular Angle =  max(dot(viewDirection, {Reflect Direction} ), 0.0)
    // Specular Light = pow(Specular Angle, Material Shininess) * Material Specular Value * Light Specular Color * Light Color
    //vec3 specularLight = (pow(max(dot(viewDirection, normalize(reflect(-lightDirection, Normal))), 0.0), _Material.shininess) * _Material.specular * _Light.specular * _Light.color);

    // BLINN-PHONG
    // Half Direction = normalize(lightDirection + viewDirection)
    // Specular Angle = max(dot( {Half Direction} , Normal), 0.0)
    // Specular Light = pow( {Specular Angle} , Material Shininess) * Material Specular Value * Light Specular Color * Light Color
    vec3 specularLight = pow(max(dot(normalize(lightDirection + viewDirection), Normal), 0.0), _Material.shininess) * _Material.specular * _Light.specular * _Light.color;

    // POINT LIGHT
    //diffuseLight *= _Light.intensity / lightDistance;
    //specularLight *= _Light.intensity / lightDistance;

    FragColor = vec4((ambientLight + diffuseLight + specularLight) * _Material.color, 1.0);
}