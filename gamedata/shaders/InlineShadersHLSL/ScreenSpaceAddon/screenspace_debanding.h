//////////////////////////////////////////////////////////////////////////
//-' CryRay Engine x64 Shaders
//-' Based on shaders from the original Anomaly 1.5.1
//-' As well as an integrated shader pack Screen Space 15.4
//-' Repository with shaders: https://github.com/cryray-team
//-' Also, if you are a shader developer
//-' You can join our server in discord: https://discord.gg/R78uVUZCTR
//-' OldSerpskiStalker7777, CryRay Team
//////////////////////////////////////////////////////////////////////////

/**
 * @ Version: SCREEN SPACE SHADERS - UPDATE 12.5
 * @ Description: Debanding implementation
 * @ Modified time: 2022-11-23 15:47
 * @ Author: https://www.moddb.com/members/ascii1457
 * @ Mod: https://www.moddb.com/mods/stalker-anomaly/addons/screen-space-shaders
 */

#include "ScreenSpaceAddon\screenspace_common.h"
#include "ScreenSpaceAddon\settings_screenspace_deband.h"

// Internal vars
static const float dband_threshold = 0.039215f;

static const float2 dband_dir_Offsets[4] =
{
	float2( 1.f, 1.f),	// XOX
	float2(-1.f,-1.f),	// O0O
	float2(-1.f, 1.f),	// XOX
	float2( 1.f,-1.f)	
};

void dband_process(inout float3 color, float2 tc, float noise, float2 dir, float loop_step)
{
	// Some vars
	float3 sampled_pixel;
	float3 diff;
	float3 avg = 0.f, max_diff = 0.f;

	float pixel_factor = loop_step / G_DEBANDING_QUALITY;

	// Radius for the sample
	float radius = noise * (G_DEBANDING_RADIUS * pixel_factor * pixel_factor) * ssfx_pixel_size;

	// Sample 4 points arround the original pixel
	[unroll (4)]
	for (int taps = 0; taps <= 4; taps++)
	{
		// Sample pixel
		sampled_pixel = s_image.Sample(smp_linear, tc + radius * (dir * dband_dir_Offsets[taps])).rgb;
		
		// Add to the average
		avg += sampled_pixel;

		// Difference between original pixel and sampled pixel
		diff = abs(color - sampled_pixel);

		// From the 4 samples save the biggest difference
		max_diff = max(max_diff, diff);
	}
	 
	// Normalize average
	avg /= 4.f;

	// Difference between original pixel and average
	diff = abs(color - avg);

	// Calc how much the pixel difference is close to our threshold.
	float3 threshold = saturate((1.f - diff  / dband_threshold) * 3.f) * saturate((1.f - max_diff  / dband_threshold) * 3.f);

	// We use the original pixel or average?
	color = lerp(color, avg, threshold);
}

float3 ssfx_debanding(float3 color, float2 tc)
{
	// Noise
	float db_noise = SSFX_permute(SSFX_permute(SSFX_permute(tc.x) + tc.y) + noise(tc));

	// Get random direction [ -1 ~ 1 ]
	float2 dir = float2(cos(db_noise), sin(db_noise));

	[unroll (G_DEBANDING_QUALITY)]
	for (int loop_cnt = 1; loop_cnt <= G_DEBANDING_QUALITY; loop_cnt++)
	{
		// More variaton for each iteration
		db_noise = SSFX_permute(db_noise);

		// Process image
		dband_process(color, tc, db_noise * 0.0033f, dir, loop_cnt);
	}

	// Return result
	return color;
}