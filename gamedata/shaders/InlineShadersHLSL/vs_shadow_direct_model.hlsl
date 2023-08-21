//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

#include "Headers\h_common.hlsl"
#include "Headers\h_skin.hlsl"

//////////////////////////////////////////////////////////////////////////////////////////
// Vertex
v2p_shadow_direct _main( v_model	I )
{
	v2p_shadow_direct	O ;
	float4 	hpos 	= mul( m_WVP, I.P );

	O.hpos 			= hpos;

 	return			O ;
}

/////////////////////////////////////////////////////////////////////////
#ifdef 	SKIN_NONE
v2p_shadow_direct 	main(v_model v) 			{ return _main(v); }
#endif

#ifdef 	SKIN_0
v2p_shadow_direct 	main(v_model_skinned_0 v) 	{ return _main(skinning_0(v)); }
#endif

#ifdef	SKIN_1
v2p_shadow_direct 	main(v_model_skinned_1 v) 	{ return _main(skinning_1(v)); }
#endif

#ifdef	SKIN_2
v2p_shadow_direct 	main(v_model_skinned_2 v) 	{ return _main(skinning_2(v)); }
#endif

#ifdef	SKIN_3
v2p_shadow_direct 	main(v_model_skinned_3 v) 	{ return _main(skinning_3(v)); }
#endif

#ifdef	SKIN_4
v2p_shadow_direct 	main(v_model_skinned_4 v) 	{ return _main(skinning_4(v)); }
#endif

FXVS;
