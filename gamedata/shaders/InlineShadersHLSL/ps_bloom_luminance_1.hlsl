//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#include "Headers\common.h"

//////////////////////////////////////////////////////////////////////////////////////////
#define	LUMINANCE_BASE		0.0001h

float	luminance	(float2	tc)	
{
	float3	source 	= s_image.Sample( smp_rtlinear, tc );
	return 	dot( source, LUMINANCE_VECTOR*def_hdr );
}

//////////////////////////////////////////////////////////////////////////////////////////
// 	perform 2x2=4s convolution, working on 4x4=16p area
//	that means 256x256 source will be scaled to (256/4)x(256/4) = 64x64p
//	a):	256x256 => 64x64p	with log 
//	b):	64x64p	=> 8x8p
//	c):	8x8p	=> 1x1p		with exp
float4 main( p_build I ) : SV_Target
{
	// first 8 bilinear samples (8x4 = 32 pixels)
	float4 	final;
	final.x = luminance(I.Tex0);
	final.y = luminance(I.Tex1);
	final.z = luminance(I.Tex2);
	final.w = luminance(I.Tex3);

	// OK
	return final;
}
