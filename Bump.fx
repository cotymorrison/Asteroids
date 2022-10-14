
#define LIGHT_FALLOFF 250.0f

float4x4  ModelWorld;
float4x4  ModelView;
float4x4  ModelViewProj;
float4    vLight;
float4    vEye;
float4    vDiffuseMaterial;
float4    vSpecularMaterial;
float4    vAmbient;
float     power;

texture MeshTexture;
texture BumpTexture;

//--------------------------------------------------------------------------------------
// Texture samplers
//--------------------------------------------------------------------------------------
sampler MeshTextureSampler = 
sampler_state
{
    Texture = <MeshTexture>;
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
};

sampler BumpTextureSampler = 
sampler_state
{
    Texture = <BumpTexture>;
    MipFilter = Linear;
    MinFilter = Linear;
    MagFilter = Linear;
};


struct a2v {
    float4 Position : POSITION;
    float2 Texcoord : TEXCOORD0;
    float4 Normal   : NORMAL;
};

struct v2p {
    float4 Position  : POSITION;
    float4 Color     : COLOR0;
	float4 ViewPos	 : TEXCOORD0;
    float3 ViewNorm	 : TEXCOORD1;
    float2 Texcoord  : TEXCOORD2;
};

struct p2f {
    float4 Color : COLOR0;
};


void RenderSceneVS( in a2v IN, out v2p OUT )
{
    OUT.Position = mul(IN.Position, ModelViewProj);
	OUT.ViewPos = mul(IN.Position, ModelViewProj);

    float4 normal = mul(float4(IN.Normal.xyz,0.0),ModelViewProj);
	normal = normalize(normal);

	OUT.ViewNorm = normal;

    OUT.Color = 0.5 * vAmbient;

    OUT.Texcoord = IN.Texcoord;
}

void RenderScenePS( in v2p IN, out p2f OUT )
{
    float4 Color = tex2D(MeshTextureSampler, IN.Texcoord);
    //float4 Normal = tex2D(BumpTextureSampler, IN.Texcoord);

    float4 light = normalize(vLight-IN.ViewPos);
    float4 eye = normalize(vEye-IN.ViewPos);
    float4 vhalf = normalize(eye+vLight);

    float diffuse = dot(IN.ViewNorm, light);
    float specular = dot(IN.ViewNorm, vhalf);
    specular = pow(specular, power);

    float3 L = vLight - IN.ViewPos;
	float3 l = normalize( L );
    float LenSq = dot( L, l );

    OUT.Color = Color*(diffuse*vDiffuseMaterial + specular*vSpecularMaterial + IN.Color);// * LIGHT_FALLOFF  / LenSq;
}


technique RenderScene
{
    pass P0
    {
        VertexShader = compile vs_2_0 RenderSceneVS(  );
        PixelShader  = compile ps_2_0 RenderScenePS(  );
    }
}