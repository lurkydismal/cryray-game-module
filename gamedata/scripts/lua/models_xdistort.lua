--' //////////////////////////////////////////////////////////////////////////
--' //-' CryRay Engine x64 Shaders
--' //-' Based on shaders from the original Anomaly 1.5.1
--' //-' As well as an integrated shader pack Screen Space 15.4
--' //-' Repository with shaders: https://github.com/cryray-team
--' //-' Also, if you are a shader developer
--' //-' You can join our server in discord: https://discord.gg/R78uVUZCTR
--' //-' OldSerpskiStalker7777, CryRay Team
--' //////////////////////////////////////////////////////////////////////////

function normal    (shader, t_base, t_second, t_detail)
  shader:begin  ("model_distort","particle_alphaonly")    -- particle_alphaonly
      : sorting (3, false)
      : blend   (true,blend.srcalpha,blend.invsrcalpha)
      : aref    (true,0)
      : zb     	(true,false)
      : fog    	(false)
      : distort (true)
--  shader:sampler("s_base")      :texture  (t_base)
	shader: dx10texture ("s_base", t_base)
	shader: dx10sampler ("smp_base")
end

function l_special  (shader, t_base, t_second, t_detail)
  shader:begin  	("model_distort","particle_distort")
      : sorting  	(3, false)
      : blend    	(true,blend.srccolor,blend.invsrcalpha)
      : zb     		(true,false)
      : fog    		(false)
      : distort   	(true)
--  shader:sampler  ("s_base")      :texture  (t_base)
--  shader:sampler  ("s_distort")   :texture  (t_base)  -- "pfx\\pfx_distortion"
	shader: dx10texture ("s_base", t_base)
	shader: dx10texture ("s_distort", t_base)
	shader: dx10sampler ("smp_linear")
end
