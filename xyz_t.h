
struct xyz_t
{
    float x;
    float y;
    float z;

    void operator+=(xyz_t other) {
        this->x += other.x;
        this->y += other.y;
        this->z += other.z;
    }

    xyz_t(float x, float y, float z)
    : x(x), y(y), z(z)
    {}
};