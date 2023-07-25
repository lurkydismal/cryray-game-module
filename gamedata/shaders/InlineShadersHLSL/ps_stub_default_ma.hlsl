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

//Texture2D s_base;
//sampler smp_base;

//////////////////////////////////////////////////////////////////////////////////////////
// Pixel

float4 main ( p_TL I ) : SV_Target
{
	float4 res = s_base.Sample( smp_base, I.Tex0 );
//	res.rgb		= lerp( I.Color.rgb, res.rgb, I.Color.a);
	res.rgb		= lerp( res.rgb, I.Color.rgb, I.Color.a);
	res.a		*= I.Color.a;

//	clip(res-m_AlphaRef);
//	clip(res-0.5);

	return res;
//	return float4(1,1,1,1);
}
