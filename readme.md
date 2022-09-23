    bool Sphere::intersect(Intersection& intersection)
    {
    // Transform ray so we can consider origin-centred sphere
    Ray localRay = intersection.ray;
    localRay.origin -= centre;
    
        // Calculate quadratic coefficients
        float a = localRay.direction.length2();
        float b = 2 * dot(localRay.direction, localRay.origin);
        float c = localRay.origin.length2() - sqr(radius);
    
        // Check whether we intersect
        float discriminant = sqr(b) - 4 * a * c;
    
        if (discriminant < 0.0f)
        {
            return false;
        }
    
        // Find two points of intersection, t1 close and t2 far
        float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
    
        // First check if close intersection is valid
        if (t1 > RAY_T_MIN && t1 < intersection.t)
        {
            intersection.t = t1;
        }
        else if (t2 > RAY_T_MIN && t2 < intersection.t)
        {
            intersection.t = t2;
        }
        else
        {
            // Neither is valid
            return false;
        }
    
        // Finish populating intersection
        intersection.pShape = this;
        intersection.color = color;
    
        return true;
    }