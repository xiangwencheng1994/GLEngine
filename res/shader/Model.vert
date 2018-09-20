#version 330

#ifdef DEBUG
    #pragma optimize(off)
    #pragma debug(on)
#else
    #pragma optimize(on)
    #pragma debug(off)
#endif

// uniforms
uniform mat4        MVP;

// base vertex attribute
in      vec3        _position;
in      vec3        _normal;

// instanced attribute
in      mat4		_local;
in      int         _matIndex;

// output for fragment
out VS_OUT
{
    vec3        position;
    vec3        normal;
    flat int    matIndex;
}vs;


/**
 * Make a transform matrix by compose trans,scale,rotate quaternion
 * @param t The trans
 * @param s The scale
 * @param q The quaternion
 * @return The matrix of rotate then scale, and then tanslate
 */
mat4 makeTransform(const in vec3 t, const in vec3 s, const in vec4 q)
{
    return mat4(
        s.x * (1 - 2 * q.y * q.y - 2 * q.z * q.z), s.x * (2 * q.x * q.y + 2 * q.w * q.z), s.x * (2 * q.x * q.z - 2 * q.w * q.y), 0,
        s.y * (2 * q.x * q.y - 2 * q.w * q.z), s.y * (1 - 2 * q.x * q.x - 2 * q.z * q.z), s.y * (2 * q.y * q.z + 2 * q.w * q.x), 0,
        s.z * (2 * q.x * q.z + 2 * q.w * q.y), s.z * (2 * q.y * q.z - 2 * q.w * q.x), s.z * (1 - 2 * q.x * q.x - 2 * q.y * q.y), 0,
        t.x, t.y, t.z, 1);
}


void main()
{
    //mat4 matModel   =   makeTransform(_instPos, _instScale, _instQuat);
    mat3 matNormal  =   mat3(_local);
    vec4 wpos   =   _local * vec4(_position, 1);
    
    // set out put
    vs.position = wpos.xyz / wpos.w;
    vs.normal   = matNormal * _normal;
    vs.matIndex = _matIndex;

    gl_Position = MVP * wpos;
}
