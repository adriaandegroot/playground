#include <stdio.h>

//-- BEGIN EXAMPLE
class Example {
public:
    Example() : m_toggle(0) { }
    void SetIt(int v) { m_toggle = v; }
    void ToggleIt() { if (m_toggle) { m_toggle = 0; } else { m_toggle = 1; } }
    const char * Status() { if (m_toggle) return "ON"; else return "OFF"; }
private:
    int m_toggle;
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
