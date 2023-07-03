struct Input
{
    float4 Pos : POSITION;
    float4 UV : TEXCOORD;
};

struct OutPut
{
    // 레스터라이저야 이 포지션이
    // w나눈 다음  뷰포트 곱하고 픽셀 건져낼때 쓸포지션 정보를 내가 보낸거야.
    float4 Pos : SV_Position;
    float4 UV : TEXCOORD;
};

OutPut FireWork_VS(Input _Value)
{
    OutPut OutPutValue = (OutPut) 0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;
    
    // 화면 전체 범위
    return OutPutValue;
}


cbuffer FireWorkData : register(b1)
{
    // 상수버퍼는 
    float4 Time;
    float4 ScreenSize;
    float4 Mouse;
}


Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 FireWork_PS(OutPut _Value) : SV_Target0
{
    float4 Color = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);

    float2 uv = _Value.UV.xy;

    return Color;
}
/// <summary>
/// test
/// </summary>

float3 glow(float2 p, float2 lpos)
{
    float2 q = p - lpos;
    float atten = 1. / dot(q, q);
    //atten *= (1. + atten*1e-4); // Make the inside slightly sharper

    return float3(1.0,0.f,0.f)* atten;
}



////////////////


float rand(float2 co) 
{
    return frac(sin(dot(co.xy, float2(12.9898f, 78.233f))) * 43758.5453f);
}

/*
float rand(float v){
    return fract(sin(12.9898*v)*43758.5453);
}
*/

float rand(float p)
{
    // Hash function by Dave Hoskins
    p = frac(p * .1031);
    p *= p + 33.33;
    p *= p + p;
    return frac(p);
}


float3 lastExplosion(float time)
{
    // vec3(time since last explosion,
    //      index of last explosion,
    //      time until next explosion)
    float t = fmod(time, 10.f);
    float interval = floor(time / 10.);
    float t0max = 0., imax = -1.;
    float t0next = 10.;
    for (float i = 0.; i < 10.; i++)
    {
        float t0 = rand(float2(interval, i)) * 10.;
        if (t > t0 && t0 > t0max)
        {
            t0max = t0;
            imax = i;
        }
        if (t < t0 && t0 < t0next)
        {
            t0next = t0;
        }
    }
    return float3(t - t0max, 10. * interval + imax, t0next - t);
}



void mainImage(out float4 fragColor, in float2 fragCoord)
{
    float2 uv = fragCoord.xy;
    float2 p = (2. * fragCoord - ScreenSize.xy) / ScreenSize.y;

    float3 col = float3(0.f, 0.f, 0.f);

    float3 lastExpl = lastExplosion(Time.x);
    float t = lastExpl.x;
    float explNum = lastExpl.y;
    float tFadeout = lastExpl.z;

    // Fireworks base color
    float3 baseCol = float3(0.5f, 0.5f, 0.5f) + 0.4f * sin(float3(1.f,0.f,0.f) * explNum + float3(0.f, 2.1f, -2.1f));

    // Number of particles
    float N_LIGHTS = 100.;
    for (float i = 0.; i < N_LIGHTS; i++)
    {

        // Generate points uniformly on hemisphere
        // (see Total Compendium eq. (34))
        float f = i / N_LIGHTS;
        float r = sqrt(1. - f * f);
        float th = 2. * 0.618033 * 3.14159 * i; // Use Golden Ratio for a quasirandom sequence
        float hash = sin(explNum + i * 85412.243);
        float weight = (1. - 0.2 * hash);
        th += hash * 3. * 6.28 / N_LIGHTS;
        // Only take x and y coordinates
        float2 lpos = float2(cos(th), sin(th)) * r;
        // Add some physics
        lpos.xy *= (1. - exp(-3. * t / weight)) * weight; // explosion, easing out
        lpos.y += t * 0.3 * weight - t * (1. - exp(-t * weight)) * 0.6 * weight; // vertical free-fall motion
        float intensity = 2e-4;
        intensity *= exp(-2. * t); // Fade out with time
        intensity *= (1. - 0.5 * hash); // Randomize per particle
        intensity *= (1. + 10. * exp(-20. * t)); // Intensity burst at explosion
        intensity *= clamp(3. * tFadeout, 0., 1.); // Fade out before next explosion
        col += glow(p, lpos) * intensity * baseCol;
    }


    col = max(col, 0.);
    //col = 1.-exp(-col); // Tone mapping
    col = (col * (2.51 * col + 0.03)) / (col * (2.43 * col + 0.59) + 0.14); // Tone mapping
    //col = col/(1.+col);
    col = sqrt(col); // gamma correction

    fragColor = float4(col, 1.0);
}