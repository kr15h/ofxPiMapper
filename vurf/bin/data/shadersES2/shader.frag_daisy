precision highp float;  

uniform float time;

#define pi 3.141592653589793238462643383279
#define pi_inv 0.318309886183790671537767526745
#define pi2_inv 0.159154943091895335768883763372

vec2 complex_mul(vec2 factorA, vec2 factorB){
  return vec2( factorA.x*factorB.x - factorA.y*factorB.y, factorA.x*factorB.y + factorA.y*factorB.x);
}

vec2 complex_div(vec2 numerator, vec2 denominator){
   return vec2( numerator.x*denominator.x + numerator.y*denominator.y,
                numerator.y*denominator.x - numerator.x*denominator.y)/
          vec2(denominator.x*denominator.x + denominator.y*denominator.y);
}

vec2 wrap_flip(vec2 uv){
	return vec2(1.)-abs(fract(uv*.5)*2.-1.);
}
 
float border(vec2 domain, float thickness){
   vec2 uv = fract(domain-vec2(0.5));
   uv = min(uv,1.-uv)*2.;
   return clamp(max(uv.x,uv.y)-1.+thickness,0.,1.)/(thickness);
}

float circle(vec2 uv, vec2 aspect, float scale){
	return clamp( 1. - length((uv-0.5)*aspect*scale), 0., 1.);
}

float sigmoid(float x) {
	return 2./(1. + exp2(-x)) - 1.;
}

float smoothcircle(vec2 uv, vec2 center, vec2 aspect, float radius, float sharpness){
	return 0.5 - sigmoid( ( length( (uv - center) * aspect) - radius) * sharpness) * 0.5;
}

float lum(vec3 color){
	return dot(vec3(0.30, 0.59, 0.11), color);
}

vec2 spiralzoom(vec2 domain, vec2 center, float n, float spiral_factor, float zoom_factor, vec2 pos){
	vec2 uv = domain - center;
	float angle = atan(uv.y, uv.x);
	float d = length(uv);
	return vec2( angle*n*pi2_inv + log(d)*spiral_factor, -log(d)*zoom_factor) + pos;
}

vec2 mobius(vec2 domain, vec2 zero_pos, vec2 asymptote_pos){
	return complex_div( domain - zero_pos, domain - asymptote_pos);
}


vec3 gear(vec2 domain, float phase, vec2 pos){
	float angle = atan(domain.y - pos.y, domain.x - pos.x);
	float d = 0.2 + sin((angle + phase) * 10.)*0.1;
	vec3 col = smoothcircle(domain, pos, vec2(1), d, 128.)*vec3(1.);
	col = mix(col, vec3(1,0.8,0), smoothcircle(domain, pos, vec2(1), 0.05, 256.));
	return col;
}

vec3 geartile(vec2 domain, float phase){
	domain = fract(domain);

	return gear(domain, phase, vec2(+0.5));

/*	return 
		gear(domain, -phase, vec2(-0.25,0.25)) + 
		gear(domain, phase, vec2(-0.25,0.75)) + 
		gear(domain, phase, vec2(1.25,0.25)) + 
		gear(domain,- phase, vec2(1.25,0.75))  + 
		gear(domain, -phase, vec2(0.25,-0.25)) + 
		gear(domain, phase, vec2(0.75,-0.25)) + 
		gear(domain, phase, vec2(0.25,1.25)) + 
		gear(domain, -phase, vec2(0.75,1.25)) + 
		gear(domain, phase, vec2(0.25,0.25)) + 
		gear(domain, -phase, vec2(0.25,0.75)) + 
		gear(domain, -phase, vec2(0.75,0.25)) + 
		gear(domain, phase, vec2(0.75,0.75))  ; */		
}
void main()
{
	vec2 uv = gl_FragCoord.xy/vec2(512.,512.);
	uv.y = 1. - uv.y;
			
	float phase = time*0.5;
	float dist = 0.75;
	vec2 uv_bipolar = mobius(uv*vec2(1.618,1.), vec2(0.5 - dist*0.5, 0.5), vec2(0.5 + dist*0.5, 0.5));
	uv_bipolar = spiralzoom(uv_bipolar, vec2(0.), 5., -0.125*pi, 0.8, vec2(-0.125,0.125)*phase);
	uv_bipolar = vec2(-uv_bipolar.y,uv_bipolar.x); // 90° rotation 

	vec3 gear = geartile(uv_bipolar, -phase*1.);
	
//	gl_FragColor.xyz = mix( vec3(0), vec3(0.1,0.2,0.4), uv.y);		
	gl_FragColor.xyz = mix(gl_FragColor.xyz, vec3(1), gear); // blend
	gl_FragColor.w = gear.x;
}

/*
void main(){
 vec4 p=vec4(gl_FragCoord.xy/vec2(512.,512.)*2.-1.,0,1);
 gl_FragColor=p+sin(atan(p.y,p.x)*9.)*sin(p*time/2.+9./dot(p,p)+time*5.);

}
*/

