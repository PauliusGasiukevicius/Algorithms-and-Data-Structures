#define ld long double

ld dist(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

/*
To find points of intersection:
1) Lets move first cirlce to origin (will need to move output points in reverse too)
2) Now first circle equation is x*x + y*y = r1*r1
3) second circle is: (x-x2)^2 + (y-y2)^2 = r2*r2
4) We can merge them to get: x*(-2*x2) + y*(-2*y2) + (x2^2 + y2^2 + r1^2 - r2^2) = 0
5) Now problem is reduced to finding Circle Line Intersection
*/

ld CircleCircleIntersectionArea(ld x1,ld y1,ld r1,ld x2,ld y2,ld r2)
{
    ld D = dist(x1,y1,x2,y2);
    ld PI = atan(1)*4;
    if(r1+r2 < D)return 0; //no intersection
    if(D+r1 <= r2)return PI*r1*r1; //smaller circle inside bigger one
    ld angle1 = 2.0 * acos((D * D + r1 * r1 - r2 * r2) / (2 * D * r1));
	ld angle2 = 2.0 * acos((D * D + r2 * r2 - r1 * r1) / (2 * D * r2));
	return 0.5 * (r1 * r1 * (angle1 - sin(angle1)) + r2 * r2 * (angle2 - sin(angle2)));
}
