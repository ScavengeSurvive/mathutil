// built-in include guard removal
// just in case the user has a local dependency with the same file name
#if defined _inc_mathutil
	#undef _inc_mathutil
#endif
// custom include-guard to ensure we don't duplicate
#if defined _mathutil_included
	#endinput
#endif
#define _mathutil_included

#include <a_samp>

// Truncates a value to the range 0.0 - 360.0
stock Float:GetAbsoluteAngle(Float:angle) {
	// Note that 360 is equal to 0
	return ((angle / 360.0) - floatround((angle / 360.0), floatround_floor)) * 360.0;
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

// Returns the distance between two points in 2D space
stock Float:GetDistance2D(Float:x1, Float:y1, Float:x2, Float:y2) {
	return floatsqroot(
		((x1 - x2) * (x1 - x2)) +
		((y1 - y2) * (y1 - y2))
	);
}

// Distance from any point on a projected line to a point
stock Float:GetDistancePointLine(
	Float:line_x, Float:line_y, Float:line_z,
	Float:vector_x, Float:vector_y, Float:vector_z,
	Float:point_x, Float:point_y, Float:point_z
) {
	return (
		floatsqroot(
			floatpower((vector_y) * ((point_z) - (line_z)) - (vector_z) * ((point_y) - (line_y)), 2.0) +
			floatpower((vector_z) * ((point_x) - (line_x)) - (vector_x) * ((point_z) - (line_z)), 2.0) +
			floatpower((vector_x) * ((point_y) - (line_y)) - (vector_y) * ((point_x) - (line_x)), 2.0)
		) /
		floatsqroot((vector_x) * (vector_x) + (vector_y) * (vector_y) + (vector_z) * (vector_z))
	);
}

// 2D Projection position based on distance and angle
stock GetXYFromAngle(&Float:x, &Float:y, Float:a, Float:distance) {
	x += (distance*floatsin(-a,degrees));
	y += (distance*floatcos(-a,degrees));
}

// 3D Projection position based on distance and angles
stock GetXYZFromAngle(&Float:x, &Float:y, &Float:z, Float:angle, Float:elevation, Float:distance) {
	x += distance * floatsin(angle, degrees) * floatcos(elevation, degrees);
	y += distance * floatcos(angle, degrees) * floatcos(elevation, degrees);
	z += distance * floatsin(elevation, degrees);
}

// Convert 3D velocity vectors to a single velocity unit (close to Km/h in SA:MP)
stock Float:CalculateVelocity(Float:x, Float:y, Float:z) {
	return floatsqroot((x * x) + (y * y) + (z * z)) * 150.0;
}

// Return a floating point random number
stock Float:frandom(Float:max, Float:min = 0.0, decimalPlaces = 4) {
	new
		Float:multiplier = floatpower(10.0, decimalPlaces),
		minRounded = floatround(min * multiplier),
		maxRounded = floatround(max * multiplier);
	return float(random(maxRounded - minRounded) + minRounded) / multiplier;
}

// Checks if one angle is within range of another angle
stock AngleInRangeOfAngle(Float:a1, Float:a2, Float:range) {
	a1 -= a2;
	return (a1 < range) && (a1 > -range);

}

// Returns the absolute value of an integer
stock abs(int) {
	if(int < 0) {
		return -int;
	}
	return int;
}

// Picks <sizeof(output)> numbers from a list ranging from 0 to <max>
stock PickFromList(max, count, output[]) {
	new
		idx,
		picked[256];

	if(max > 256) {
		return 1;
	}

	while(idx < count) {
		output[idx] = random(max);

		if(picked[output[idx]] == 0) {
			picked[output[idx]] = 1;
			idx++;
		}
	}

	return 0;
}

// Checks if a variable is not a number
#if !defined IsNaN
	stock IsNaN(Float:number) {
		return !(number <= 0 || number > 0);
	}
#endif
