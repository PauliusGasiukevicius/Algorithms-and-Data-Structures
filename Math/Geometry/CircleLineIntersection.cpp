//Finds intersection of circle at point (0,0) to line a*x + b*y + c = 0
//Returns (possibly empty) vector of intersection points
vector<array<ld,2>> CircleLineIntersection(ld r, ld a, ld b, ld c){
    ld EPS = 1e-7;
    ld x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);
    if (c*c > r*r*(a*a+b*b)+EPS)return {};
    if (fabs (c*c - r*r*(a*a+b*b)) < EPS) return {{x0,y0}};

        ld d = r*r - c*c/(a*a+b*b);
        ld mult = sqrt (d / (a*a+b*b));
        ld ax, ay, bx, by;
        ax = x0 + b * mult;
        bx = x0 - b * mult;
        ay = y0 - a * mult;
        by = y0 + a * mult;

    return {{ax,ay},{bx,by}};
}
