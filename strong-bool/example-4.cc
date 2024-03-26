#include <stdio.h>

//-- BEGIN EXAMPLE
class strong_bool
{
    bool b = false;
public:
    strong_bool() = default;
    strong_bool(bool v) : b(v) {}
    explicit operator bool() const { return b; }
};

class Example {
public:
    Example() : m_toggle(0) { }
    void SetIt(int v) { m_toggle = v; }
    void ToggleIt() { if (m_toggle) { m_toggle = 0; } else { m_toggle = 1; } }
    const char * Status() { if (m_toggle) return "ON"; else return "OFF"; }
private:
    strong_bool m_toggle;
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

    strong_bool a{0};
    strong_bool b = 2;
    strong_bool c{true};
    strong_bool d = false;

    return a && b && c && d && e.Status() ? 0 : 1;
}
