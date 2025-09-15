export module gfx.canvas;

import gfx.types;
import gfx.vec;
import std;

namespace gfx {
export class canvas {
public:
    canvas(i32 width, i32 height)
        : m_width(width)
        , m_height(height)
        , m_data(new vec3[width * height]())
    {
    }

    canvas(canvas const& other)
        : m_width(other.width())
        , m_height(other.height())
        , m_data(new vec3[other.width() * other.height()])
    {
        std::copy(other.begin(), other.end(), begin());
    }

    canvas(canvas&& other)
        : m_width(other.width())
        , m_height(other.height())
        , m_data(other.m_data)
    {
        other.m_data = nullptr;
    }

    canvas& operator=(canvas const&) = delete;

    canvas& operator=(canvas&&) = delete;

    ~canvas()
    {
        delete[] m_data;
    }

    vec3& operator[](ivec2 xy)
    {
        return operator[](xy.x, xy.y);
    }

    vec3 const& operator[](ivec2 xy) const
    {
        return operator[](xy.x, xy.y);
    }

    vec3& operator[](int col, int row)
    {
        if (col < 0 || col >= m_width || row < 0 || row >= m_height) {
            return dummy_pixel;
        }
        return m_data[row * m_width + col];
    }

    vec3 const& operator[](int col, int row) const
    {
        if (col < 0 || col >= m_width || row < 0 || row >= m_height) {
            return dummy_pixel;
        }
        return m_data[row * m_width + col];
    }

    int width() const { return m_width; }
    int height() const { return m_height; }
    int size() const { return m_width * m_height; }
    vec3* begin() { return m_data; }
    vec3 const* begin() const { return m_data; }
    vec3* end() { return m_data + size(); }
    vec3 const* end() const { return m_data + size(); }

private:
    i32 m_width;
    i32 m_height;
    vec3* m_data;
    static vec3 dummy_pixel;
};

vec3 canvas::dummy_pixel = vec3();

u8 to_u8(f32 x)
{
    if (x <= 0.0f)
        return 0;
    if (x >= 1.0f)
        return 255;
    return x * 255.0f + 0.5f;
}

export void write_ppm(canvas const& canvas, std::ostream& os)
{
    os << "P6\n"
       << canvas.width() << " " << canvas.height() << "\n"
       << 255 << "\n";

    for (auto const& pixel : canvas)
        os << to_u8(pixel.r)
           << to_u8(pixel.g)
           << to_u8(pixel.b);
}

export void write_ppm(canvas const& canvas, std::string const& file_path)
{
    std::ofstream os(file_path, std::ios::binary);
    write_ppm(canvas, os);
}
} // namespace gfx
