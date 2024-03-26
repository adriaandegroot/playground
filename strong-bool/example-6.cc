#include <stdio.h>

//-- BEGIN EXAMPLE
class strong_bool
{
    bool b = false;
public:
    strong_bool() = default;
    template<typename T> strong_bool(T v) = delete;
    strong_bool(bool v) : b(v) {};
    explicit operator bool() const { return b; }
};

static_assert(sizeof(strong_bool) == sizeof(bool));
static_assert(alignof(strong_bool) == alignof(bool));
static_assert(sizeof(strong_bool) == 1);

class Example {
public:
    Example() = default;
    void SetIt(bool v) { m_toggle = v; }
    void ToggleIt() { if (m_toggle) { m_toggle = false; } else { m_toggle = true; } }
    const char * Status() { if (m_toggle) return "ON"; else return "OFF"; }
private:
    strong_bool m_toggle = false;
};
//-- END EXAMPLE

int main()
{
    Example e;
    e.ToggleIt();
    puts(e.Status());
    e.SetIt(3);
    puts(e.Status());
    e.ToggleIt();
    puts(e.Status());
    return e.Status() ? 0 : 1;
}
