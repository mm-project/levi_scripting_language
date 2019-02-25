
[![Build Status](https://travis-ci.org/nagaina/diploma.svg?branch=master)](https://travis-ci.org/nagaina/diploma)

# "levi" general purpose scripting language

Yes, Yet another scripting language.
Currently it's just run-time interpreter, however 
It's on-going project and there are plans to add virtual machine so parser backend will be translating to native bytcode. But at least for now it is working as fair interpreter. 

#### Following supported
* expressions
* functions definions, function calls
* if/while statements
* classes ( member function )
* comments

#### Usage
`./bin/levi <filename>`

#### Examples

Hanoi Game
```
function Hanoi(var m, var a, var b, var c) {
  moves++;
  if(m == 1){
    print << m << " from " << a << " to " << c << endl;
  }else{  
    Hanoi(m-1, a,c,b);
    cout << "Move disc " << m << " from " << a << " to " << c << endl;
    Hanoi(m-1,b,a,c);
  }
}

function main(){
  var discs = 4;
  var result = Hanoi(discs, 'A', 'B', 'C');
  print result;
}
```

Calculate fibonacii
```
function fibonacci(n)
{
        if (n <= 1) return n;
        return fibonacci(n - 2) + fibonacci(n - 1);
}
print fibonacci(20);
```

#### CPP API
In parallel we've started to work on providing cpp API to connect LEVI from cpp itself. 
but it's experimental

```
#include <integ/levi_interp.hpp>

int main(int argc, char** argv)
{
	LeviInterpreter levi;

	levi.execute("function fibonacci(n)				      "
	"{												                      "
  "    if (n <= 1) return n;						          "
  "    return fibonacci(n - 2) + fibonacci(n - 1);"
	"}                                              "
	"                                               "
	"print fibonacci(20);                           ");

}
```

#### Supported OS
* Linux
* Windows

#### Build steps
##### Linux
* todo

##### Windows
* todo



