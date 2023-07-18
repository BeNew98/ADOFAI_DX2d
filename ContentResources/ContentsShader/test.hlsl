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
    OutPut OutPutValue = (OutPut)0;
    OutPutValue.Pos = _Value.Pos;
    OutPutValue.UV = _Value.UV;

    // 화면 전체 범위
    return OutPutValue;
};


cbuffer FireWorkValue : register(b1)
{
    // 상수버퍼는 
    float4 fTime;
    float4 ScreenSize;
    float4 PlusColor;
    float4 f4Dir;
};


#define ITER 100
#define MAX_DIST 1000
#define MIN_DIST 0.1
#define UP f4Dir.xyz
#define PI 3.1415926
#define GOLDEN 2.3999632
//float rand(float n) { return frac(sin(n) * 43758.5453123); }
//float rand(float2 n) {
//    return frac(sin(dot(n, float2(12.9898, 4.1414))) * 43758.5453);
//}
float rand(float n) { return frac(sin(n) * 1); }
float rand(float2 n) {
    return frac(sin(dot(n, float2(1, 1))) * 1);
}

float atan(in float y, in float x) {
    bool s = (abs(x) > abs(y));
    return lerp(PI / 2.0 - atan2(x, y), atan2(y, x), s);
}

float grow(float x) {
    return (cos(exp(-20.0 * x) * PI) * 0.5 + 0.5) * 150.0;
}

float falloff(float x) {
    return pow(x, 512.0);
}

float2x2 InverseMatrix(float2x2 _matrix)
{
    float det = _matrix._11 * _matrix._22 - _matrix._12 * _matrix._21;
    float invDet = 1.0 / det;

    float2x2 inverse;
    inverse._11 = _matrix._22 * invDet;
    inverse._12 = -_matrix._12 * invDet;
    inverse._21 = -_matrix._21 * invDet;
    inverse._22 = _matrix._11 * invDet;

    return inverse;
}


float DE(float3 pos, float3 dir, float index) {
    float rVal = 0.1f; //rand(index);
    float block = max(4.0, abs(rVal) * 10.0);//최대 폭발까지의 달성 시간
    float subTime = frac(fTime.x / block);
    float timeBlock = floor(fTime.x / block);

    float3 offset = (0);// float3((rand(timeBlock) * 2.0 - 1.0) * 300.0,
    //(rand(timeBlock + 1.0) * 2.0 - 1.0) * 100.0 - subTime * subTime * 20.0,
    //(rand(timeBlock + 2.0) * 2.0 - 1.0) * 300.0);
//추가위치 랜덤값 오프셋
    float boubleRadius = grow(subTime);

    float3 newPos = normalize(pos - offset);

    float theta = atan(newPos.x, newPos.z);
    float y = newPos.y;

    float samples = 500;//200.0 + rand(timeBlock) * 10.0; // has to be at least 29


    ////
    float2 q = float2(y, theta);

    float2 f1 = float2(1.0 - (2.0 * 8.0) / (samples - 1.0), fmod(8.0 * GOLDEN, 2.0 * PI));
    float2 f2 = float2(1.0 - (2.0 * 21.0) / (samples - 1.0), fmod(21.0 * GOLDEN, 2.0 * PI));
    float2 f3 = float2(1.0 - (2.0 * 29.0) / (samples - 1.0), fmod(29.0 * GOLDEN, 2.0 * PI));

    float2 d1 = f2 - f1;
    float2 d2 = f3 - f1;

    float2x2 m = float2x2(d1.x, d1.y, d2.x, d2.y);
    float2x2 m_inv = InverseMatrix(m);

    float2 p1 = mul(floor(mul(q, m_inv)), m);

    float2 p2 = mul(q, m_inv);
    p2.x = floor(p2.x);
    p2.y = ceil(p2.y);
    p2 = mul(p2, m);
    float2 p3 = mul(q, m_inv);
    p3.x = ceil(p3.x);
    p3.y = floor(p3.y);
    p3 = mul(p3, m);
    float2 p4 = mul(ceil(mul(q, m_inv)), m);

    float l1 = dot(p1 - q, p1 - q) + 1000.0 * float(abs(p1.x) > 1.0);
    float l2 = dot(p2 - q, p2 - q) + 1000.0 * float(abs(p2.x) > 1.0);
    float l3 = dot(p3 - q, p3 - q) + 1000.0 * float(abs(p3.x) > 1.0);
    float l4 = dot(p4 - q, p4 - q) + 1000.0 * float(abs(p4.x) > 1.0);

    float minl = min(l1, min(l2, min(l3, l4)));

    float2 res = float(minl == l1) * p1 +
        float(minl == l2) * p2 +
        float(minl == l3) * p3 +
        float(minl == l4) * p4;
    ////

    float resultY = res.x;
    float resultTheta = res.y;


    float radius = sqrt(1.0 - resultY * resultY);

    newPos.x = sin(resultTheta) * radius;
    newPos.y = resultY;
    newPos.z = cos(resultTheta) * radius;

    newPos *= boubleRadius +rand(res)* 10.0;

    return max(0.0, min(length(newPos + offset - pos) - 1.0, length(pos - offset)));
}

float3 march(float3 pos, float3 dir, float3 clr, float index) {
    float rVal = 0.1;//rand(index);
    float block = max(4.0, abs(rVal) * 10.0);
    float subTime = frac(fTime.x / block);
    float timeBlock = floor(fTime.x / block);

    float totalDist;
    float minDist = MAX_DIST;

    float maxDist = 0.0;
    float3 result = clr;

    for (int i = 0; i < ITER; i++) {
        float dist = DE(pos, dir, index);
        totalDist += dist;
        minDist = min(minDist, dist);
        maxDist = max(maxDist, dist);
        if (dist < MIN_DIST) {
            //return float3(float(i)/float(10.0));
            result = clr;
            break;
        }
        else if (totalDist > MAX_DIST) {
            result = clr * falloff(1.0 - minDist / MAX_DIST);
            break;
        }
        pos += dir * dist;
    }
    result = clr * falloff(1.0 - minDist / MAX_DIST);

    return lerp(result, (float3)0, subTime);
}

void mainImage(out float4 fragColor, in float2 fragCoord)
{

    // float2 centered = fragCoord-ScreenSize.xy / 2.0f;
    float2 centered = float2(fragCoord.x * ScreenSize.x, -fragCoord.y * ScreenSize.y) / 2.f;
    centered.x -= ScreenSize.x / 2.f / 2.f;
    centered.y += ScreenSize.y / 2.f / 2.f;
    float3 eye = float3(sin(fTime.x * 0.1) * 510, 0.0, cos(fTime.x * 0.1) * 510);
    float3 center = float3(sin(fTime.x * 0.1) * 500.0, 0.0, cos(fTime.x * 0.1) * 500.0);
    float3 dir = normalize(center - eye);
    float3 right = cross(dir, UP);

    float3 color = march(right * centered.x + UP * centered.y + eye, dir, PlusColor, 1);
    //float3 color = march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0, 0), 1.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.2, 0), 2.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 1.0, 0.0), 3.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 0.3, 1.0), 4.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.9, 0.4), 5.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.2, 0), 6.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 1.0, 0.0), 7.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.2, 0), 8.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 1.0, 0.0), 9.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 0.3, 1.0), 10.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.9, 0.4), 11.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(1, 0.2, 0), 12.0);
    //color += march(right * centered.x + UP * centered.y + eye, dir, float3(0.2, 1.0, 0.0), 13.0);


    fragColor = float4(color, 1.0);
}

Texture2D DiffuseTex : register(t0);
SamplerState WRAPSAMPLER : register(s0);

float4 FireWork_PS(OutPut _Value) : SV_Target0
{
    float2 uv = _Value.UV.xy;

    float4 Color = (float4) 0.0f;

    mainImage(Color, uv);

    float4 TexColor = DiffuseTex.Sample(WRAPSAMPLER, _Value.UV.xy);

    Color += TexColor;
    //Color = saturate(Color);

    return Color;
}
