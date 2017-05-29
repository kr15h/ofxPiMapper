precision highp float;

uniform float time;

void main()
{
    // gl_FragCoord contains the window relative coordinate for the fragment.
    // we use gl_FragCoord.x position to control the red color value.
    // we use gl_FragCoord.y position to control the green color value.
    // please note that all r, g, b, a values are between 0 and 1.
    
    float windowWidth = 1024.0;
    float windowHeight = 768.0;

    float x = gl_FragCoord.x / windowWidth * 2. -.5;
    float y = gl_FragCoord.y / windowHeight * 2. - .5;
    vec2 uv = vec2(x,y);        

    uv.x *= 1.5;
    float a = atan(uv.y,uv.x)/3.14 + time/20. + 9.0;
    float r = length(uv);
    //float c1=float(r > .1),c2 = float(r < .49),c3 = float(r > .51);
    float v = 0.0;
    float p = 2.0;
    r = .2 / r + time / 4.;
    for(int i = 9;i > 0;i--)
    {
        p /= 2.;
                int m = 0;
        if (a > p)m++;
        if (r > p)m++;
        a = mod(a,p);
        r = mod(r,p);
        if (m == 1)v += p;
    }
//    gl_FragColor = vec4(mod(v*8.,1.),mod(v*4.,1.),mod(v,2.),0)*c1*c2+c3;
    gl_FragColor = vec4(mod(v*8.,1.),mod(v*4.,1.),mod(v,2.),1.);

}


