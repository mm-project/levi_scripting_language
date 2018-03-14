#include <levi_interp.hpp>

int main(int argc, char** argv)
{
	LeviInterpreter levi;

	levi.execute("function fibonacci(n)				"
	"{												"
    "    if (n <= 1) return n;						"
    "    return fibonacci(n - 2) + fibonacci(n - 1);"
	"}"
	""
	"print fibonacci(20)");
	
}
