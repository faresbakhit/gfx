export module raytracer.canvas;

import raytracer.types;
import raytracer.vec;
import std;

namespace raytracer {
export template<vec V>
requires(std::floating_point<typename V::scalar_type>)
class Canvas {
public:
    constexpr Canvas(i32 width, i32 height)
        : m_width(width)
        , m_height(height)
        , m_data(new V[width * height]())
    {
    }

    constexpr Canvas(Canvas const& other)
        : m_width(other.width())
        , m_height(other.height())
        , m_data(new V[other.width() * other.height()])
    {
        std::copy(other.begin(), other.end(), begin());
    }

    constexpr Canvas(Canvas&& other)
        : m_width(other.width())
        , m_height(other.height())
        , m_data(other.m_data)
    {
        other.m_data = nullptr;
    }

    Canvas& operator=(Canvas const&) = delete;

    Canvas& operator=(Canvas&&) = delete;

    constexpr ~Canvas()
    {
        delete[] m_data;
    }

    constexpr V& operator[](ivec2 xy)
    {
        return operator[](xy.x, xy.y);
    }

    constexpr V const& operator[](ivec2 xy) const
    {
        return operator[](xy.x, xy.y);
    }

    constexpr V& operator[](i32 row, i32 col)
    {
        if (col < 0 || col >= m_width || row < 0 || row >= m_height) {
            return dummy_pixel;
        }
        return m_data[row * m_width + col];
    }

    constexpr V const& operator[](i32 row, i32 col) const
    {
        if (col < 0 || col >= m_width || row < 0 || row >= m_height) {
            return dummy_pixel;
        }
        return m_data[row * m_width + col];
    }

    constexpr int width() const { return m_width; }
    constexpr int height() const { return m_height; }
    constexpr int size() const { return m_width * m_height; }
    constexpr V* begin() { return m_data; }
    constexpr V const* begin() const { return m_data; }
    constexpr V* end() { return m_data + size(); }
    constexpr V const* end() const { return m_data + size(); }

private:
    i32 m_width;
    i32 m_height;
    V* m_data;
    static V dummy_pixel;
};

template<vec V>
requires(std::floating_point<typename V::scalar_type>)
V Canvas<V>::dummy_pixel = V();

export using CanvasRGB = Canvas<vec3>;
export using CanvasRGBA = Canvas<vec4>;

u8 toU8(f32 x)
{
    if (x <= 0.0f)
        return 0;
    if (x >= 1.0f)
        return 255;
    return x * 255.0f + 0.5f;
}

u16 toU16(f32 x)
{
    if (x <= 0.0f)
        return 0;
    if (x >= 1.0f)
        return 65535;
    return x * 65535.0f + 0.5f;
}

export template<vec V>
void writePAM(Canvas<V> const& canvas, std::ostream& os)
{
    char const* depth;
    char const* tuple_type;

    if constexpr (V::size_tag == 2) {
        depth = "2";
        tuple_type = "GRAYSCALE_ALPHA";
    } else if constexpr (V::size_tag == 3) {
        depth = "3";
        tuple_type = "RGB";
    } else if constexpr (V::size_tag == 4) {
        depth = "4";
        tuple_type = "RGB_ALPHA";
    }

    os << "P7\n"
       << "WIDTH " << canvas.width() << "\n"
       << "HEIGHT " << canvas.height() << "\n"
       << "DEPTH " << depth << "\n"
       << "MAXVAL 65535" << "\n"
       << "TUPLTYPE " << tuple_type << "\n"
       << "ENDHDR" << "\n";

    for (V const& pixel : canvas) {
        auto raster_pixel = map(pixel, toU16);
        if constexpr (V::size_tag == 2) {
            os << u8(raster_pixel.x >> 8) << u8(raster_pixel.x)
               << u8(raster_pixel.y >> 8) << u8(raster_pixel.y);
        } else if constexpr (V::size_tag == 3) {
            os << u8(raster_pixel.r >> 8) << u8(raster_pixel.r)
               << u8(raster_pixel.g >> 8) << u8(raster_pixel.g)
               << u8(raster_pixel.b >> 8) << u8(raster_pixel.b);
        } else if constexpr (V::size_tag == 4) {
            os << u8(raster_pixel.r >> 8) << u8(raster_pixel.r)
               << u8(raster_pixel.g >> 8) << u8(raster_pixel.g)
               << u8(raster_pixel.b >> 8) << u8(raster_pixel.b)
               << u8(raster_pixel.a >> 8) << u8(raster_pixel.a);
        }
    }
}

void writePFM(Canvas<vec3> const& canvas, std::ostream& os)
{
    char const* scale;

    if constexpr (std::endian::native == std::endian::little) {
        scale = "-1.0";
    } else if constexpr (std::endian::native == std::endian::big) {
        scale = "1.0";
    }

    os << "PF\n"
       << canvas.width() << " " << canvas.height() << "\n"
       << scale << "\n";

    for (i32 row = canvas.height() - 1; row >= 0; --row) {
        for (i32 col = 0; col < canvas.width(); ++col) {
            os.write(
                reinterpret_cast<char const*>(canvas[row, col].data()),
                sizeof(vec3));
        }
    }
}

export template<vec V>
void writePAM(Canvas<V> const& Canvas, std::string const& file_path)
{
    std::ofstream os(file_path, std::ios::binary);
    writePAM(Canvas, os);
}

export template<vec V>
void writePFM(Canvas<V> const& Canvas, std::string const& file_path)
{
    std::ofstream os(file_path, std::ios::binary);
    writePFM(Canvas, os);
}
} // namespace raytracer
