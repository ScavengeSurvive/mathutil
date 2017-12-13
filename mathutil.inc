#if defined _mathutil_included
	#endinput
#endif
#define _mathutil_included

#include <a_samp>

// Truncates a value to the range 0.0 - 360.0
stock Float:GetAbsoluteAngle(Float:angle) {
	while(angle < 0.0) {
        angle += 360.0;
    }
	while(angle > 360.0) {
        angle -= 360.0;
    }
	return angle;
}

// Returns the offset heading from north between a point and a destination
stock Float:GetAngleToPoint(Float:fPointX, Float:fPointY, Float:fDestX, Float:fDestY) {
	return GetAbsoluteAngle(-(
        90 - (
            atan2(
                (fDestY - fPointY),
                (fDestX - fPointX)
            )
        )
    ));
}

// Returns the distance between two points in 3D space
stock Float:GetDistance3D(Float:x1, Float:y1, Float:z1, Float:x2, Float:y2, Float:z2) {
	return floatsqroot(
        ((x1 - x2) * (x1 - x2)) +
        ((y1 - y2) * (y1 - y2)) +
        ((z1 - z2) * (z1 - z2))
    );
}
