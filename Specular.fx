float4x4 ModelViewProj;
float4x4 ModelViewIT;
float4 LightVec;

texture MeshTexture;


//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler MeshTextureSampler = 
sampler_state
{
    Texture = <MeshTexture>;
    MipFilter = LINEAR;
    MinFilter = LINEAR;
    MagFilter = LINEAR;
};

//--------------------------------------------------------------------------------------
// Application to Vertex Shader
//--------------------------------------------------------------------------------------
struct a2v {
    float4 Position		: POSITION;
	float2 TextureUV	: TEXCOORD0;
    float4 Normal		: NORMAL;
};

//--------------------------------------------------------------------------------------
// Vertex Shader to Pixel Shader
//--------------------------------------------------------------------------------------
struct v2p {
    float4 Position		: POSITION;
	float2 TextureUV	: TEXCOORD0;
    float4 Color		: COLOR0;
};


//--------------------------------------------------------------------------------------
// Vertex shader output structure
//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
    float4 Position   : POSITION;   // vertex position 
    float4 Specular   : COLOR0;     // vertex specular color
    float2 TextureUV  : TEXCOORD0;  // vertex texture coords 
};


//--------------------------------------------------------------------------------------
// This shader computes standard transform and lighting
//--------------------------------------------------------------------------------------
v2p RenderSceneVS( in a2v IN )
{
	v2p OUT;
    float4 pos = mul(IN.Position, ModelViewProj);
	OUT.Position = pos;

    float4 normal = mul(IN.Normal, ModelViewIT);
    normal.w = 0.0;
    normal = normalize(normal);
    float4 light = normalize(LightVec);
    float4 eye = normalize(float4(20.0, 0.0, -5.0, 0.0));
    float4 vhalf = normalize(light + eye);

    float diffuse = dot(normal, light);
    float specular = dot(normal, vhalf);
    specular = pow(specular, 32);

    float4 diffuseMaterial = float4(0.5, 0.5, 1.0, 1.0);
    float4 specularMaterial = float4(0.5, 0.5, 1.0, 1.0);

    OUT.Color = diffuse*diffuseMaterial + specular*specularMaterial;
	
	OUT.TextureUV = IN.TextureUV;

	return OUT;
}

//--------------------------------------------------------------------------------------
// Pixel shader output structure
//--------------------------------------------------------------------------------------
struct PS_OUTPUT
{
    float4 RGBColor : COLOR0;  // Pixel color    
};

//--------------------------------------------------------------------------------------
// This shader outputs the pixel's color by modulating the texture's
//       color with diffuse material color
//--------------------------------------------------------------------------------------
PS_OUTPUT RenderScenePS( v2p In ) 
{ 
    PS_OUTPUT Output;

	Output.RGBColor = tex2D(MeshTextureSampler, In.TextureUV) * In.Color;

    //Output.RGBColor = In.Color;

    return Output;
}


technique RenderScene
{
    pass P0
    {
        VertexShader = compile vs_2_0 RenderSceneVS(  );
        PixelShader  = compile ps_2_0 RenderScenePS(  ); // trivial pixel shader (could use FF instead if desired)
    }
}