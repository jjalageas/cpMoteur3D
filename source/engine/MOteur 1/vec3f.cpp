#include "vec3f.h"

#define M_2PI 6.28318530717958705692

Vec3f Vec3f::MultMatrix(GLfloat par_pd_matrix[4][4])
{
    Vec3f loc_r_res;
    loc_r_res.setX(par_pd_matrix[0][0] * v[0] + par_pd_matrix[0][1] * v[1] + par_pd_matrix[0][2] * v[2]);
    loc_r_res.setY(par_pd_matrix[1][0] * v[0] + par_pd_matrix[1][1] * v[1] + par_pd_matrix[1][2] * v[2]);
    loc_r_res.setZ(par_pd_matrix[2][0] * v[0] + par_pd_matrix[2][1] * v[1] + par_pd_matrix[2][2] * v[2]);
    return loc_r_res;
}

Vec3f Vec3f::RotationMatrix(Vec3f _angle)
{
    Vec3f loc_r_res(*this), loc_r_tmp;

    _angle = _angle * M_2PI / 360.;

    if (fmod(_angle[0], M_2PI) != 0.)
    {
        loc_r_tmp.setX(loc_r_res[0]);
        loc_r_tmp.setY(cos(_angle[0]) * loc_r_res[1] - sin(_angle[0]) * loc_r_res[2]);
        loc_r_tmp.setZ(sin(_angle[0]) * loc_r_res[1] + cos(_angle[0]) * loc_r_res[2]);
        loc_r_res = loc_r_tmp;
    }
    if (fmod(_angle[1], M_2PI) != 0.)
    {
        loc_r_tmp.setX(cos(_angle[1]) * loc_r_res[0] + sin(_angle[1]) * loc_r_res[2]);
        loc_r_tmp.setY(loc_r_res[1]);
        loc_r_tmp.setZ(-sin(_angle[1]) * loc_r_res[0] + cos(_angle[1]) * loc_r_res[2]);
        loc_r_res = loc_r_tmp;
    }
    if (fmod(_angle[2], M_2PI) != 0.)
    {
        loc_r_tmp.setX(cos(_angle[2]) * loc_r_res[0] - sin(_angle[2]) * loc_r_res[1]);
        loc_r_tmp.setY(sin(_angle[2]) * loc_r_res[0] + cos(_angle[2]) * loc_r_res[1]);
        loc_r_tmp.setZ(loc_r_res[2]);
        loc_r_res = loc_r_tmp;
    }
    return loc_r_res;
}

Vec3f Abs(const Vec3f &_vec3f)
{
    Vec3f loc_r_res(fabs(_vec3f[0]), fabs(_vec3f[1]), fabs(_vec3f[2]));
    return loc_r_res;
}
