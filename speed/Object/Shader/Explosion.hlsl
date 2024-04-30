#include"./Pixel/PixelShader2DHeader.hlsli"

cbuffer cbParam : register(b4)
{
    float4 g_color_;
}

float4 main(PS_INPUT PSInput) : SV_TARGET
{
	//UV���W�ƃe�N�X�`�����Q�Ƃ��āA�œK�ȐF���擾����
    float4 srcCol = tex.Sample(texSampler, PSInput.uv);
	//�A���t�@�e�X�g�`�悵�Ȃ�
    if (srcCol.a < 0.01f)
    {
        discard;
    }
	//float gray = dot(srcCol.rgb, float3(0.299, 0.587, 0.114));
    float gray = (srcCol.r + srcCol.g + srcCol.b) / 3.0f;
    return gray;
}